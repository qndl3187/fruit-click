#ifndef FRUITCLICK_ANDROID_H
#define FRUITCLICK_ANDROID_H

#include <string.h>
#include <jni.h>
#include <android/log.h>
#include "platform.h"
#include "application.h"

#define  LOG_TAG    "hellojni"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_FATAL,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

extern "C" {

class AndroidPlatform : public FruitClick::Platform
{
public:
    AndroidPlatform();

protected:
    virtual void drawBeginImpl();
    virtual void drawEndImpl();
    virtual void drawImpl(FruitClick::Platform::Texture id, float x, float y, float angle);
    virtual void drawTextImpl(const char* text, float x, float y);
    virtual void playSoundImpl(FruitClick::Platform::Sound id);
    virtual void logImpl(const char* text);
};

FruitClick::Application* g_app;
AndroidPlatform* g_platform;
JNIEnv* g_env;
jclass g_activityClass;
jobject g_activity;

jmethodID beginID;
jmethodID drawTextID;
jmethodID drawID;
jmethodID endID;
jmethodID playSoundID;

void Java_com_fruitclick_Application_createNative(JNIEnv* env, jobject thiz);
void Java_com_fruitclick_Application_renderNative(JNIEnv* env, jobject thiz);
void Java_com_fruitclick_Application_touchNative(JNIEnv* env, jobject thiz, jint x, jint y);
void Java_com_fruitclick_Application_disposeNative(JNIEnv* env, jobject thiz);
void setupEnv(JNIEnv* env, jobject thiz);

}

#endif
