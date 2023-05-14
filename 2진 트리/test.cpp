#include <stdio.h>
#include "tree.h"

void test()
{
    Node* root;      //포인트 변수 3개 선언
    Node* find_value;
    Node* insert_value;
    int value = 400;

    root = makeTree();                              // 트리 생성 및 루트 노드 반환
    printTree(root);                                // 생성된 트리의 노드 값을 출력

    find_value = findNode(root, value);             // 트리에서 값이 400인 노드를 찾음
    printf("찾는 값: %d, 해당 주소: %p\n", find_value->value, find_value);

    root = insertLeftNode(root, createNode(600));   // 루트 노드의 왼쪽에 새로운 노드(값: 600) 삽입
    root = insertRightNode(root, createNode(700));  // 루트 노드의 오른쪽에 새로운 노드(값: 700) 삽입
    printTree(root);                                // 변경된 트리의 노드 값을 출력
}

