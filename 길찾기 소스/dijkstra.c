#include <stdio.h>
#include <stdlib.h>
#include "menu1.h"
#define MAX_VTXS 256

// 다익스트라 알고리즘

#define _CRT_SECURE_NO_WARNINGS

void error(char str[])
{ // 오류 메세지를 출력하고 프로그램을 종료하는 함수
	printf("%s\n", str);
	exit(1);
}

typedef struct VtxData // 지역 정보 담아주는 구조체
{
	char name[50];
} VtxData;

// 정점(지역)의 데이터를 나타내는 타입으로, 현재는 char로 정의
int adj[MAX_VTXS][MAX_VTXS]; // 인접 행렬로, 정점 간의 가중치(거리) 정보를 저장
int vsize; // 그래프(지역)의 정점 개수를 저장
VtxData vdata[MAX_VTXS]; // 정점(지역)의 데이터를 저장하는 배열

int is_empty_graph() // 그래프가 비어있는지 확인
{
	return (vsize == 0);
}

int is_full_graph() // 그래프가 가득찼는지 확인
{
	return (vsize >= MAX_VTXS);
}

void init_graph() // 그래프 초기화
{
	int i, j;
	vsize = 0;
	for (i = 0; i < MAX_VTXS; i++) 
	{
		for (j = 0; j < MAX_VTXS; j++)
		{
			adj[i][j] = 0;
		}
	}
}

void insert_vertex(VtxData name) // vertex(지역 정보) 삽입
{
	if (is_full_graph())
	{
		error("Error: 그래프 정점의 개수 초과");
	}
	else
		vdata[vsize++] = name;
	// 정점의 데이터를 vdata 배열에 저장하고, 'vsize'값을 증가시킴
}

void insert_edge(int u, int v, int val) // 가중치(거리) 삽입
{
	adj[u][v] = val;
}

void insert_edge2(int u, int v, int val) // 무방향그래프 버전
{
	adj[u][v] = adj[v][u] = val; // 서로 반대도 val값으로 똑같다.
}

#define INF 9999
void load_wgraph(char* filename) // Region.txt파일에 있는 정보들을 구조체로 저장해주는 함수
{
	int i, j, val, n;
	VtxData str[80];
	FILE* fp = fopen(filename, "r");
	if (fp != NULL)
	{
		init_graph(); // 그래프의 초기화
		fscanf(fp, "%d", &n); // 파일의 첫 번째 줄에서 그래프의 크기 'n'을 불러옴
		for (i = 0; i < n; i++)
		{
			fscanf(fp, "%s", str[i].name); // 두 번째부터 문자열을 str로 받아옴
			insert_vertex(str[i]); // 각 정점의 데이터를 insert_vertex를 통해 삽입
			// str[i] 구조체를 insert_vertex 함수에 전달
			for (j = 0; j < n; j++)
			{
				fscanf(fp, "%d", &val); // 문자열 다음에 있는 숫자를 val에 담음
				if (i != j && val == 0) // val 값이 0이고, i, j가 서로 다르다면 
				{
					adj[i][j] = INF;
				}
				else // 둘 중 하나라도 아니라면
				{
					adj[i][j] = val; // val 값을 넣음
				}
			}
		}
		fclose(fp); // 파일 닫음
	}
}

int path[MAX_VTXS]; // 경로
int dist[MAX_VTXS]; // 거리
int found[MAX_VTXS];// 발견 확인 여부

int choose_vertex() // 최단거리의 위치를 출력해주는 함수
{
	int i, min = INF, minpos = -1;

	for (i = 0; i < vsize; i++)
	{
		if (dist[i] < min && !found[i]) // 거리가 현재정점보다 최단거리가 더 작고 선택되지 않은 값이면
		{
			min = dist[i]; // dist[i](최단거리)를 min에 대입
			//printf("%d ", dist[i]);
			minpos = i; // 몇 번 째 정점인지 minpos로 받음
		}
	}
	return minpos; // minpos값 반환
}

void shortest_path_dijkstra(int start) // 다익스트라 알고리즘 함수
{
	int i, u, w;
	for (i = 0; i < vsize; i++)
	{
		path[i] = -1; // -1로 초기화하여 미방문 상태로 표시
	}
	
	for (i = 0; i < vsize; i++) // 그래프의 갯수만큼
	{
		dist[i] = adj[start][i]; // adj[0][i]를 dist[i]에 대입
		// 시작 정점으로부터의 초기 거리를 설정하는 단계
		path[i] = start; // 최단 경로 추적을 위한 초기 설정
		found[i] = 0; // 해당 정점은 아직 방문하지 않았다는 것을 나타냄
	}
	found[start] = 1; // 시작정점은 이미 방문한 것이기 때문에 1로 처리
	dist[start] = 0; // 시작 정점 거리를 0으로 설정 (D)

	for (i = 0; i < vsize; i++)
	{
		u = choose_vertex(); // 최단거리 선정 후
		found[u] = 1; // 그 위치를 찾았다고 표시해놓음
		
		for (w = 0; w < vsize; w++)
		{
			if (found[w] == 0) // 아직 방문하지 않은 곳이 있다면
			{
				if (dist[u] + adj[u][w] < dist[w]) 
				// 지금 구한 거리에 adj(인접행렬)을 더한 것이 
				//	현재 최단 거리(dist[w])보다 작으면
				{
					dist[w] = dist[u] + adj[u][w]; // 최단거리를 갱신한다.
					path[w] = u; // 정점 w의 이전 정점을 u로 설정함
				}
			}
		}

	}
}

int print_shortest_path(int start, int end) // 다익스트라 결과값 출력하는 함수
// 시작, 끝(vsize만큼)
{
	shortest_path_dijkstra(start);

	return dist[end]; // 도착지 거리 출력
	
}
