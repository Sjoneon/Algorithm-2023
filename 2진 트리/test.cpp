#include <stdio.h>
#include "tree.h"

void test()
{
    Node* root;      //����Ʈ ���� 3�� ����
    Node* find_value;
    Node* insert_value;
    int value = 400;

    root = makeTree();                              // Ʈ�� ���� �� ��Ʈ ��� ��ȯ
    printTree(root);                                // ������ Ʈ���� ��� ���� ���

    find_value = findNode(root, value);             // Ʈ������ ���� 400�� ��带 ã��
    printf("ã�� ��: %d, �ش� �ּ�: %p\n", find_value->value, find_value);

    root = insertLeftNode(root, createNode(600));   // ��Ʈ ����� ���ʿ� ���ο� ���(��: 600) ����
    root = insertRightNode(root, createNode(700));  // ��Ʈ ����� �����ʿ� ���ο� ���(��: 700) ����
    printTree(root);                                // ����� Ʈ���� ��� ���� ���
}

