/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "arm_math.h"
#include "ModBusRTU.h"
//#include "call_mode.h"
#include "call_data.h"
#include "globalVar.h"
#include "gripper.h"
#include "motor_control.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim5;
TIM_HandleTypeDef htim8;
TIM_HandleTypeDef htim16;
TIM_HandleTypeDef htim20;

UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_tx;
DMA_HandleTypeDef hdma_usart2_rx;

/* USER CODE BEGIN PV */
ModbusHandleTypedef hmodbus;
uint32_t fpos = 0;
//u16u8_t registerFrame[200];
uint8_t guuuauua = 0 , vacc = 0, pp = 0;

typedef struct
{
	// for record New / Old value to calculate dx / dt
	uint32_t QEIRead[2];
//	uint64_t TimeStamp[2];
//	float QEIPostion_1turn;
//	float QEIAngularVelocity;
}QEI_StructureTypeDef;

QEI_StructureTypeDef QEIdata = {0};

int abbs = 0;

//int set_pos = 0;
float pi = 3.1415926535897932384626433832795;
//float di_pulley = 24.95;

arm_pid_instance_f32 PID = { 0 };
uint32_t QEI_raw = 0;
float QEI_mm = 0;
float set_point = 0;
float en_motor = 0;
float PWMset = 0;
float diffpos = 0;
uint32_t Vfeedback = 0;
uint8_t condi = 0;

uint16_t ADC[2] = { 0 };

uint16_t sen_top = 0;
uint16_t sen_bot = 0;

uint32_t time = 0;



/*-----------------------------------*/
float32_t kp = 0;
float32_t ki = 0;
float32_t kd = 0;
uint32_t Now = 0;
uint32_t Lastime = 0;
float error = 0;
float errorsum = 0;
float Iterm = 0;
float dinput = 0;
float Lasterror = 0;
float speed = 0;
float LastPos = 0;
float Dis_down = 0;
//float dt = 0;
float dt_velo = 0;
float dt_acc = 0;

float tim_velo_new = 0;
float tim_velo_last = 0;
float tim_acc_new = 0;
float tim_acc_last = 0;
float velo_new = 0;
float velo_last = 0;
float acc = 0;


/*--------------------------------------------------*/
float Vmax = 600.0; // mm/s
float Amax = 500.0; // mm/s^2
float Distance = 0;
float t = 0;
float temp_pos_acc = 0;
float temp_pos_const = 0;
float temp_v_acc = 0;
int temp = 0;
float Distance_Velo_Max = 0;
float traj[3];
float pos = 0;


float Time_acc = 0;
float Time_acc_tri = 0;
float Time_dec = 0;
float Time_const = 0;
float time_now = 0;
float Timestamp = 0;
float QEI_start = 0;
uint8_t trajec_state = 0;

float tim_new = 0;
float tim_last = 0;

uint8_t temp_check = 0;
//uint32_t Position[2];
//uint64_t TimeStamp[2];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM16_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM8_Init(void);
static void MX_TIM20_Init(void);
static void MX_TIM5_Init(void);
static void MX_TIM4_Init(void);
static void MX_TIM3_Init(void);
/* USER CODE BEGIN PFP */
void remote_recieve();
void motor_run(uint64_t pwm, uint8_t dir);
int go_point();
void speedread();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_TIM16_Init();
  MX_TIM2_Init();
  MX_TIM1_Init();
  MX_TIM8_Init();
  MX_TIM20_Init();
  MX_TIM5_Init();
  MX_TIM4_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
  hmodbus.huart = &huart2;
  hmodbus.htim = &htim16;
  hmodbus.slaveAddress = 0x15;
  hmodbus.RegisterSize = 200;
  Modbus_init(&hmodbus, registerFrame);

  HAL_TIM_Base_Start_IT(&htim2);

  HAL_TIM_Encoder_Start(&htim1,TIM_CHANNEL_ALL);
//
  HAL_TIM_Base_Start(&htim5);
  HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_2);

  trajec_target = -10;
