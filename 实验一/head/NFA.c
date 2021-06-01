#pragma once
#include "NFA.h"

void get_name(char* name)
{
    char c;
    int i = 0;
    //用于检测输入前有没有回车符或者空格
    if ((c = getchar()) == '\n' || c == ' ')
    {
        c = getchar();
    }
    while (c != '\n' && c != ' ')
    {
        *(name + i) = c;
        i++;
        //如果输入的名称太长
        if (i >= MAX_NAME_LEN)
        {
            printf("名称过长请重新输入！\n");
            i = 0;
        }
        c = getchar();
    }
    //字符串的结尾
    *(name + i) = '\0';
}

int match_name(int num, char* name[MAX_NAME_LEN + 1], char* state)
{
    //进行字符串的匹配
    for (int i = 0; i < num; i++)
    {
        if (!strncmp(*(name + i), state, MAX_NAME_LEN))
        {
            return i;
        }
    }
    return -1;
}

void init_NFA(int num, NFA* m)
{
    m->State_num = num;//状态个数赋值
    //为转移函数开辟空间
    m->Delta = (char***)malloc(sizeof(char*) * num);
    for (int i = 0; i < num; i++)
    {
        m->Delta[i] = (char**)malloc(sizeof(char*) * num);
        for (int j = 0; j < num; j++)
        {
            m->Delta[i][j] = (char*)malloc(sizeof(char*) * m->num_char);
        }
    }
    //初始化转移函数
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num; j++)
        {
            for (int k = 0; k < m->num_char; k++)
            {
                m->Delta[i][j][k] = 0;
            }
        }
    }
    //为终结符开辟空间
    m->F = (int*)malloc(sizeof(int) * num);
    //初始化
    for (int i = 0; i < num; i++)
    {
        m->F[i] = 0;
    }
}
void build_NFA(NFA* m, char* name[MAX_NAME_LEN + 1])
{

    //获取每一个状态的名称
    for (int i = 0; i < m->State_num; i++)
    {
        printf("num%d:", i);
        get_name(*(name + i));
    }

    //读取字符的个数
    printf("请输入字母表字符个数：");
    scanf_s("%d", &m->num_char);

    //初始化NFA
    init_NFA(m->State_num, m);
    getchar();//读取结尾回车

    //为字母表分配空间
    m->T = (char*)malloc(sizeof(char) * m->num_char);

    //读取字母表
    for (int i = 0; i < m->num_char; i++)
    {
        printf("num%d:", i);
        m->T[i] = getchar();
        getchar();
    }
    char temp[MAX_NAME_LEN + 1];

    //读取初始字符
    printf("请输入起始字符：");
    get_name(temp);
    int temp_num1, temp_num2;
    for (int i = 0; i < 1; i++)
    {
        if ((temp_num1 = match_name(m->State_num, name, temp)) != -1)
        {
            m->Q0 = temp_num1;
        }
        else            //输入错误重新输入
        {
            printf("未检测到该字符，请重新输入！");
            i--;
        }
    }

    //读入终结符
    int num;
    printf("请输入终结符个数：");
    scanf_s("%d", &num);//读入终结符的个数
    for (int i = 0; i < num; i++)
    {
        printf("num%d:", i);
        get_name(temp);
        if ((temp_num1 = match_name(m->State_num, name, temp)) != -1)
        {
            m->F[temp_num1] = 1;
        }
        else        //输入错误
        {
            printf("为检测到字符%s，请重新输入！", temp);
            i--;
        }
    }

    //读入转移函数
    char c;
    int n;
    printf("请输入状态转移函数个数：");
    scanf_s("%d", &n);//转移函数个数
    getchar();
    for (int i = 0; i < n; i++)
    {

        //源状态
        printf("num%d:", i);
        get_name(temp);
        temp_num1 = match_name(m->State_num, name, temp);
        if (temp_num1 == -1)
        {
            printf("未检测到字符%s，请重新输入！", temp);
            while (getchar() != '\n');
            i--;
            continue;
        }

        //转移字符
        while ((c = getchar()) == ' ');

        //目的状态
        get_name(temp);
        temp_num2 = match_name(m->State_num, name, temp);
        if (temp_num2 == -1)
        {
            printf("未检测到字符%s，请重新输入！", temp);
            while (getchar() != '\n');
            i--;
            continue;
        }
        //为转移函数赋值
        for (int j = 0; j < m->num_char; j++)
        {
            if (m->T[j] == c)
            {
                m->Delta[temp_num1][temp_num2][j] = 1;
            }
        }
    }
}

