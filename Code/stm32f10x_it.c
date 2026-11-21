/*----------------------函式庫宣告-------------------------*/
#include "stm32f10x.h"

/*----------------------定義宣告---------------------------*/
#define IR_0 0
#define IR_1 1
#define IR_2 2
#define IR_3 3
#define IR_4 4
#define IR_5 5

/*----------------------副程式宣告-------------------------*/
void BUZZER(void);
void MOTOR_Control(void);
void Encoder(void);
void Index(void);
	
/*----------------------變數宣告---------------------------*/
//ADC
int IR_Count;
extern float IR_ADC[6];
extern float IR_ADC_F[6];
//選單
extern int Menu_F;

//SYSTICK--------------------------------------------------//
void SysTick_Handler(void)
{
	BUZZER();
	Encoder();
	
	if(Menu_F==2||Menu_F==3)
	{
		Index();
	}
}

/******************************************************************************/
/*            STM32F10x Peripherals Interrupt Handlers                        */
/******************************************************************************/
//TIM2_ADC-------------------------------------------------//
void TIM2_IRQHandler(void)
{
	IR_Count++;
	
	if(IR_Count==1)
	{
		ADC_RegularChannelConfig(ADC1, ADC_Channel_2,1,ADC_SampleTime_7Cycles5);	
		ADC_SoftwareStartConvCmd(ADC1,ENABLE);
		ADC_ResetCalibration(ADC1);
		while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)==RESET);
		ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
		IR_ADC_F[IR_0]=ADC_GetConversionValue(ADC1);
		
		ADC_RegularChannelConfig(ADC1, ADC_Channel_13,1,ADC_SampleTime_7Cycles5);	
		ADC_SoftwareStartConvCmd(ADC1,ENABLE);
		ADC_ResetCalibration(ADC1);
		while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)==RESET);
		ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
		IR_ADC_F[IR_2]=ADC_GetConversionValue(ADC1);
		
		ADC_RegularChannelConfig(ADC1, ADC_Channel_11,1,ADC_SampleTime_7Cycles5);	
		ADC_SoftwareStartConvCmd(ADC1,ENABLE);
		ADC_ResetCalibration(ADC1);
		while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)==RESET);
		ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
		IR_ADC_F[IR_4]=ADC_GetConversionValue(ADC1);
	}	
	else if(IR_Count==2)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_8);
	}
	else if(IR_Count==3)
	{
		ADC_RegularChannelConfig(ADC1, ADC_Channel_2,1,ADC_SampleTime_7Cycles5);	
		ADC_SoftwareStartConvCmd(ADC1,ENABLE);
		ADC_ResetCalibration(ADC1); 
		while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)==RESET);
		ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
		IR_ADC[IR_0]=ADC_GetConversionValue(ADC1)-IR_ADC_F[IR_0];
		
		ADC_RegularChannelConfig(ADC1, ADC_Channel_13,1,ADC_SampleTime_7Cycles5);	
		ADC_SoftwareStartConvCmd(ADC1,ENABLE);
		ADC_ResetCalibration(ADC1);
		while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)==RESET);
		ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
		IR_ADC[IR_2]=ADC_GetConversionValue(ADC1)-IR_ADC_F[IR_2];
		
		ADC_RegularChannelConfig(ADC1, ADC_Channel_11,1,ADC_SampleTime_7Cycles5);	
		ADC_SoftwareStartConvCmd(ADC1,ENABLE);
		ADC_ResetCalibration(ADC1);
		while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)==RESET);
		ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
		IR_ADC[IR_4]=ADC_GetConversionValue(ADC1)-IR_ADC_F[IR_4];
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_8);
	}
	else if(IR_Count==5)
	{
		ADC_RegularChannelConfig(ADC1, ADC_Channel_1,1,ADC_SampleTime_7Cycles5);	
		ADC_SoftwareStartConvCmd(ADC1,ENABLE);
		ADC_ResetCalibration(ADC1);
		while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)==RESET);
		ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
		IR_ADC_F[IR_1]=ADC_GetConversionValue(ADC1);
		
		ADC_RegularChannelConfig(ADC1, ADC_Channel_12,1,ADC_SampleTime_7Cycles5);
		ADC_SoftwareStartConvCmd(ADC1,ENABLE);
		ADC_ResetCalibration(ADC1);
		while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)==RESET);
		ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
		IR_ADC_F[IR_3]=ADC_GetConversionValue(ADC1);
		
		ADC_RegularChannelConfig(ADC1, ADC_Channel_10,1,ADC_SampleTime_7Cycles5);
		ADC_SoftwareStartConvCmd(ADC1,ENABLE);
		ADC_ResetCalibration(ADC1);
		while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)==RESET);
		ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
		IR_ADC_F[IR_5]=ADC_GetConversionValue(ADC1);
	}
	else if(IR_Count==6)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_5);
	}
	else if(IR_Count==7)
	{
		ADC_RegularChannelConfig(ADC1, ADC_Channel_1,1,ADC_SampleTime_7Cycles5);	
		ADC_SoftwareStartConvCmd(ADC1,ENABLE);
		ADC_ResetCalibration(ADC1);
		while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)==RESET);
		ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
		IR_ADC[IR_1]=ADC_GetConversionValue(ADC1)-IR_ADC_F[IR_1];
		
		ADC_RegularChannelConfig(ADC1, ADC_Channel_12,1,ADC_SampleTime_7Cycles5);	
		ADC_SoftwareStartConvCmd(ADC1,ENABLE);
		ADC_ResetCalibration(ADC1);
		while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)==RESET);
		ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
		IR_ADC[IR_3]=ADC_GetConversionValue(ADC1)-IR_ADC_F[IR_3];
		
		ADC_RegularChannelConfig(ADC1, ADC_Channel_10,1,ADC_SampleTime_7Cycles5);	
		ADC_SoftwareStartConvCmd(ADC1,ENABLE);
		ADC_ResetCalibration(ADC1);
		while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)==RESET);
		ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
		IR_ADC[IR_5]=ADC_GetConversionValue(ADC1)-IR_ADC_F[IR_5];
		
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	}
	else if(IR_Count==8)
	{
		IR_Count=0;
	}
	
	TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update);	
}

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{}