//
//  HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_ALL);

  arm_pid_instance_f32 PID = {0};
  PID.Kp = 0.4;
  PID.Ki = 0.0001;
  PID.Kd = 0;
  arm_pid_init_f32(&PID, 0);

//  HAL_TIM_IC_Start(&htim1, TIM_CHANNEL_1);
//  HAL_TIM_IC_Start(&htim1, TIM_CHANNEL_2);
//  HAL_TIM_IC_Start(&htim1, TIM_CHANNEL_3);
//  HAL_TIM_IC_Start(&htim1, TIM_CHANNEL_4);
  HAL_TIM_IC_Start(&htim3, TIM_CHANNEL_1);
  HAL_TIM_IC_Start(&htim3, TIM_CHANNEL_2);
  HAL_TIM_IC_Start(&htim4, TIM_CHANNEL_1);
  HAL_TIM_IC_Start(&htim4, TIM_CHANNEL_2);
  HAL_TIM_IC_Start(&htim8, TIM_CHANNEL_1);
  HAL_TIM_IC_Start(&htim8, TIM_CHANNEL_2);
  HAL_TIM_IC_Start(&htim8, TIM_CHANNEL_3);
  HAL_TIM_IC_Start(&htim8, TIM_CHANNEL_4);
//  HAL_TIM_IC_Start(&htim20, TIM_CHANNEL_1);
//  HAL_TIM_IC_Start(&htim20, TIM_CHANNEL_2);
  HAL_TIM_IC_Start(&htim20, TIM_CHANNEL_1);
  HAL_TIM_IC_Start(&htim20, TIM_CHANNEL_2);
  HAL_TIM_IC_Start(&htim20, TIM_CHANNEL_3);
  HAL_TIM_IC_Start(&htim20, TIM_CHANNEL_4);
//
//  HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
//  HAL_ADC_Start_DMA(&hadc1, ADC_RawRead, 2);
  p1_timeStamp = HAL_GetTick();
  p2_timeStamp = HAL_GetTick();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  if(modBusTimeStamp < HAL_GetTick()){
		  registerFrame[0x00].U16 = 22881;
		  sendall();
		  modBusTimeStamp += 200;
	  }


	  QEIReadRaw = __HAL_TIM_GET_COUNTER(&htim1);
	  QEI_raw = QEIReadRaw;
	  QEIdata.QEIRead[0] = QEIReadRaw;

	  Modbus_Protocal_Worker();
	  is_motor_should_run();
	  readLimit();
	  changeUnit();

	  linearPos = QEI_mm;

	  Emer = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7);
	  tickk = HAL_GetTick();

	  if(Emer == 0){
		  readLead();
		  motor_run(0, 3);
//		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
//		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0);
		  registerFrame[0x10].U16 = 0;
		  modeSelection = 0;
		  jogModeState = goPick;
		  currentOrder = 0;
	  }
	  else{
		  readLead();
		  remote_recieve();
		  watch_mode();
		  go_point();
//		  z_axis_control_by_remote();

		  if(home_trigger == 1){
			  if(home_timeStamp < HAL_GetTick()){
		  		__HAL_TIM_SET_COUNTER(&htim1, 0);
		  		QEIReadRaw = 0;
		  		home_trigger = 0;
		  		xAxisPosition = 0;
		  		zMovingStatus = 0;
		  		home_trig = 0;

		  		p1Off();
		  		p2Off();
			  }
		  }
		  if(pointMode_timeTrig == 1){
			  if(pointMode_timeStamp < HAL_GetTick()){
				  pointMode_timeTrig = 0;
				  zMovingStatus = 0;
				  goalPointZ = 0;
			  }
		  }

		  if(trajec_target >= 0 && trajec_state == 0){
		  		QEI_start = QEI_mm;
		  }
		  Trajectory();
		  HomemadePID();
		  speedread();
		  accelread();
//		  if(p1_timeStamp < tickk){
//		  		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0);
//		  		p1_timeStamp = tickk + 1000;
//		  	}
//		  	else if(p1_timeStamp > tickk){
//		  		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1);
//		  	}



		  zActualSpeed = speed;
		  zAccel = acc;

	  }
