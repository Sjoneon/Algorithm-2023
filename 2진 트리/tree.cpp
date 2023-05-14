#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

// 주어진 값으로 새로운 노드를 생성하는 함수
Node* createNode(int value)
{
    Node* pNode = (Node*)malloc(sizeof(Node));    // Node 구조체에 대한 메모리 할당
    pNode->value = value;                         // 노드의 값 설정
    pNode->left = NULL;                           // 왼쪽 자식 노드를 NULL로 초기화
    pNode->right = NULL;                          // 오른쪽 자식 노드를 NULL로 초기화
    return pNode;                                 // 생성된 노드 포인터 반환
}

// 부모 노드에 왼쪽과 오른쪽 자식 노드를 연결하는 함수
void connectChild(Node* parent, Node* left, Node* right)
{
    if (parent == NULL)
        return;               // 부모 노드가 NULL인 경우 함수 종료

    parent->left = left;      // 부모 노드의 왼쪽 자식 노드를 주어진 'left' 노드로 연결
    parent->right = right;    // 부모 노드의 오른쪽 자식 노드를 주어진 'right' 노드로 연결
}

// 샘플 트리를 생성하고 루트 노드를 반환하는 함수
Node* makeTree()
{
    Node* pRoot = createNode(100);                 // 값이 100인 새로운 루트 노드 생성
    Node* tleft = createNode(200);                 // 값이 200인 왼쪽 자식 노드 생성
    Node* tright = createNode(300);                // 값이 300인 오른쪽 자식 노드 생성

    connectChild(pRoot, tleft, tright);            // 루트 노드에 왼쪽과 오른쪽 자식 노드 연결
    connectChild(tright, createNode(400), createNode(500));  // 오른쪽 자식 노드에 추가적인 자식 노드 생성 및 연결

    return pRoot;                // 생성된 트리의 루트 노드 반환
}

// 트리 노드의 값을 전위 순회로 재귀적으로 출력하는 함수
void printTree(Node* root)
{
    if (root == NULL)
        return;                 // 루트 노드가 NULL인 경우 함수 종료

    printf("Node: %d ", root->value);    // 현재 노드의 값을 출력
    printTree(root->left);               // 왼쪽 서브트리를 전위 순회로 출력
    printTree(root->right);              // 오른쪽 서브트리를 전위 순회로 출력
}

// 주어진 값과 동일한 값을 가지는 노드를 트리에서 찾는 함수
Node* findNode(Node* root, int value)
{
    if (root == NULL || root->value == value)
        return root;                     // 루트 노드가 NULL이거나 찾는 값과 일치하는 경우 해당 노드 반환

    Node* leftResult = findNode(root->left, value);     // 왼쪽 서브트리에서 찾는 값 탐색
    if (leftResult != NULL)
        return leftResult;                              // 왼쪽 서브트리에서 찾았을 경우 해당 노드 반환

    Node* rightResult = findNode(root->right, value);   // 오른쪽 서브트리에서 찾는 값 탐색
    return rightResult;                                 // 오른쪽 서브트리에서 찾았을 경우 해당 노드 반환
}

// 주어진 노드의 왼쪽 자식으로 새로운 노드를 삽입하는 함수
Node* insertLeftNode(Node* where, Node* new_node)
{
    if (where != NULL)
    {
        new_node->left = where->left;    // 새로운 노드의 왼쪽 자식을 'where' 노드의 왼쪽 자식과 연결
        where->left = new_node;          // 'where' 노드의 왼쪽 자식을 새로운 노드로 연결
    }
    return where;                        // 변경된 트리의 'where' 노드 반환
}

// 주어진 노드의 오른쪽 자식으로 새로운 노드를 삽입하는 함수
Node* insertRightNode(Node* where, Node* new_node)
{
    if (where != NULL)
    {
        new_node->right = where->right;    // 새로운 노드의 오른쪽 자식을 'where' 노드의 오른쪽 자식과 연결
        where->right = new_node;           // 'where' 노드의 오른쪽 자식을 새로운 노드로 연결
    }
    return where;                          // 변경된 트리의 'where' 노드 반환
}
