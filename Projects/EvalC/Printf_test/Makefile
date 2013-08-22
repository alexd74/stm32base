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

BOARD	= STM3210C
#USE_STM_PERIF_LIB = 1
#USE_USB = 1
#RTOS = scmRTOS
START_FROM_RAM = 1
USART_RETARGET = MINI
#USART_RETARGET = NEWLIB

TARGET		= printf_test
OPTIMIZE	= -O2

#PROJECT_SRC = src
PROJECT_FLAGS = -ggdb
PROJECT_LDFLAGS = -nostartfiles -nostdlib
#PROJECT_CWARNINGS =
#PROJECT_CXXWARNINGS =

include $(TOPDIR)/Makefile.common