//	  init_motor_cal();
//	  remote_recieve();
//	  watch_mode();
	  abbs = QEIdata.QEIRead[0] - QEIdata.QEIRead[1];
	  if(abbs > 32767)
//		  abbs -= 65535;
	  	  __HAL_TIM_SET_COUNTER(&htim1, QEIReadRaw - 65535);
	  if(abbs < -32767)
//		  abbs += 65535;
	  	  __HAL_TIM_SET_COUNTER(&htim1, QEIReadRaw - 65535);

	  QEIdata.QEIRead[1] = QEIdata.QEIRead[0];
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI12;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 2;
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 2;
  if (HAL_TIM_Encoder_Init(&htim1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 169;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 4294967295;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_SlaveConfigTypeDef sSlaveConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 169;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 65535;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sSlaveConfig.SlaveMode = TIM_SLAVEMODE_RESET;
  sSlaveConfig.InputTrigger = TIM_TS_TI1FP1;
  sSlaveConfig.TriggerPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sSlaveConfig.TriggerFilter = 0;
  if (HAL_TIM_SlaveConfigSynchro(&htim3, &sSlaveConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim3, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
  sConfigIC.ICSelection = TIM_ICSELECTION_INDIRECTTI;
  if (HAL_TIM_IC_ConfigChannel(&htim3, &sConfigIC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_SlaveConfigTypeDef sSlaveConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 169;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 65535;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sSlaveConfig.SlaveMode = TIM_SLAVEMODE_RESET;
  sSlaveConfig.InputTrigger = TIM_TS_TI1FP1;
  sSlaveConfig.TriggerPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sSlaveConfig.TriggerFilter = 0;
  if (HAL_TIM_SlaveConfigSynchro(&htim4, &sSlaveConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim4, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
  sConfigIC.ICSelection = TIM_ICSELECTION_INDIRECTTI;
  if (HAL_TIM_IC_ConfigChannel(&htim4, &sConfigIC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief TIM5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM5_Init(void)
{

  /* USER CODE BEGIN TIM5_Init 0 */

  /* USER CODE END TIM5_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM5_Init 1 */

  /* USER CODE END TIM5_Init 1 */
  htim5.Instance = TIM5;
  htim5.Init.Prescaler = 3;
  htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim5.Init.Period = 29999;
  htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim5) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim5, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim5) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM5_Init 2 */

  /* USER CODE END TIM5_Init 2 */
  HAL_TIM_MspPostInit(&htim5);

}

/**
  * @brief TIM8 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM8_Init(void)
{

  /* USER CODE BEGIN TIM8_Init 0 */

  /* USER CODE END TIM8_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_SlaveConfigTypeDef sSlaveConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM8_Init 1 */

  /* USER CODE END TIM8_Init 1 */
  htim8.Instance = TIM8;
  htim8.Init.Prescaler = 169;
  htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim8.Init.Period = 65535;
  htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim8.Init.RepetitionCounter = 0;
  htim8.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim8) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim8, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_Init(&htim8) != HAL_OK)
  {
    Error_Handler();
  }
  sSlaveConfig.SlaveMode = TIM_SLAVEMODE_RESET;
  sSlaveConfig.InputTrigger = TIM_TS_TI1FP1;
  sSlaveConfig.TriggerPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sSlaveConfig.TriggerFilter = 0;
  if (HAL_TIM_SlaveConfigSynchro(&htim8, &sSlaveConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim8, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim8, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
  sConfigIC.ICSelection = TIM_ICSELECTION_INDIRECTTI;
  if (HAL_TIM_IC_ConfigChannel(&htim8, &sConfigIC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  if (HAL_TIM_IC_ConfigChannel(&htim8, &sConfigIC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
  sConfigIC.ICSelection = TIM_ICSELECTION_INDIRECTTI;
  if (HAL_TIM_IC_ConfigChannel(&htim8, &sConfigIC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM8_Init 2 */

  /* USER CODE END TIM8_Init 2 */

}

/**
  * @brief TIM16 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM16_Init(void)
{

  /* USER CODE BEGIN TIM16_Init 0 */

  /* USER CODE END TIM16_Init 0 */

  /* USER CODE BEGIN TIM16_Init 1 */

  /* USER CODE END TIM16_Init 1 */
  htim16.Instance = TIM16;
  htim16.Init.Prescaler = 169;
  htim16.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim16.Init.Period = 1145;
  htim16.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim16.Init.RepetitionCounter = 0;
  htim16.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim16) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_OnePulse_Init(&htim16, TIM_OPMODE_SINGLE) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM16_Init 2 */

  /* USER CODE END TIM16_Init 2 */

}

/**
  * @brief TIM20 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM20_Init(void)
{

  /* USER CODE BEGIN TIM20_Init 0 */

  /* USER CODE END TIM20_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_SlaveConfigTypeDef sSlaveConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM20_Init 1 */

  /* USER CODE END TIM20_Init 1 */
  htim20.Instance = TIM20;
  htim20.Init.Prescaler = 169;
  htim20.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim20.Init.Period = 65535;
  htim20.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim20.Init.RepetitionCounter = 0;
  htim20.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim20) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim20, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_Init(&htim20) != HAL_OK)
  {
    Error_Handler();
  }
  sSlaveConfig.SlaveMode = TIM_SLAVEMODE_RESET;
  sSlaveConfig.InputTrigger = TIM_TS_TI1FP1;
  sSlaveConfig.TriggerPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sSlaveConfig.TriggerFilter = 0;
  if (HAL_TIM_SlaveConfigSynchro(&htim20, &sSlaveConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim20, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim20, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
  sConfigIC.ICSelection = TIM_ICSELECTION_INDIRECTTI;
  if (HAL_TIM_IC_ConfigChannel(&htim20, &sConfigIC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  if (HAL_TIM_IC_ConfigChannel(&htim20, &sConfigIC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
  sConfigIC.ICSelection = TIM_ICSELECTION_INDIRECTTI;
  if (HAL_TIM_IC_ConfigChannel(&htim20, &sConfigIC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM20_Init 2 */

  /* USER CODE END TIM20_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 19200;
  huart2.Init.WordLength = UART_WORDLENGTH_9B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_EVEN;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart2, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart2, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMAMUX1_CLK_ENABLE();
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
  /* DMA1_Channel2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIOUT_PushPull_Pin|GPIOUT_Vacuum_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIOUT_Pilot2_Pin|GPIOUT_DrivINA_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIOUT_Pilot1_Pin|GPIOUT_DrivINB_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : GPIOUT_PushPull_Pin GPIOUT_Vacuum_Pin */
  GPIO_InitStruct.Pin = GPIOUT_PushPull_Pin|GPIOUT_Vacuum_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : GPIOUT_Pilot2_Pin GPIOUT_DrivINA_Pin */
  GPIO_InitStruct.Pin = GPIOUT_Pilot2_Pin|GPIOUT_DrivINA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : GPIOIN_LeadMax_Pin GPIOIN_LeadMin_Pin */
  GPIO_InitStruct.Pin = GPIOIN_LeadMax_Pin|GPIOIN_LeadMin_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : GPIOUT_Pilot1_Pin GPIOUT_DrivINB_Pin */
  GPIO_InitStruct.Pin = GPIOUT_Pilot1_Pin|GPIOUT_DrivINB_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : GPIOIN_LimitMin_Pin GPIOIN_LimitMax_Pin */
  GPIO_InitStruct.Pin = GPIOIN_LimitMin_Pin|GPIOIN_LimitMax_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : GPIOIN_Emer_Pin */
  GPIO_InitStruct.Pin = GPIOIN_Emer_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOIN_Emer_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
//    if (htim == &htim2) {
//        registerFrame[0x00].U16 = 22881;
//        sendall();
//    }
//}

void motor_run(uint64_t pwm, uint8_t dir){
	is_motor_should_run();
	if(dir == 1){
		if(isMotorCanMoveUp == 1){
			usePWM = pwm;
			__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_2, usePWM);
			motoring = 1;
//			motor_moveup();
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7,GPIO_PIN_SET);
//			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
//			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1);
		}
		else if(isMotorCanMoveUp == 0){
			gopoint_act = 0;
			__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_2, usePWM);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7,GPIO_PIN_RESET);
		}
	}
	else if(dir == 2){
		if(isMotorCanMoveDown == 1){
			usePWM = pwm;
			__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_2, usePWM);
			motoring = 2;
//			motor_movedown();
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7,GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0);
//			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);
		}
		else if(isMotorCanMoveDown == 0){
			__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_2, usePWM);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7,GPIO_PIN_RESET);
		}
	}
	else if(dir == 3){
		if(modeSelection != 2){
			usePWM = 30000;
			__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_2, usePWM);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7,GPIO_PIN_RESET);
			motoring = 3;
		}
		if(modeSelection == 2){
			usePWM = 0;
			motoring = 4;
		}
	}
//	else{
//		usePWM = 0;
//		__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_2, usePWM);
//		motoring = 0;
//	}
}

void remote_recieve(){
	JoyxPosition_Rise = __HAL_TIM_GET_COMPARE(&htim8,TIM_CHANNEL_1);
	JoyxPosition_Fall = __HAL_TIM_GET_COMPARE(&htim8,TIM_CHANNEL_2);
	JoyxPosition_dt = JoyxPosition_Rise - JoyxPosition_Fall;
	if(JoyxPosition_Rise > JoyxPosition_Fall)
		JoyxPosition = JoyxPosition_dt + 19999 ;
	else
		JoyxPosition = JoyxPosition_dt;

	zUp_Rise = __HAL_TIM_GET_COMPARE(&htim8,TIM_CHANNEL_3);
	zUp_Fall = __HAL_TIM_GET_COMPARE(&htim8,TIM_CHANNEL_4);
	zUp_dt = zUp_Rise - zUp_Fall;
	if(zUp_Rise>zUp_Fall)
		zUp = zUp_dt + 19999 ;
	else
		zUp = zUp_dt;

	zDown_Rise = __HAL_TIM_GET_COMPARE(&htim20,TIM_CHANNEL_3);
	zDown_Fall = __HAL_TIM_GET_COMPARE(&htim20,TIM_CHANNEL_4);
	zDown_dt = zDown_Rise - zDown_Fall;
	if(zDown_Rise>zDown_Fall)
		zDown = zDown_dt + 19999 ;
	else
		zDown = zDown_dt;


	joySel1_Rise = __HAL_TIM_GET_COMPARE(&htim4,TIM_CHANNEL_1);
	joySel1_Fall = __HAL_TIM_GET_COMPARE(&htim4,TIM_CHANNEL_2);
	joySel1_dt = joySel1_Rise - joySel1_Fall;
	if(joySel1_Rise > joySel1_Fall)
		joySel1 = joySel1_dt + 19999 ;
	else
		joySel1 = joySel1_dt;

	joySel2_Rise = __HAL_TIM_GET_COMPARE(&htim20,TIM_CHANNEL_1);
	joySel2_Fall = __HAL_TIM_GET_COMPARE(&htim20,TIM_CHANNEL_2);
	joySel2_dt = joySel2_Rise - joySel2_Fall;
	if(joySel2_Rise > joySel2_Fall)
		joySel2 = joySel2_dt + 19999 ;
	else
		joySel2 = joySel2_dt;

	joySave_Rise = __HAL_TIM_GET_COMPARE(&htim3,TIM_CHANNEL_1);
	joySave_Fall = __HAL_TIM_GET_COMPARE(&htim3,TIM_CHANNEL_2);
	joySave_dt = joySave_Rise - joySave_Fall;
	if(joySave_Rise > joySave_Fall)
		joySave = joySave_dt + 19999 ;
	else
		joySave = joySave_dt;



	if(modeSelection  == 0 || modeSelection == 4){
		if(zUp < -2000 && zUp > -2010){
			p1Blink();
			p2Off();
			remoteCheck = 1;
			motor_run(9000, 1);
			if(goPoint_times  < HAL_GetTick()){
				goPointgoal = linearPos + 1;
				goPoint_times = HAL_GetTick() + 10;
			}
			gopoint_act = 1;
//			trajec_target = linearPos + 10;
		}
		else if(zDown > 38000 && zDown < 38800){
			p2Blink();
			p1Off();
			remoteCheck = 2;
			motor_run(7500, 2);
		}
		else{
			motor_run(0, 3);
			remoteCheck = 0;
		}

		if(JoyxPosition < 38100){
			if(JoyxPosition_timestamp < HAL_GetTick() && xAxisPosition < 100){
				xAxisPosition += 1;
				JoyxPosition_timestamp = HAL_GetTick() + 20;
			}
		}
		else if(JoyxPosition > 39000 && xAxisPosition > -100){
			if(JoyxPosition_timestamp < HAL_GetTick()){
				xAxisPosition -= 1;
				JoyxPosition_timestamp = HAL_GetTick() + 20;
			}
		}
	}

	if(joySel1 > 39000 && joySel1 < 40000){
		if(joySel2 > 39000) ShelvesSelect = 1;
		else  if(joySel2 > 38500 && joySel2 < 39000) ShelvesSelect = 2;
		else if(joySel2 > 38000 && joySel2 < 38100) ShelvesSelect = 3;
	}
	else if(joySel1 > 38000 && joySel1 < 39000){
		if(joySel2 > 38000 && joySel2 < 38100) ShelvesSelect = 4;
		else  if(joySel2 > 38500 && joySel2 < 39000) ShelvesSelect = 5;
		else if(joySel2 > 39000) ShelvesSelect = 6;
	}
}

int go_point(){
	if(goPoint_trig == 1){
		if(linearPos >= goPointgoal){
			motor_run(0, 3);
			goPoint_trig = 0;
			gopoint_act = 0;
			return 4;
		}
	}
	if(goPoint_trig == 2){
		if(linearPos <= goPointgoal){
			motor_run(0, 3);
			goPoint_trig = 0;
			gopoint_act = 0;
			return 4;
		}
	}

	if(gopoint_act == 1){
		if(linearPos < goPointgoal){
			motor_run(10000, 1);
			goPoint_trig = 1;
			jog_goPoint_actt = 1;
		}
		else if(linearPos > goPointgoal){
			motor_run(7200, 2);
			goPoint_trig = 2;
			jog_goPoint_actt = 1;
		}
	}
}

void speedread(){
	static uint32_t Timestamp = 0;
	if (Timestamp < __HAL_TIM_GET_COUNTER(&htim2)) {
		Timestamp = __HAL_TIM_GET_COUNTER(&htim2) + 10000;
		QEI_raw = __HAL_TIM_GET_COUNTER(&htim1);
		changeUnit();
		tim_velo_new = __HAL_TIM_GET_COUNTER(&htim2);
		dt_velo = (tim_velo_new - tim_velo_last)/1000000.0;
		speed = (QEI_mm - LastPos)/dt_velo;

		LastPos = QEI_mm;
		tim_velo_last = tim_velo_new;
	}
}

void accelread(){
	static uint32_t TimesTamp = 0;
	if (TimesTamp < __HAL_TIM_GET_COUNTER(&htim2)) {
		TimesTamp = __HAL_TIM_GET_COUNTER(&htim2) + 40000;

		tim_acc_new = __HAL_TIM_GET_COUNTER(&htim2);
		velo_new = speed;
		dt_acc = (tim_acc_new - tim_acc_last)/1000000.0;
		acc = (velo_new - velo_last)/dt_acc;

		velo_last = velo_new;
		tim_acc_last = tim_acc_new;
	}
}

void changeUnit(){
	QEI_mm = (QEI_raw/8192.0)*25.326*pi;
}

void HomemadePID(){
//	Now Lastime error errorsum kp ki kd Iterm dinput Lasterror
	set_point = traj[0];
	static uint32_t timestamp = 0;
	if (timestamp < __HAL_TIM_GET_COUNTER(&htim2)) {
		timestamp = __HAL_TIM_GET_COUNTER(&htim2) + 1000;
		Now = __HAL_TIM_GET_COUNTER(&htim2);
		error = set_point - QEI_mm;
		finish_state = 0;

		if(error < 2 && error > -2){
			errorsum = 0;
			finish_state = 1;
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15,0);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7,0);
			__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_2,30000);
		} else if(error < 11 && error > -11){
			errorsum += 15;
		}

		if(error > 32768)
			error -= 65536;
		if(error < -32768)
			error += 65536;

		if(error > 0){
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15,0);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7,1);
			errorsum = errorsum + (error*(Now-Lastime)/10000);
			Iterm = ki*errorsum;
			if(Iterm > 65535){
				errorsum = (Iterm/ki) - (error*(Now-Lastime));
			}
			dinput = (error-Lasterror)/(Now-Lastime);
			if(errorsum < 0){
				errorsum = errorsum*-1;
			}
			Vfeedback = (kp*error)+(ki*errorsum)+(kd*dinput);
			if(Vfeedback > 65536){
				Vfeedback = 65536;
			}

			PWMset = (Vfeedback/65536.0)*30000;
		}
		else if(error < 0){
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15,1);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7,0);
			error = error*(-1);

//			if(t < Time_acc_tri){
//				PWMset = 8000;
//			} else{
				errorsum = errorsum + (error*(Now-Lastime)/10000);
				Iterm = ki*errorsum;
				if(Iterm > 65535){
					errorsum = (Iterm/ki) - (error*(Now-Lastime));
				}
				dinput = (error-Lasterror)/(Now-Lastime);
				if(errorsum < 0){
					errorsum = errorsum*-1;
				}
				Vfeedback = (kp*error)+(ki*errorsum)+(kd*dinput);
				if(Vfeedback > 65536){
					Vfeedback = 65536;
				}

				PWMset = (Vfeedback/65536.0)*30000;
				if(PWMset > 8000){
					PWMset = 8000;
				}
//				PWMset = 4000;
//			}
		}
		else if(error == 0){
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15,0);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7,0);
		}

		__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_2, PWMset);

		Lastime = Now;
		Lasterror = error;
	}
}

void Trajectory(){
	Distance = trajec_target - QEI_start;
	Time_acc = Vmax / Amax;
	Time_dec = Time_acc;


	time_now = __HAL_TIM_GET_COUNTER(&htim2);

	if(trajec_target >= 0 && trajec_state == 0){
		trajec_state = 1;
		Timestamp = time_now;
		QEI_start = QEI_mm;
		pos = QEI_start;
	}
	else if(Distance > 0 && trajec_state == 1){	//Run Up
		kp = 900;
		ki = 7;
		kd = 1;
		Distance_Velo_Max = -(Vmax*Time_acc) + Distance ;
		t = (time_now - Timestamp)/1000000.0;  //s
		if(Distance_Velo_Max > 0){						//Trapezoi
			temp_check = 1;
			Time_const = Distance_Velo_Max/Vmax;
			if(t < Time_acc){
				traj[2] = Amax;
				traj[1] = Amax*t;
				traj[0] = (Amax/2.0)*t*t + pos;
				temp_pos_acc = traj[0];
			}
			else if(t < Time_const+Time_acc){
				traj[2] = 0;
				traj[1] = Vmax;
				traj[0] = (Vmax*(t-Time_acc)) + temp_pos_acc;
				temp_pos_const = traj[0];
			}
			else if(t < Time_const+Time_acc+Time_dec){
				traj[2] = -Amax;
				traj[1] = (traj[2]*(t-Time_const-Time_acc)) + Vmax;
				traj[0] = ((Amax/2)*(t-Time_const-Time_acc)*(t-Time_const-Time_acc))+(traj[1]*(t-Time_const-Time_acc))+temp_pos_const;
			}
			else{
				trajec_state = 0;
				trajec_target = -10;
				traj[2] = 0;
				temp_pos_acc = 0;
				temp_pos_const = 0;
			}
		}
		else if(Distance_Velo_Max <= 0){				//Triangle
			temp_check = 2;
			Time_acc_tri = sqrt(Distance/Amax);
			if(t < Time_acc_tri){
				traj[2] = Amax;
				traj[1] = Amax*t;
				traj[0] = (Amax/2.0)*t*t + pos;
				temp_pos_acc = traj[0];
				temp_v_acc = traj[1];
			}
			else if(t < Time_acc_tri*2){
				traj[2] = -Amax;
				traj[1] = temp_v_acc - (Amax*(t-Time_acc_tri));
				traj[0] = ((Amax/2.0)*(t-Time_acc_tri)*(t-Time_acc_tri))+(traj[1]*(t-Time_acc_tri))+temp_pos_acc;
			}
			else{
				trajec_state = 0;
				trajec_target = -10;
				traj[2] = 0;
				Time_acc_tri = 0;
				temp_pos_acc = 0;
				temp_v_acc = 0;
			}
		}
	}
	else if(Distance < 0 && trajec_state == 1){        		// Run Down
		kp = 900;
		ki = 10;
		kd = 0;
		Distance_Velo_Max = (Vmax*Time_acc) + Distance ;
		t = (time_now - Timestamp)/1000000.0;  //s
		if(Distance_Velo_Max < 0){							//Trapezoi
			temp_check = 3;
			Time_const = Distance_Velo_Max/Vmax;
			if(t < Time_acc){
				traj[2] = -Amax;
				traj[1] = -Amax*t;
				traj[0] = (-Amax/2.0)*t*t + pos;
				temp_pos_acc = traj[0];
			}
			else if(t < Time_const+Time_acc){
				traj[2] = 0;
				traj[1] = -Vmax;
				traj[0] = (-Vmax*(t-Time_acc)) + temp_pos_acc;
				temp_pos_const = traj[0];
			}
			else if(t < Time_const+Time_acc+Time_dec){
				traj[2] = Amax;
				traj[1] = (traj[2]*(t-Time_const-Time_acc)) - Vmax;
				traj[0] = ((Amax/2)*(t-Time_const-Time_acc)*(t-Time_const-Time_acc))+(traj[1]*(t-Time_const-Time_acc))+temp_pos_const;
			}
			else{
				trajec_state = 0;
				trajec_target = -10;
				traj[2] = 0;
				temp_pos_acc = 0;
				temp_pos_const = 0;
			}
		}
		else if(Distance_Velo_Max >= 0){					//Triangle
			temp_check = 4;
			Time_acc_tri = sqrt(-Distance/Amax);
			if(t < Time_acc_tri){
				traj[2] = -Amax;
				traj[1] = -Amax*t;
				traj[0] = (-Amax/2.0)*t*t + pos;
				temp_pos_acc = traj[0];
				temp_v_acc = traj[1];
			}
			else if(t < Time_acc_tri*2){
				traj[2] = Amax;
				traj[1] = temp_v_acc + (Amax*(t-Time_acc_tri));
				traj[0] = ((-Amax/2.0)*(t-Time_acc_tri)*(t-Time_acc_tri))+(traj[1]*(t-Time_acc_tri))+temp_pos_acc;
			}
			else{
				trajec_state = 0;
				trajec_target = -10;
				traj[2] = 0;
				Time_acc_tri = 0;
				temp_pos_acc = 0;
				temp_v_acc = 0;
			}
		}
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
