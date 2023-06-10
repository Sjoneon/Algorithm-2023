#pragma once

void error(char str[]);

#define MAX_VTXS 256

typedef char VtxData;
// 정점의 데이터를 나타내는 타입으로, 현재는 char로 정의
int adj[MAX_VTXS][MAX_VTXS]; // 인접 행렬로, 정점 간의 가중치 정보를 저장
int vsize; // 그래프의 정점 개수를 저장
VtxData vdata[MAX_VTXS]; // 정점의 데이터를 저장하는 배열

int is_empty_graph(); // 그래프가 비어있는지 확인
int is_full_graph(); // 그래프가 가득찼는지 확인
void init_graph(); // 그래프 초기화

void insert_vertex(VtxData name); // vertex 삽입
void insert_edge(int u, int v, int val); // 가중치 삽입
void insert_edge2(int u, int v, int val);

#define INF 9999
void load_wgraph(char* filename);

int path[MAX_VTXS]; // 경로
int dist[MAX_VTXS]; // 거리
int found[MAX_VTXS]; // 

int print_shortest_path(int start, int end); // 시작, 끝(vsize만큼)

int choose_vertex();

void shortest_path_dijkstra(int start);

