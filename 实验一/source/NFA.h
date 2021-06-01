#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_NAME_LEN 4

typedef struct Graph1
{
    int State_num;      //NFA״̬����
    char*** Delta;      //Delta����ά�ַ�����洢���Զ�������ͼ��ÿ��״̬����һ�л���һ�У�����ά���ڱ�ʾ���ĸ��ַ��ɴ�
    int Q0;     //��ʼ״̬
    int* F;     //�ս�״̬�ļ���
    char* T;    //��ĸ��ļ���
    int num_char;   //��ĸ�ĸ���
}NFA;

void build_NFA(NFA* m, char* name[MAX_NAME_LEN + 1]);  //����NFA��������������һ��NFA

void get_name(char* name);        //���ڶ�ȡ״̬��

int match_name(int num, char* name[MAX_NAME_LEN + 1], char* state);     //����ƥ��״̬����ƥ�䵽����״̬��ţ�û��ƥ�䵽�򷵻�-1

void init_NFA(int num, NFA* m);      //��ʼ��NFA��ΪNFA����ռ�
