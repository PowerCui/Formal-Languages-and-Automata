#pragma once
#include "NFA.h"

void get_name(char* name)
{
    char c;
    int i = 0;
    //���ڼ������ǰ��û�лس������߿ո�
    if ((c = getchar()) == '\n' || c == ' ')
    {
        c = getchar();
    }
    while (c != '\n' && c != ' ')
    {
        *(name + i) = c;
        i++;
        //������������̫��
        if (i >= MAX_NAME_LEN)
        {
            printf("���ƹ������������룡\n");
            i = 0;
        }
        c = getchar();
    }
    //�ַ����Ľ�β
    *(name + i) = '\0';
}

int match_name(int num, char* name[MAX_NAME_LEN + 1], char* state)
{
    //�����ַ�����ƥ��
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
    m->State_num = num;//״̬������ֵ
    //Ϊת�ƺ������ٿռ�
    m->Delta = (char***)malloc(sizeof(char*) * num);
    for (int i = 0; i < num; i++)
    {
        m->Delta[i] = (char**)malloc(sizeof(char*) * num);
        for (int j = 0; j < num; j++)
        {
            m->Delta[i][j] = (char*)malloc(sizeof(char*) * m->num_char);
        }
    }
    //��ʼ��ת�ƺ���
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
    //Ϊ�ս�����ٿռ�
    m->F = (int*)malloc(sizeof(int) * num);
    //��ʼ��
    for (int i = 0; i < num; i++)
    {
        m->F[i] = 0;
    }
}
void build_NFA(NFA* m, char* name[MAX_NAME_LEN + 1])
{

    //��ȡÿһ��״̬������
    for (int i = 0; i < m->State_num; i++)
    {
        printf("num%d:", i);
        get_name(*(name + i));
    }

    //��ȡ�ַ��ĸ���
    printf("��������ĸ���ַ�������");
    scanf_s("%d", &m->num_char);

    //��ʼ��NFA
    init_NFA(m->State_num, m);
    getchar();//��ȡ��β�س�

    //Ϊ��ĸ�����ռ�
    m->T = (char*)malloc(sizeof(char) * m->num_char);

    //��ȡ��ĸ��
    for (int i = 0; i < m->num_char; i++)
    {
        printf("num%d:", i);
        m->T[i] = getchar();
        getchar();
    }
    char temp[MAX_NAME_LEN + 1];

    //��ȡ��ʼ�ַ�
    printf("��������ʼ�ַ���");
    get_name(temp);
    int temp_num1, temp_num2;
    for (int i = 0; i < 1; i++)
    {
        if ((temp_num1 = match_name(m->State_num, name, temp)) != -1)
        {
            m->Q0 = temp_num1;
        }
        else            //���������������
        {
            printf("δ��⵽���ַ������������룡");
            i--;
        }
    }

    //�����ս��
    int num;
    printf("�������ս��������");
    scanf_s("%d", &num);//�����ս���ĸ���
    for (int i = 0; i < num; i++)
    {
        printf("num%d:", i);
        get_name(temp);
        if ((temp_num1 = match_name(m->State_num, name, temp)) != -1)
        {
            m->F[temp_num1] = 1;
        }
        else        //�������
        {
            printf("Ϊ��⵽�ַ�%s�����������룡", temp);
            i--;
        }
    }

    //����ת�ƺ���
    char c;
    int n;
    printf("������״̬ת�ƺ���������");
    scanf_s("%d", &n);//ת�ƺ�������
    getchar();
    for (int i = 0; i < n; i++)
    {

        //Դ״̬
        printf("num%d:", i);
        get_name(temp);
        temp_num1 = match_name(m->State_num, name, temp);
        if (temp_num1 == -1)
        {
            printf("δ��⵽�ַ�%s�����������룡", temp);
            while (getchar() != '\n');
            i--;
            continue;
        }

        //ת���ַ�
        while ((c = getchar()) == ' ');

        //Ŀ��״̬
        get_name(temp);
        temp_num2 = match_name(m->State_num, name, temp);
        if (temp_num2 == -1)
        {
            printf("δ��⵽�ַ�%s�����������룡", temp);
            while (getchar() != '\n');
            i--;
            continue;
        }
        //Ϊת�ƺ�����ֵ
        for (int j = 0; j < m->num_char; j++)
        {
            if (m->T[j] == c)
            {
                m->Delta[temp_num1][temp_num2][j] = 1;
            }
        }
    }
}

