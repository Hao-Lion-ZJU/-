/**
  ****************************(C) COPYRIGHT 2022 AHU****************************
  * @file       test.c/h
  * @brief      ���ڿ����ƶ�ƽ̨
  * @note       
  * @history
  *  Version    Date            Author          Liangliang Hao (������)
	* E-mail  1526885155@qq.com
  *  V1.0.0     April-4-2022     AHU            1. done
  *
  @verbatim
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2022 AHU****************************
  */
#include "test.h"
#include <stdlib.h>


unsigned char uart_cmd;

/**
  * @brief  �����ڽ��յ�������
  * @paramin  ��
  * @retval ��
  */
void DealSerialData(void)
{
	unsigned int dis=0;
	//���յ�' '��ʼ��������
	if(uart_cmd==TRUE)
	{
		if(UART_RxBuffer[0] == 'f')		//��ǰ�ƶ�
      {
				//�Ӵ��ڻ�ȡ����
        dis = atoi((char const *)UART_RxBuffer+1);
				Plane_Move(0,dis);
			}
			else if(UART_RxBuffer[0] == 'b')		//����ƶ�
			{
				dis = atoi((char const *)UART_RxBuffer+1);
				Plane_Move(1,dis);
			}
			else if(UART_RxBuffer[0] == 'l')		//�����ƶ�
			{
				dis = atoi((char const *)UART_RxBuffer+1);
				Plane_Move(2,dis);
			}
			else if(UART_RxBuffer[0] == 'r')		//�����ƶ�
			{
				dis = atoi((char const *)UART_RxBuffer+1);
				Plane_Move(3,dis);
			}
		uart_cmd = FALSE;
		uart_FlushRxBuffer();
	}
}