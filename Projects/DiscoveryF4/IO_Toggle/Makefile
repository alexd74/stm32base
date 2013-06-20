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

TOPDIR = ../../..

BOARD	= DISCOVERY_F4
USE_STM_PERIF_LIB = 1
#USE_USB = 1
#RTOS = FreeRTOS
START_FROM_RAM = 1

TARGET		= target
OPTIMIZE	= -O2

#PROJECT_SRC = src
#PROJECT_SRC = src 
#PROJECT_INCLUDES = $(TOPDIR)/Libraries/STM32_USB_Device_Library/Class/hid/inc
PROJECT_FLAGS = -ggdb 
PROJECT_LDFLAGS = -nostartfiles -nostdlib
#PROJECT_CWARNINGS =
#PROJECT_CXXWARNINGS =

#VPATH += $(TOPDIR)/Libraries/STM32_USB_Device_Library/Class/hid/src
#SRCS += usb_dcd_int.c usb_dcd.c usbd_core.c usbd_req.c usbd_ioreq.c usbd_hid_core.c

include $(TOPDIR)/Makefile.common
