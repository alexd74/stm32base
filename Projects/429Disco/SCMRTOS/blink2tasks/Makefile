#+---------------------------------------------------------------------------
#
# Copyright (c) 2011 Alexey Dyachenko <alexd@inbox.ru>
#
# Makefile template for STM32 base project
#

TOPDIR = ../../../..

BOARD	= 429DISCO
#USE_STM_PERIF_LIB = 1
RTOS = scmRTOS
START_FROM_RAM = 1
#USART_RETARGET = 1
#HARD_FLOAT = 1

TARGET		= target
OPTIMIZE	= -O2

#PROJECT_SRC = src
PROJECT_FLAGS = -ggdb
PROJECT_LDFLAGS = -nostartfiles -nostdlib
#PROJECT_CWARNINGS =
#PROJECT_CXXWARNINGS =

include $(TOPDIR)/Makefile.common
