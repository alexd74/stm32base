#+---------------------------------------------------------------------------
#
# Copyright (c) 2011 Alexey Dyachenko <alexd@inbox.ru>
#
# Makefile template for STM32 base project
#

TOPDIR = ../..

OPTIMIZE	= -O2

MCU	= cortex-m3
ifndef CHIP
	CHIP = STM32F10X_LD_VL
endif
USE_STM_PERIF_LIB = 1

TARGET		= test

ifeq ($(CHIP),STM32F10X_LD_VL)
	LIBRARY = STM32F10x_StdPeriphLibVL.a
else
	LIBRARY = STM32F10x_StdPeriphLibCL.a
endif

PROJECT_SRC = src
PROJECT_FLAGS = -ggdb
#PROJECT_LDFLAGS = -nostartfiles -nostdlib
#PROJECT_CWARNINGS =
#PROJECT_CXXWARNINGS =

all : dirs lib

include $(TOPDIR)/Makefile.common
