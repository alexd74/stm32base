#+---------------------------------------------------------------------------
#
# Copyright (c) 2011 Alexey Dyachenko <alexd@inbox.ru>
#
# Makefile template for STM32 base project
#

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
