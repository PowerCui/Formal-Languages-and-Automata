#pragma once
#define MAX_NAME_LEN 4
#include <stdlib.h>
#include <stdio.h>

typedef struct Graph2
{
    int state_num;      //״̬����
    int** state_flag;   //״̬���ϣ����λģʽ
    /*state_flag��ά����ĵ�һά���±���DFA��״̬����ţ�
     �ڶ�λ���±���NFA��״̬����ţ��������������֣�1��0
     1��ʾ�����б�ʾ��DFA״̬���������е�NFA״̬*/
    int** state;        //״̬���ϣ���ͨģʽ
    /*���ַ�ʽ����λģʽ��ͬ���ǣ�����ģʽ�������е���������¼��������NFA״̬����-1��ʾ����*/
    char*** Delta;      //״̬ת�ƺ�����NFA��ͬ
    int Q0;             //��ʼ״̬
    int* F;             //�ս�״̬����
    char* T;            //��ĸ����
    int num_char;       //��ĸ���ַ�����
    int flag;           //���ڱ���ĸ�״̬�ǿռ��������ʱ����Ե�
}DFA;

int match_DFA(int num_DFA, int num, int** state, int* set);        //ƥ��DFA��״̬���ҵ��˷���״̬��ţ�û���ҵ�����-1

void init_DFA(int num, DFA* n);//DFA�ĳ�ʼ��

int Pow(int x, int y);       //�ݺ�������

void Print(const DFA* m, const char* name[MAX_NAME_LEN]);//���DFA
