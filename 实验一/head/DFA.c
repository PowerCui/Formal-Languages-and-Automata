#pragma once
#include "DFA.h"
#define MAX_NAME_LEN 4


int Pow(int x, int y)//幂函数
{
    int result = 1;
    for (int i = 0; i < y; i++)
    {
        result *= x;
    }
    return result;
}
int match_DFA(int num_DFA, int num, int** state_flag, int* set)
{
    for (int i = 0; i < num_DFA; i++)
    {
        int flag = 1;
        for (int j = 0; j < num && flag == 1; j++)
        {
            if (state_flag[i][j] != set[j])
            {
                flag = 0;
                break;
            }
        }
        if (flag == 1)
        {
            return i;
        }
    }
    return -1;
}

void init_DFA(int num, DFA* n)
{
    //状态个数初始化
    n->state_num = 0;
    //计算最大的状态个数
    int len = Pow(2, num);

    //为状态转移函数开辟空间
    n->Delta = (char***)malloc(sizeof(char*) * len);
    for (int i = 0; i < len; i++)
    {
        n->Delta[i] = (char**)malloc(sizeof(char*) * len);
        for (int j = 0; j < len; j++)
        {
            n->Delta[i][j] = (char*)malloc(sizeof(char) * n->num_char);
            for (int k = 0; k < n->num_char; k++)
            {
                n->Delta[i][j][k] = 0;
            }
        }
    }

    //为其他数据开辟空间
    n->state_flag = (int**)malloc(sizeof(int*) * len);
    n->state_flag[0] = (int*)malloc(sizeof(int) * num);
    n->state = (int**)malloc(sizeof(int*) * len);
    for (int i = 0; i < len; i++)
    {
        n->state[i] = (int*)malloc(sizeof(int) * (num + 1));
    }
    n->F = (int*)malloc(sizeof(int) * len);
    for (int i = 0; i < len; i++)
    {
        n->F[i] = 0;
    }
}

void Print(const DFA* m, const char* name[MAX_NAME_LEN])
{
    for (int i = 0; i < m->state_num; i++)//遍历DFA中所有状态
    {
        for (int j = 0; j < m->state_num; j++)//遍历所有可达状态
        {
            for (int k = 0; k < m->num_char; k++)//遍历所有字符
            {
                if (m->Delta[i][j][k] != 0 && i != m->flag)//可达且状态不是空集
                {
                    int index = 0;
                    while (m->state[i][index] != -1)
                    {
                        printf("%s ", name[m->state[i][index]]);
                        index++;
                    }
                    printf("%c", m->T[k]);
                    printf(" ");
                    index = 0;
                    if (j == m->flag)
                    {
                        printf("φ");
                    }
                    else
                    {
                        while (m->state[j][index] != -1)
                        {
                            printf("%s ", name[m->state[j][index]]);
                            index++;
                        }
                    }
                    printf("\n");
                }
            }
        }
    }
}
