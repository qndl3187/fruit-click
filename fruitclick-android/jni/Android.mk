LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := libgdx
LOCAL_SRC_FILES := libgdx.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libandroidgl20
LOCAL_SRC_FILES := libandroidgl20.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := fruitclick
LOCAL_SRC_FILES += fruitclick-android.cpp
LOCAL_C_INCLUDES += ../../fruitclick
LOCAL_SRC_FILES += $(shell find ../../fruitclick/ -name '*.cpp')
LOCAL_LDLIBS := -llog
include $(BUILD_SHARED_LIBRARY)
