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
#USART_RETARGET = MINI
USART_RETARGET = NEWLIB
STACK_SIZE = 0x300
#HEAP_SIZE = 5K

TARGET		= new_test
OPTIMIZE	= -O2

PROJECT_SRC = src
PROJECT_FLAGS = -ggdb
PROJECT_LDFLAGS = -nostartfiles -nostdlib
#PROJECT_CWARNINGS =
#PROJECT_CXXWARNINGS =

SRCS	+= new.c

# use small printf 
#SRCS += printf-stdarg.c


include $(TOPDIR)/Makefile.common
