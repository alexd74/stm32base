#+---------------------------------------------------------------------------
#
# Copyright (c) 2011 Alexey Dyachenko <alexd@inbox.ru>
#
# Makefile template for STM32 base project
#

TOPDIR = ../..

OPTIMIZE	= -O2

BOARD	= STM3210C
#BOARD	= DISCOVERY_VL
USE_STM_PERIF_LIB = 1
#RTOS = scmRTOS
#START_FROM_RAM = 1

TARGET		= test

LIBRARY = STM32F10x_StdPeriphLibCL.a
#LIBRARY = STM32F10x_StdPeriphLibVL.a

PROJECT_SRC = src
PROJECT_FLAGS = -ggdb
#PROJECT_LDFLAGS = -nostartfiles -nostdlib
#PROJECT_CWARNINGS =
#PROJECT_CXXWARNINGS =

all : dirs lib

include $(TOPDIR)/Makefile.common
