# Copyright 2005 The Android Open Source Project

LOCAL_PATH:= $(call my-dir)


init_cflags += \
    -Wall -Wextra \
    -Wno-unused-parameter \


# If building on Linux, then build unit test for the host.
ifeq ($(HOST_OS),linux)
include $(CLEAR_VARS)
LOCAL_CFLAGS := $(init_cflags)
LOCAL_SRC_FILES:= \
    init.c \

LOCAL_MODULE := mint2g-init
LOCAL_CLANG := true
LOCAL_FORCE_STATIC_EXECUTABLE := true
LOCAL_MODULE_PATH := $(PRODUCT_OUT)

include $(BUILD_EXECUTABLE)