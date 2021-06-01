#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_NAME_LEN 4

typedef struct Graph1
{
    int State_num;      //NFA状态个数
    char*** Delta;      //Delta用三维字符数组存储将自动机看做图，每个状态代表一行或者一列，第三维用于表示用哪个字符可达
    int Q0;     //初始状态
    int* F;     //终结状态的集合
    char* T;    //字母表的集合
    int num_char;   //字母的个数
}NFA;

void build_NFA(NFA* m, char* name[MAX_NAME_LEN + 1]);  //读入NFA并处理数据生成一个NFA

void get_name(char* name);        //用于读取状态名

int match_name(int num, char* name[MAX_NAME_LEN + 1], char* state);     //用于匹配状态名，匹配到返回状态序号，没有匹配到则返回-1

void init_NFA(int num, NFA* m);      //初始化NFA，为NFA分配空间
