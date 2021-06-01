#include <stdio.h>
#include "NFA.h"
#include "DFA.h"
#include "invert.h"

int main()
{
    NFA m1;             //����һ��NFA�ṹ
    int n;              //���ڼ�¼NFA��״̬����
    printf("������NFA��״̬������");     //��ʾ����
    scanf_s("%d", &n);     //����NFA��״̬����
    m1.State_num = n;     //��״̬������ֵ��NFA�ṹ��
    char** name = (char**)malloc(sizeof(char*) * n);    //״̬�����б�
    for (int i = 0; i < n; i++)        //Ϊ״̬�����б��ٿռ�
    {
        name[i] = (char*)malloc(sizeof(char) * MAX_NAME_LEN);
    }
    build_NFA(&m1, name);        //����NFA���������ݲ���¼��m1��
    DFA m2;                     //����һ��DFA
    m2.num_char = m1.num_char;    //DFA����ĸ��T��NFA����ĸ����ͬ
    m2.T = (char*)malloc(sizeof(char) * m2.num_char);  //ΪDFA��ĸ���ٵ�ַ
    for (int i = 0; i < m1.num_char; i++)      //ΪDFA����ĸ��ֵ
    {
        m2.T[i] = m1.T[i];
    }
    init_DFA(n, &m2);        //��ʼ��DFA
    invert(&m1, &m2);        //ת������
    Print(&m2, name);        //���DFA
    return 0;
}

