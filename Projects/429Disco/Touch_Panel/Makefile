#+---------------------------------------------------------------------------
#
# Copyright (c) 2011 Alexey Dyachenko <alexd@inbox.ru>
#
# Makefile template for STM32 base project
#

TOPDIR = ../../..

BOARD	= 429DISCO

USE_STM_PERIF_LIB = 1
#USE_USB = 1
#RTOS = FreeRTOS
START_FROM_RAM = 1
#USART_RETARGET = MINI
#USART_RETARGET = NEWLIB
HARD_FLOAT = 1

TARGET		= target
OPTIMIZE	= -O2

#PROJECT_SRC = src
PROJECT_SRC = src 
#PROJECT_INCLUDES = $(TOPDIR)/Libraries/STM32_USB_Device_Library/Class/hid/inc
PROJECT_FLAGS = -ggdb
PROJECT_LDFLAGS = -nostartfiles -nostdlib
#PROJECT_CWARNINGS =
#PROJECT_CXXWARNINGS =

SRCS += stm32f429i_discovery_lcd.c stm32f429i_discovery_sdram.c stm32f429i_discovery_ioe.c

include $(TOPDIR)/Makefile.common
