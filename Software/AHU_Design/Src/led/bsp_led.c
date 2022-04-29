#include "./led/bsp_led.h"   

 /**
  * @brief  ��ʼ������LED��IO
  * @param  ��
  * @retval ��
  */
void LED_GPIO_Config(void)
{		
		
    /*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
    GPIO_InitTypeDef  GPIO_InitStruct;

    /*����LED��ص�GPIO����ʱ��*/
    LED_GPIO_CLK_ENABLE();
  
    /*ѡ��Ҫ���Ƶ�GPIO����*/															   
    GPIO_InitStruct.Pin = LED1_PIN|LED2_PIN;	

    /*�������ŵ��������Ϊ�������*/
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;  

    /*��������Ϊ����ģʽ*/
    GPIO_InitStruct.Pull  = GPIO_PULLUP;

    /*������������Ϊ���� */   
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

    /*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/
    HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);	
    /*�رպ��*/
    LED1_OFF;
		/*�ر��̵�*/
    LED2_OFF;
}



/*********************************************END OF FILE**********************/