#+---------------------------------------------------------------------------
#
# Copyright (c) 2011 Alexey Dyachenko <alexd@inbox.ru>
#
# Makefile template for STM32 base project
#

TOPDIR = ../../..

#TOOL	= /opt/Sourcery_gcc/bin/arm-none-eabi-
#TOOL	= /opt/Sourcery_gcc-4.5.2/bin/arm-none-eabi-
#TOOL	= /opt/Sourcery_gcc-4.6.3/bin/arm-none-eabi-
#TOOL	= /opt/Sourcery_gcc-4.7.2/bin/arm-none-eabi-
#TOOL	= /opt/arm-none-eabi/bin/arm-none-eabi-

BOARD	= DISCOVERY_F4

USE_STM_PERIF_LIB = 1
#USE_USB = 1
#RTOS = FreeRTOS
START_FROM_RAM = 1
USART_RETARGET = MINI
#USART_RETARGET = NEWLIB
HARD_FLOAT = 1

TARGET		= target
OPTIMIZE	= -O2

#PROJECT_SRC = src
PROJECT_SRC = src 
#PROJECT_INCLUDES = $(TOPDIR)/Libraries/STM32_USB_Device_Library/Class/hid/inc
PROJECT_FLAGS = -ggdb
PROJECT_LDFLAGS = -nostartfiles
#PROJECT_WARNINGS = -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wredundant-decls -Wshadow -Wcast-qual -Wcast-align
#PROJECT_CWARNINGS =
#PROJECT_CXXWARNINGS =

include $(TOPDIR)/Makefile.common
