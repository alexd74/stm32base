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

TOPDIR = ../..

OPTIMIZE	= -O2

BOARD	= DISCOVERY_F4
USE_STM_PERIF_LIB = 1
#RTOS = scmRTOS
#START_FROM_RAM = 1
#HARD_FLOAT = 1

TARGET		= test

ifdef HARD_FLOAT
	LIBRARY = STM32F4xx_StdPeriphLibHard.a
else
	LIBRARY = STM32F4xx_StdPeriphLibSoft.a
endif

PROJECT_SRC = src
PROJECT_FLAGS = -ggdb
#PROJECT_LDFLAGS = -nostartfiles -nostdlib
#PROJECT_CWARNINGS =
#PROJECT_CXXWARNINGS =

all : dirs lib

include $(TOPDIR)/Makefile.common
