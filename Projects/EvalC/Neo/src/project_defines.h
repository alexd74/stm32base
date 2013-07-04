/**
  ******************************************************************************
  * @file    project_defines.h
  * @author  WNT
  * @version 1.0
  * @date    02/12/2010
  * @brief   project specific definitions
  ******************************************************************************
  */

#ifndef PROJECT_DEFINES_H
#define PROJECT_DEFINES_H

/* retarget c lib io functions to usart */
#define USART_RETARGET_CLIB_IO

/* enable irq driver */
#define USART_USE_IRQ

/* use Ringpuffer or double buffer */
#define USART_USE_RINGBUFFER

#define DONT_USE_SYSTICK_TIMER

/* disable funktions of usart_io */
// #define USART_IO_DISABLE

/* enable debug output */
//#define DEBUG_OUTPUT

/* adapt to Keil evaluation board */
//#define BOARD_MCBSTM32C

/* adapt to CCM , opposite: EVAL BOARD */
//#define BOARD_CCM

/* define slave as processing unit application */
//#define MS_APP_DEFINE_TU

/* enable bootloader function */
//#define USE_BOOTLOADER


/* enable satellite i2c interface 0 */
//#define USE_I2C_INTERFACE_0
/* enable satellite i2c interface 1 */
//#define USE_I2C_INTERFACE_1
/* enable satellite i2c interface 2 */
//#define USE_I2C_INTERFACE_2

//#define SENSOR_TASK_CYCLIC_RUN_TIME 2

#endif
