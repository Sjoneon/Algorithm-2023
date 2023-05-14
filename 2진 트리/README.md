아래는 2진 트리에 대한 과제이며 그 조건들 입니다.

수업에서 다루었던 2진 트리 구조에 관한 코드를 완성하세요.



요구사항

1. 노드 타입 선언: 정수값, 왼쪽 노드, 오른쪽 노드 포인터로 구성 : 노트 타입 정의 (Value, Left Node, Right Node)

    typedef struct _Node { int value; struct _Node left, struct _Node right; } Node;



2. 트리 생성 함수 작성 : 다음과 같은 노드들을 생성, 포인터로 연결하여 Root 노드 포인터 반환

      (100, 200, 300), (200, NULL, NULL), (300, 400, 500), (400, NULL, NULL), (500, NULL, NULL)

      Node * makeTree()

  - 노드 생성함수 : Node * createNode(int value)





3. 전체 노드 값 출력 함수 작성 : pre order, in order, post order (재귀함수)

     void printNode(Node * root)



* 4. 추가 함수1 작성 : 특정 값을 찾는 노드의 포인터 반환하는 함수 (선택적)

     Node * findNode(int value)



* 5. 추가 함수2 작성 : 노드를 트리에 삽입하는 코드 작성 (선택적)

    Node * insertLeftNode (Node * where, Node * new_node)

    -->   트리의 중간에 있는 where 노드에 새로운 new_node를 기존의 Left 노드 사이에 삽입하고 where 노드 반환

    Node * insertRightNode(Node *where, Node * new_node)

    -->   트리의 중간에 있는 where 노드에 새로운 new_node를 기존의 Right 노드 사이에 삽입하고 where 노드 반환

    --> where 가 NULL이면 바로 NULL 반환


제약사항

- tree.h tree.cpp, test.cpp, main.cpp 로 분할하여 코드 작성

- test case : 먼저 트리
