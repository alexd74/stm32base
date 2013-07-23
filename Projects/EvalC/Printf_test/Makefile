#+---------------------------------------------------------------------------
#
#  Copyright (c) 2010 Anton Gusev aka AHTOXA (HTTP://AHTOXA.NET)
#
#  File:       Makefile
#
#  Contents:   makefile to build arm Cortex-M3 software with gcc
#
#----------------------------------------------------------------------------

#############  program name

TOPDIR = ../../..

BOARD	= STM3210C
USE_STM_PERIF_LIB = 1
#USE_USB = 1
#RTOS = scmRTOS
START_FROM_RAM = 1
USART_RETARGET = 1

TARGET		= printf_test
OPTIMIZE	= -O2

#PROJECT_SRC = src
PROJECT_FLAGS = -ggdb
PROJECT_LDFLAGS = -nostartfiles -nostdlib
#PROJECT_CWARNINGS =
#PROJECT_CXXWARNINGS =

include $(TOPDIR)/Makefile.common
