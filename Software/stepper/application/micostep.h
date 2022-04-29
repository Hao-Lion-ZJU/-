#ifndef MICOSTEP_H
#define MICOSTEP_H

#include "main.h"
#include "gpio.h"
#include "tim.h"
#include "usart.h"

#define CW  0
#define CCW 1

#define running 1
#define stop 0

typedef enum 
{
  Front = 0, 
  Back = 1,
	Left = 2,
	Right = 3	
} DirStatus;

typedef struct {
  //�������״̬
  unsigned char run_state : 1;
  //������з���
  unsigned char dir : 1;
  //��Ҫ������������
  unsigned int max_count;
  //��ǰ�Ѿ�������������
  unsigned int cur_count;
} step_ctrl;

#define SMD1_DIR(a)	if (a == CW)	\
					HAL_GPIO_WritePin(SMD1_DIR_PORT,SMD1_DIR_PIN,0);\
					else		\
					HAL_GPIO_WritePin(SMD1_DIR_PORT,SMD1_DIR_PIN,1)
					
#define SMD2_DIR(a)	if (a == CW)	\
					HAL_GPIO_WritePin(SMD2_DIR_PORT,SMD2_DIR_PIN,0);\
					else		\
					HAL_GPIO_WritePin(SMD2_DIR_PORT,SMD2_DIR_PIN,1)
			
extern void Plane_Move(DirStatus DIR,unsigned int dis);					
extern void SMD1_ENA(FunctionalState NewState);				
extern void SMD2_ENA(FunctionalState NewState);
extern unsigned char Get_PlaneStatus(void);
#endif				
//-----------------------------------------------------END OF FILE--------------------------------------------------------------------------------
					