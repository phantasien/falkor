LOCAL_PATH := $(call my-dir)

# BASTIAN
include $(CLEAR_VARS)
LOCAL_MODULE    := bastian
LOCAL_SRC_FILES := $(BASTIAN_LIBS_PATH)/libbastian.a
include $(PREBUILT_STATIC_LIBRARY)

# Falkor test

include $(CLEAR_VARS)


LOCAL_MODULE := falkor-test
LOCAL_SRC_FILES := main.cc
LOCAL_C_INCLUDES += $(V8_HOME)/include
LOCAL_STATIC_LIBRARIES += bastian
LOCAL_WHOLE_STATIC_LIBRARIES := libstlport_static
LOCAL_LDLIBS := -llog
include $(BUILD_SHARED_LIBRARY)