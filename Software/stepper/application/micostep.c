/**
  ****************************(C) COPYRIGHT 2022 AHU****************************
  * @file       micostep.c/h
  * @brief      ���Ʋ�������ײ�
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
#include "micostep.h"
#define p 3.0					//˿�˵���Ϊ3mm
#define ppr			3200		//���ÿתһȦ�����������

 step_ctrl SMD1={0};
 step_ctrl SMD2={0};

/**
  * @brief          1�Ų������ʹ�ܺ���
  * @param[in]      DISABEL�������
  * @param[in]      ENABLE�����
  * @retval         none
  */
void SMD1_ENA(FunctionalState NewState)
{
    if(NewState)
    {
      //ENAʧ�ܣ���ֹ���������
			HAL_GPIO_WritePin(SMD1_ENA_PORT,SMD1_ENA_PIN,1);
    }
    else
    {
      //ENAʹ��  
			HAL_GPIO_WritePin(SMD1_ENA_PORT,SMD1_ENA_PIN,0);     
    }  
}

/**
  * @brief          2�Ų������ʹ�ܺ���
  * @param[in]      DISABEL�������
  * @param[in]      ENABLE�����
  * @retval         none
  */
void SMD2_ENA(FunctionalState NewState)
{
    if(NewState)
    {
      //ENAʧ�ܣ���ֹ���������
			HAL_GPIO_WritePin(SMD2_ENA_PORT,SMD2_ENA_PIN,1);
    }
    else
    {
      //ENAʹ��  
			HAL_GPIO_WritePin(SMD2_ENA_PORT,SMD2_ENA_PIN,0);     
    }  
}


/**
  * @brief          ʹ�����������������
	* @param[in]      SMD:�����Ĳ�������������
	* @param[in]      steps:�����������
	* @param[in]      dir:��ת����
  * @retval         none
  */
void SMD_Move(step_ctrl* SMD,unsigned int steps,unsigned char dir)
{
	SMD->dir=dir;
	SMD->cur_count=0; //���¿�ʼ����
	SMD->max_count=steps;
	SMD->run_state=running;
	if(SMD==&SMD1)
	{
		SMD1_DIR(dir);
		HAL_Delay(10);
		HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1);               //����pwm
	}
	else
	{
		SMD2_DIR(dir);
		HAL_Delay(10);
		HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_4);               //����pwm
	}

}


/**
  * @brief          XYƽ̨�ƶ�����
	* @param[in]      DirStatus:  0:ǰ   1����   2����		3:��
	* @param[in]      dis:  �ƶ�����  ��λ��mm
  * @retval         none
  */
void Plane_Move(DirStatus DIR,unsigned int dis)
{
	unsigned int steps=0;
	steps=(dis/3.0)*ppr;				//������=�ƶ�����/˿�˵���*ÿȦ������
	if(DIR==Front)
	{
		SMD_Move(&SMD2,steps,CW);
	}
	else if(DIR==Back)
	{
		SMD_Move(&SMD2,steps,CCW);
	}
	else if(DIR==Left)
	{
		SMD_Move(&SMD1,steps,CW);
	}
	else if(DIR==Right)
	{
		SMD_Move(&SMD1,steps,CCW);
	}
}

/**
  * @brief          ���ص�ǰƽ̨����״̬
	* @param[in]      none
	* @retval         Statues:    0:��������		1��ֹͣ״̬
  */
unsigned char Get_PlaneStatus(void)
{
	if((SMD1.run_state==stop)&&(SMD2.run_state==stop))
	{
		return 1;
	}
	else
		return 0;
}



/**
  * @brief          PWM���һ������Ļص�����
	* @param[in]      htim:��ʱ�����  htim3����һ�Ų��������htim2���ƶ��Ų������
  * @retval         none
  */
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(htim);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_TIM_PWM_PulseFinishedCallback could be implemented in the user file
   */
	if(htim==(&htim3))
	{
		if(SMD1.cur_count<SMD1.max_count)	//�������ۼƵ�Ӧ���ֵʱ,ֹͣPWM���
		{
			SMD1.cur_count++;
		}
		else
		{
			SMD1.cur_count=0;
			HAL_TIM_PWM_Stop_IT(&htim3, TIM_CHANNEL_1);
			SMD1.run_state=stop;
		}
	}
	if(htim==(&htim2))
	{
		if(SMD2.cur_count<SMD2.max_count)
		{
			SMD2.cur_count++;
		}
		else
		{
			SMD2.cur_count=0;
			HAL_TIM_PWM_Stop_IT(&htim2, TIM_CHANNEL_4);
			SMD2.run_state=stop;
		}
	}
	if((SMD1.run_state==stop)&&(SMD2.run_state==stop))			//������������ת����ϣ���
	{
		unsigned char ch='y';
		HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 1000);
	}
}

