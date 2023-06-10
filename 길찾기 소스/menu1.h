#pragma once

typedef struct _Region_
{
	char region[5];
	char nickname[12];
}Region;

Region R[10];

void You_Find_Road();
int start_point();
int end_point();
int Transport();
void T_R_Result();

void load_road_Region(char* filename);

void menu1();
