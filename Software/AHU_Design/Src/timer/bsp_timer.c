#include"bsp_timer.h"

TIM_HandleTypeDef TIM_TimeBaseStructure;


/**
*********************************************************************************************************
* @brief  ʱ�����ж�����
* @param  ��
* @retval ��
*********************************************************************************************************
*/
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{  
    /* ������ʱ������ʱ��ʹ�� */
    __HAL_RCC_TIM4_CLK_ENABLE();

    /* �����ж����� */
    HAL_NVIC_SetPriority(TIM4_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(TIM4_IRQn);  
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_SET_TIM4_FREQ
*	����˵��: ����TIM4��ʱ��Ƶ��
*	��    �Σ�_ulFreq : ����Ƶ�ʣ���λHz��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_SET_TIM4_FREQ(uint32_t _ulFreq)
{
	uint16_t usPrescaler;
	uint16_t usPeriod;

//	HAL_TIM_Base_DeInit(&TIM_TimeBaseStructure);	/* ��λTIM4��ʱ�� */

	/* TIM4 configuration 
		TIM4CLK = 72 MHz	
	*/
	if (_ulFreq == 0)
	{
		return;		/* ����Ƶ��Ϊ0��ֹͣ���� */
	}
	else if (_ulFreq <= 100)   /* ����Ƶ��С��100Hz */
	{
		usPrescaler = 36000;		/* TM2CLK = 72 000 000/36000 = 2000 */
		usPeriod = 2000 / _ulFreq;			 	
	}
	else if (_ulFreq <= 200000)	/* ����Ƶ�� ��100Hz - 200kHz */
	{
		usPrescaler = 36 - 1;		/* TM2CLK = 36 000 000/36 = 2 000 000 */
		usPeriod = 2000000 / _ulFreq;
	}	
	else	/* ����Ƶ�ʴ��� 200kHz */
	{
		return;
	}
	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  TIM_TimeBaseStructure.Instance = TIM4;
	// ʱ��Ԥ��Ƶ��
	TIM_TimeBaseStructure.Init.Prescaler = usPrescaler-1;
	// ����������ģʽ������Ϊ���ϼ���
  TIM_TimeBaseStructure.Init.CounterMode = TIM_COUNTERMODE_UP;
	// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
  TIM_TimeBaseStructure.Init.Period = usPeriod-1;
	// ʱ�ӷ�Ƶ���� ��û�õ����ù�
  TIM_TimeBaseStructure.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	// �ظ���������ֵ��û�õ����ù�
  TIM_TimeBaseStructure.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	HAL_TIM_Base_Init(&TIM_TimeBaseStructure);
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  HAL_TIM_ConfigClockSource(&TIM_TimeBaseStructure, &sClockSourceConfig);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&TIM_TimeBaseStructure, &sMasterConfig);
	
	/* ���ж�ģʽ��������ʱ�� */
  HAL_TIM_Base_Start_IT(&TIM_TimeBaseStructure);
}  

/*********************************************END OF FILE**********************/
