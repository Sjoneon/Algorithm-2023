#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

// �־��� ������ ���ο� ��带 �����ϴ� �Լ�
Node* createNode(int value)
{
    Node* pNode = (Node*)malloc(sizeof(Node));    // Node ����ü�� ���� �޸� �Ҵ�
    pNode->value = value;                         // ����� �� ����
    pNode->left = NULL;                           // ���� �ڽ� ��带 NULL�� �ʱ�ȭ
    pNode->right = NULL;                          // ������ �ڽ� ��带 NULL�� �ʱ�ȭ
    return pNode;                                 // ������ ��� ������ ��ȯ
}

// �θ� ��忡 ���ʰ� ������ �ڽ� ��带 �����ϴ� �Լ�
void connectChild(Node* parent, Node* left, Node* right)
{
    if (parent == NULL)
        return;               // �θ� ��尡 NULL�� ��� �Լ� ����

    parent->left = left;      // �θ� ����� ���� �ڽ� ��带 �־��� 'left' ���� ����
    parent->right = right;    // �θ� ����� ������ �ڽ� ��带 �־��� 'right' ���� ����
}

// ���� Ʈ���� �����ϰ� ��Ʈ ��带 ��ȯ�ϴ� �Լ�
Node* makeTree()
{
    Node* pRoot = createNode(100);                 // ���� 100�� ���ο� ��Ʈ ��� ����
    Node* tleft = createNode(200);                 // ���� 200�� ���� �ڽ� ��� ����
    Node* tright = createNode(300);                // ���� 300�� ������ �ڽ� ��� ����

    connectChild(pRoot, tleft, tright);            // ��Ʈ ��忡 ���ʰ� ������ �ڽ� ��� ����
    connectChild(tright, createNode(400), createNode(500));  // ������ �ڽ� ��忡 �߰����� �ڽ� ��� ���� �� ����

    return pRoot;                // ������ Ʈ���� ��Ʈ ��� ��ȯ
}

// Ʈ�� ����� ���� ���� ��ȸ�� ��������� ����ϴ� �Լ�
void printTree(Node* root)
{
    if (root == NULL)
        return;                 // ��Ʈ ��尡 NULL�� ��� �Լ� ����

    printf("Node: %d ", root->value);    // ���� ����� ���� ���
    printTree(root->left);               // ���� ����Ʈ���� ���� ��ȸ�� ���
    printTree(root->right);              // ������ ����Ʈ���� ���� ��ȸ�� ���
}

// �־��� ���� ������ ���� ������ ��带 Ʈ������ ã�� �Լ�
Node* findNode(Node* root, int value)
{
    if (root == NULL || root->value == value)
        return root;                     // ��Ʈ ��尡 NULL�̰ų� ã�� ���� ��ġ�ϴ� ��� �ش� ��� ��ȯ

    Node* leftResult = findNode(root->left, value);     // ���� ����Ʈ������ ã�� �� Ž��
    if (leftResult != NULL)
        return leftResult;                              // ���� ����Ʈ������ ã���� ��� �ش� ��� ��ȯ

    Node* rightResult = findNode(root->right, value);   // ������ ����Ʈ������ ã�� �� Ž��
    return rightResult;                                 // ������ ����Ʈ������ ã���� ��� �ش� ��� ��ȯ
}

// �־��� ����� ���� �ڽ����� ���ο� ��带 �����ϴ� �Լ�
Node* insertLeftNode(Node* where, Node* new_node)
{
    if (where != NULL)
    {
        new_node->left = where->left;    // ���ο� ����� ���� �ڽ��� 'where' ����� ���� �ڽİ� ����
        where->left = new_node;          // 'where' ����� ���� �ڽ��� ���ο� ���� ����
    }
    return where;                        // ����� Ʈ���� 'where' ��� ��ȯ
}

// �־��� ����� ������ �ڽ����� ���ο� ��带 �����ϴ� �Լ�
Node* insertRightNode(Node* where, Node* new_node)
{
    if (where != NULL)
    {
        new_node->right = where->right;    // ���ο� ����� ������ �ڽ��� 'where' ����� ������ �ڽİ� ����
        where->right = new_node;           // 'where' ����� ������ �ڽ��� ���ο� ���� ����
    }
    return where;                          // ����� Ʈ���� 'where' ��� ��ȯ
}
