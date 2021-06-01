#pragma once
#define MAX_NAME_LEN 4
#include <stdlib.h>
#include <stdio.h>

typedef struct Graph2
{
    int state_num;      //状态个数
    int** state_flag;   //状态集合，标记位模式
    /*state_flag二维数组的第一维的下标是DFA中状态的序号，
     第二位的下标是NFA中状态的序号，其中数据有两种，1和0
     1表示所在行表示的DFA状态包含所在列的NFA状态*/
    int** state;        //状态集合，普通模式
    /*这种方式与标记位模式不同的是，这种模式用数组中的数据来记录所包含的NFA状态，用-1表示结束*/
    char*** Delta;      //状态转移函数与NFA相同
    int Q0;             //初始状态
    int* F;             //终结状态集合
    char* T;            //字母表集合
    int num_char;       //字母表字符个数
    int flag;           //用于标记哪个状态是空集在输出的时候忽略掉
}DFA;

int match_DFA(int num_DFA, int num, int** state, int* set);        //匹配DFA的状态，找到了返回状态序号，没有找到返回-1

void init_DFA(int num, DFA* n);//DFA的初始化

int Pow(int x, int y);       //幂函数计算

void Print(const DFA* m, const char* name[MAX_NAME_LEN]);//输出DFA
