#+---------------------------------------------------------------------------
#
# Copyright (c) 2011 Alexey Dyachenko <alexd@inbox.ru>
#
# Makefile template for STM32 base project
#

TOPDIR = ../../..

BOARD	= DISCOVERY_F4

USE_STM_PERIF_LIB = 1
USE_USB = 1
#RTOS = FreeRTOS
START_FROM_RAM = 1
#USART_RETARGET = MINI
#USART_RETARGET = NEWLIB
HARD_FLOAT = 1

TARGET		= Demonstration
OPTIMIZE	= -O2

#PROJECT_SRC = src
PROJECT_SRC = src 
PROJECT_INCLUDES = $(TOPDIR)/Libraries/STM32_USB_Device_Library/Class/hid/inc
PROJECT_FLAGS = -ggdb -DUSE_USB_OTG_FS=1
PROJECT_LDFLAGS = -nostartfiles -nostdlib
#PROJECT_CWARNINGS =
#PROJECT_CXXWARNINGS =

VPATH += $(TOPDIR)/Libraries/STM32_USB_Device_Library/Class/hid/src
SRCS += usb_dcd_int.c usb_dcd.c usbd_core.c usbd_req.c usbd_ioreq.c usbd_hid_core.c
SRCS += stm32f4_discovery_audio_codec.c stm32f4_discovery_lis302dl.c

include $(TOPDIR)/Makefile.common
