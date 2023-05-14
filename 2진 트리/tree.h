#pragma once

typedef struct Node
{
    int value;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int value);                         // 새로운 노드를 생성하는 함수 선언
void connectChild(Node* parent, Node* left, Node* right);    // 부모 노드와 자식 노드들을 연결하는 함수 선언
Node* makeTree();                                    // 트리를 생성하는 함수 선언
void printTree(Node* root);                          // 트리의 노드 값을 출력하는 함수 선언
Node* findNode(Node* root, int value);               // 주어진 값과 일치하는 노드를 찾는 함수 선언
Node* insertLeftNode(Node* where, Node* new_node);   // 주어진 위치에 왼쪽 자식 노드를 삽입하는 함수 선언
Node* insertRightNode(Node* where, Node* new_node);  // 주어진 위치에 오른쪽 자식 노드를 삽입하는 함수 선언

