#       Makefile for esunlib (EagleSun Extended Libraries to C)

ESUN_PLATFORM = ix86_Win32_gcc2
ESUN_ROOT = /c/opt/EagleSun
ESUN_INCLUDE_DIR = $(ESUN_ROOT)/include
ESUN_INCLUDE_SYS_DIR = $(ESUN_INCLUDE_DIR)/$(ESUN_PLATFORM)
ESUN_LIB_DIR = $(ESUN_ROOT)/lib/MinGW

LOCAL_INCLUDE_DIR = ../include
LOCAL_INCLUDE_SYS_DIR = $(LOCAL_INCLUDE_DIR)/$(ESUN_PLATFORM)

CC = gcc
INSTALL = install
MAKEDIR = install -d
CFLAGS = -O3 -I$(LOCAL_INCLUDE_DIR) -I$(LOCAL_INCLUDE_SYS_DIR)
LIBESUN = libesun.a

include Makefile.common

