#+---------------------------------------------------------------------------
#
# Copyright (c) 2011 Alexey Dyachenko <alexd@inbox.ru>
#
# Makefile template for STM32 base project
#

TOPDIR = ../../..

BOARD	= STM3210C
USE_STM_PERIF_LIB = 1
#RTOS = scmRTOS
START_FROM_RAM = 1

TARGET		= DisplayTest
OPTIMIZE	= -O2

#PROJECT_SRC = src
PROJECT_FLAGS = -ggdb
PROJECT_LDFLAGS = -nostartfiles -nostdlib
#PROJECT_CWARNINGS =
#PROJECT_CXXWARNINGS =

SRCS	+= stm3210c_eval_lcd.c stm3210c_eval_ioe.c

# use small printf 
SRCS += printf-stdarg.c


include $(TOPDIR)/Makefile.common
