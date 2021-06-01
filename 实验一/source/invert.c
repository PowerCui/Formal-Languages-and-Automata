//
//  invert.c
//  NFA2DFA
//
//  Created by 刘明哲 on 2021/4/11.
//
#pragma once
#include "invert.h"
#include "NFA.h"
#include "DFA.h"

void invert(NFA* m1, DFA* m2)
{
    //DFA的第一个状态为初始状态与NFA相同，为DFA的第一个状态赋值
    m2->state_num = 1;
    m2->state_flag[0][m1->Q0] = 1;
    m2->state[0][0] = m1->Q0;
    m2->state[0][1] = -1;


    int f = 0;                        //标记值用于处理空集
    int num_inited_state = 0;       //用于记录已经处理完的DFA的状态


    while (num_inited_state != m2->state_num)//处理完的DFA的状态数量等于所有的状态数量表示转换函数结束
    {
        for (int k = 0; k < m1->num_char; k++)//k用于遍历字符集中的所有字符
        {
            int flag = 0;                     //标记位用于记录DFA中生成的空集状态的序号


            int* array_temp = (int*)malloc(sizeof(int) * m1->State_num);//整形数组用于记录构造出新DFA状态
            for (int i = 0; i < m1->State_num; i++)
            {
                array_temp[i] = 0;      //对临时数组进行初始化
            }


            for (int i = 0; m2->state[num_inited_state][i] != -1; i++)//遍历DFA中未处理的状态包含的所有状态
            {
                int temp = m2->state[num_inited_state][i];//temp用于记录未处理的状态包含的每一个状态
                for (int j = 0; j < m1->State_num; j++)//遍历Delta中的值
                {
                    if (m1->Delta[temp][j][k] == 1)       //如果Delta中的值为1说明状态temp到状态j有一条字符k的路径
                    {
                        array_temp[j] = 1;      //说明temp通过k到j可达，j需加入到创建的新的状态中
                        flag = 1;                 //说明该状态不是空集
                    }
                }
            }
            if (flag == 0 && f == 0)               //如果没有任何状态可达，且是第一个空集（空集也会生成空集）
            {
                m2->flag = m2->state_num;     //m_flag用于记录空集的位置
                f = 1;
            }


            int ret_val = match_DFA(m2->state_num, m1->State_num, m2->state_flag, array_temp);
            //检测生成的状态在DFA中是否已经存在
            if (ret_val != -1)//已经存在返回该状态的位置
            {
                m2->Delta[num_inited_state][ret_val][k] = 1;   //将所对应的Delta设置为1
            }
            else        //不存在该状态
            {

                m2->state_flag[m2->state_num] = array_temp;//将该状态赋值给m2

                //根据已有的state_flag生成state
                int n = 0;    //用于记录state中状态的个数
                for (int i = 0; i < m1->State_num; i++)
                {
                    if (m2->state_flag[m2->state_num][i] == 1)
                    {
                        m2->state[m2->state_num][n] = i;
                        n++;
                    }
                }
                m2->state[m2->state_num][n] = -1; //-1标识数组结束
                m2->Delta[num_inited_state][m2->state_num][k] = 1;//转换函数赋值
                m2->state_num++;//状态个数+1
            }
        }
        num_inited_state++;     //已处理的状态+1
    }
    //处理终结符
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
