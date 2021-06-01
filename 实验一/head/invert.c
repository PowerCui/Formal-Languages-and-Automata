//
//  invert.c
//  NFA2DFA
//
//  Created by ������ on 2021/4/11.
//
#pragma once
#include "invert.h"
#include "NFA.h"
#include "DFA.h"

void invert(NFA* m1, DFA* m2)
{
    //DFA�ĵ�һ��״̬Ϊ��ʼ״̬��NFA��ͬ��ΪDFA�ĵ�һ��״̬��ֵ
    m2->state_num = 1;
    m2->state_flag[0][m1->Q0] = 1;
    m2->state[0][0] = m1->Q0;
    m2->state[0][1] = -1;


    int f = 0;                        //���ֵ���ڴ���ռ�
    int num_inited_state = 0;       //���ڼ�¼�Ѿ��������DFA��״̬


    while (num_inited_state != m2->state_num)//�������DFA��״̬�����������е�״̬������ʾת����������
    {
        for (int k = 0; k < m1->num_char; k++)//k���ڱ����ַ����е������ַ�
        {
            int flag = 0;                     //���λ���ڼ�¼DFA�����ɵĿռ�״̬�����


            int* array_temp = (int*)malloc(sizeof(int) * m1->State_num);//�����������ڼ�¼�������DFA״̬
            for (int i = 0; i < m1->State_num; i++)
            {
                array_temp[i] = 0;      //����ʱ������г�ʼ��
            }


            for (int i = 0; m2->state[num_inited_state][i] != -1; i++)//����DFA��δ�����״̬����������״̬
            {
                int temp = m2->state[num_inited_state][i];//temp���ڼ�¼δ�����״̬������ÿһ��״̬
                for (int j = 0; j < m1->State_num; j++)//����Delta�е�ֵ
                {
                    if (m1->Delta[temp][j][k] == 1)       //���Delta�е�ֵΪ1˵��״̬temp��״̬j��һ���ַ�k��·��
                    {
                        array_temp[j] = 1;      //˵��tempͨ��k��j�ɴj����뵽�������µ�״̬��
                        flag = 1;                 //˵����״̬���ǿռ�
                    }
                }
            }
            if (flag == 0 && f == 0)               //���û���κ�״̬�ɴ���ǵ�һ���ռ����ռ�Ҳ�����ɿռ���
            {
                m2->flag = m2->state_num;     //m_flag���ڼ�¼�ռ���λ��
                f = 1;
            }


            int ret_val = match_DFA(m2->state_num, m1->State_num, m2->state_flag, array_temp);
            //������ɵ�״̬��DFA���Ƿ��Ѿ�����
            if (ret_val != -1)//�Ѿ����ڷ��ظ�״̬��λ��
            {
                m2->Delta[num_inited_state][ret_val][k] = 1;   //������Ӧ��Delta����Ϊ1
            }
            else        //�����ڸ�״̬
            {

                m2->state_flag[m2->state_num] = array_temp;//����״̬��ֵ��m2

                //�������е�state_flag����state
                int n = 0;    //���ڼ�¼state��״̬�ĸ���
                for (int i = 0; i < m1->State_num; i++)
                {
                    if (m2->state_flag[m2->state_num][i] == 1)
                    {
                        m2->state[m2->state_num][n] = i;
                        n++;
                    }
                }
                m2->state[m2->state_num][n] = -1; //-1��ʶ�������
                m2->Delta[num_inited_state][m2->state_num][k] = 1;//ת��������ֵ
                m2->state_num++;//״̬����+1
            }
        }
        num_inited_state++;     //�Ѵ����״̬+1
    }
    //�����ս��
    for (int i = 0; i < m1->State_num; i++)
    {
        if (m1->F[i] == 1)
        {
            for (int j = 0; j < m2->state_num; j++)
            {
                for (int k = 0; k < m1->State_num; k++)
                {
                    if (m2->state_flag[j][k] == i)
                    {
                        m2->F[j] = 1;
                        break;
                    }
                }
            }
        }
    }
}
