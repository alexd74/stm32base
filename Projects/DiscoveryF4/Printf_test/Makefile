#+---------------------------------------------------------------------------
#
# Copyright (c) 2011 Alexey Dyachenko <alexd@inbox.ru>
#
# Makefile template for STM32 base project
#

TOPDIR = ../../..

#TOOL	= /opt/Sourcery_gcc/bin/arm-none-eabi-
#TOOL	= /opt/Sourcery_gcc-4.5.2/bin/arm-none-eabi-
#TOOL	= /opt/Sourcery_gcc-4.6.3/bin/arm-none-eabi-
#TOOL	= /opt/Sourcery_gcc-4.7.2/bin/arm-none-eabi-
#TOOL	= /opt/arm-none-eabi/bin/arm-none-eabi-

BOARD	= DISCOVERY_F4

USE_STM_PERIF_LIB = 1
#USE_USB = 1
#RTOS = FreeRTOS
START_FROM_RAM = 1
USART_RETARGET = MINI
#USART_RETARGET = NEWLIB

TARGET		= target
OPTIMIZE	= -O2

#PROJECT_SRC = src
PROJECT_FLAGS = -ggdb
PROJECT_LDFLAGS = -nostartfiles -nostdlib
#PROJECT_CWARNINGS =
#PROJECT_CXXWARNINGS =

#VPATH += $(TOPDIR)/Libraries/STM32_USB_Device_Library/Class/hid/src
#SRCS += usb_dcd_int.c usb_dcd.c usbd_core.c usbd_req.c usbd_ioreq.c usbd_hid_core.c

include $(TOPDIR)/Makefile.common
