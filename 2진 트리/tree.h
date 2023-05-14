#pragma once

typedef struct Node
{
    int value;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int value);                         // ���ο� ��带 �����ϴ� �Լ� ����
void connectChild(Node* parent, Node* left, Node* right);    // �θ� ���� �ڽ� ������ �����ϴ� �Լ� ����
Node* makeTree();                                    // Ʈ���� �����ϴ� �Լ� ����
void printTree(Node* root);                          // Ʈ���� ��� ���� ����ϴ� �Լ� ����
Node* findNode(Node* root, int value);               // �־��� ���� ��ġ�ϴ� ��带 ã�� �Լ� ����
Node* insertLeftNode(Node* where, Node* new_node);   // �־��� ��ġ�� ���� �ڽ� ��带 �����ϴ� �Լ� ����
Node* insertRightNode(Node* where, Node* new_node);  // �־��� ��ġ�� ������ �ڽ� ��带 �����ϴ� �Լ� ����

