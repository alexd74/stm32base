#
# Copyright (c) 2011 Alexey Dyachenko <alexd@inbox.ru>
#
# Makefile template for STM32 base project
#

TOPDIR = ../../../..

#TOOL	= /opt/Sourcery_gcc/bin/arm-none-eabi-
#TOOL	= /opt/arm-kgp-eabi/bin/arm-kgp-eabi-
#TOOL	= /opt/arm-kgp-eabi.12/bin/arm-kgp-eabi-
#TOOL	= /opt/arm-none-eabi/bin/arm-none-eabi-


#BOARD	= DISCOVERY_VL
BOARD	= STM3210C

#USE_STM_PERIF_LIB = 1
RTOS = scmRTOS
START_FROM_RAM = 1

TARGET		= target
OPTIMIZE	= -O2

#PROJECT_SRC = src
PROJECT_FLAGS = -ggdb
#PROJECT_LDFLAGS = -nostartfiles
#PROJECT_LDFLAGS = -nostartfiles -nostdlib
#PROJECT_CWARNINGS =
#PROJECT_CXXWARNINGS =

include $(TOPDIR)/Makefile.common
