#include <stdio.h>
#include "NFA.h"
#include "DFA.h"
#include "invert.h"

int main()
{
    NFA m1;             //创建一个NFA结构
    int n;              //用于记录NFA的状态个数
    printf("请输入NFA的状态个数：");     //提示输入
    scanf_s("%d", &n);     //输入NFA的状态个数
    m1.State_num = n;     //将状态个数赋值到NFA结构中
    char** name = (char**)malloc(sizeof(char*) * n);    //状态名字列表
    for (int i = 0; i < n; i++)        //为状态名字列表开辟空间
    {
        name[i] = (char*)malloc(sizeof(char) * MAX_NAME_LEN);
    }
    build_NFA(&m1, name);        //读入NFA，处理数据并记录在m1中
    DFA m2;                     //创建一个DFA
    m2.num_char = m1.num_char;    //DFA的字母表T和NFA的字母表相同
    m2.T = (char*)malloc(sizeof(char) * m2.num_char);  //为DFA字母表开辟地址
    for (int i = 0; i < m1.num_char; i++)      //为DFA的字母表赋值
    {
        m2.T[i] = m1.T[i];
    }
    init_DFA(n, &m2);        //初始化DFA
    invert(&m1, &m2);        //转化函数
    Print(&m2, name);        //输出DFA
    return 0;
}

