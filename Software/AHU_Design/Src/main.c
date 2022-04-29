/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx.h"
#include "./usart/bsp_debug_usart.h"
#include <stdlib.h>
#include "./led/bsp_led.h" 
#include "./timer/bsp_timer.h"
#include "./ad7606/bsp_spi_ad7606.h"
#include "./key/bsp_exti.h"

uint8_t timer_flag = 0; // �ж϶�ʱ��־�������ж���1
uint8_t rx_flag = 0; // �жϴ��ڱ�־�������ж���1


  

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

void DMA_Usart_Send(uint8_t *buf,uint8_t len)//���ڷ��ͷ�װ
{
 if(HAL_UART_Transmit_DMA(&UartHandle, buf,len)!= HAL_OK) //�ж��Ƿ�����������������쳣������쳣�жϺ���
  {
   printf("\nDMA���ڷ��ʹ���\n");
		LED1_ON;
  }

}
/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	uint8_t i=0;
	uint8_t j=0;
	uint8_t Data[SIZE*2]={0};
  /* MCU Configuration--------------------------------------------------------*/
  /* Configure the system clock */
  SystemClock_Config();
	EXTI_Key_Config();
  /* Initialize all configured peripherals */
  LED_GPIO_Config();  //��ʼ��������LED��
	Debug_USART_Config();
	USART_DMA_Config();
	AD7606_Config();   //����GPIO����
	
	ad7606_Init();
  while (1)
  {
    if(rx_flag)
		{
			rx_flag=0;			//���ñ�־λ
			ad7606_IRQSrc();	//�ж����һ�βɼ���ȡ
			i=0;
			for(j=0;j<SIZE;j++)	//���ɼ������ݲ��Ϊ�߰�λ��Ͱ�λ�洢�ڷ��ͻ�����
			{
				Data[i]=g_tAD[j]/256;		//�߰�λ
				Data[i+1]=g_tAD[j]%256;	//�Ͱ�λ
				i+=2;				
			}

			HAL_UART_Transmit(&UartHandle, (uint8_t *)Data, SIZE*2, 3);
//			//LED2_TOGGLE;  //���ڷ��ͳɹ�ʱ���̵���˸
		}
  }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
}


#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
