#+---------------------------------------------------------------------------
#
# Copyright (c) 2011 Alexey Dyachenko <alexd@inbox.ru>
#
# Makefile template for STM32 base project
#

TOPDIR = ../..

OPTIMIZE	= -O2

MCU	= cortex-m4
ifndef CHIP
	CHIP = STM32F429_439xx
endif
USE_STM_PERIF_LIB = 1

TARGET		= test

ifeq ($(CHIP),STM32F429_439xx)
	ifdef HARD_FLOAT
		LIBRARY = STM32F4xx_StdPeriphLibHard429.a
	else
		LIBRARY = STM32F4xx_StdPeriphLibSoft429.a
	endif
else
	ifdef HARD_FLOAT
		LIBRARY = STM32F4xx_StdPeriphLibHard40x.a
	else
		LIBRARY = STM32F4xx_StdPeriphLibSoft40x.a
	endif
endif

PROJECT_SRC = src
PROJECT_FLAGS = -ggdb -DHSE_VALUE=8000000
#PROJECT_LDFLAGS = -nostartfiles -nostdlib
#PROJECT_CWARNINGS =
#PROJECT_CXXWARNINGS =

all : dirs lib

include $(TOPDIR)/Makefile.common
