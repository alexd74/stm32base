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

BOARD	= STM3210C
USE_STM_PERIF_LIB = 1
#RTOS = scmRTOS
#START_FROM_RAM = 1

TARGET		= test
LIBRARY = STM32F10x_StdPeriphLib.a

PROJECT_SRC = src
PROJECT_FLAGS = -ggdb
#PROJECT_LDFLAGS = -nostartfiles -nostdlib
#PROJECT_CWARNINGS =
#PROJECT_CXXWARNINGS =

all : dirs lib

include $(TOPDIR)/Makefile.common
