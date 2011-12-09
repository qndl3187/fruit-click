#include "fruitclick-android.h"


AndroidPlatform::AndroidPlatform()
{
    FruitClick::Platform::set(this);
}

void AndroidPlatform::drawBeginImpl()
{
    g_env->CallVoidMethod(g_activity, beginID);
}

void AndroidPlatform::drawEndImpl()
{
    g_env->CallVoidMethod(g_activity, endID);
}

void AndroidPlatform::drawImpl(const FruitClick::Platform::Texture id, float x, float y, float angle)
{
    g_env->CallVoidMethod(g_activity, drawID, id, x, y, angle * TO_DEG);
}

void AndroidPlatform::drawTextImpl(const char* text, float x, float y)
{
    jstring javaString = g_env->NewStringUTF(text);
    g_env->CallVoidMethod(g_activity, drawTextID, javaString, x, y);
}

void AndroidPlatform::playSoundImpl(FruitClick::Platform::Sound id)
{
    g_env->CallVoidMethod(g_activity, playSoundID, id);
}

void AndroidPlatform::logImpl(const char* text)
{
    LOGI(text);
}

void setupEnv(JNIEnv* env, jobject thiz)
{
    g_env = env;
    g_activity = thiz;
    g_activityClass = env->GetObjectClass(thiz);

    beginID = env->GetMethodID(g_activityClass, "drawBegin", "()V");
    endID = env->GetMethodID(g_activityClass, "drawEnd", "()V");
    drawID = env->GetMethodID(g_activityClass, "draw", "(IFFF)V");
    drawTextID = env->GetMethodID(g_activityClass, "drawText", "(Ljava/lang/String;FF)V");
    playSoundID = env->GetMethodID(g_activityClass, "playSound", "(I)V");
}

void Java_com_fruitclick_Application_createNative(JNIEnv* env, jobject thiz)
{
    LOGI("Create");
    setupEnv(env, thiz);
    g_platform = new AndroidPlatform();
    g_app = new FruitClick::Application();
}

void Java_com_fruitclick_Application_renderNative(JNIEnv* env, jobject thiz)
{
    g_app->render();
}

void Java_com_fruitclick_Application_touchNative(JNIEnv* env, jobject thiz, jint x, jint y)
{
    LOGI("Touch");
    g_app->touch(x, y);
}

void Java_com_fruitclick_Application_disposeNative(JNIEnv* env, jobject thiz)
{
    LOGI("Destroy");
    delete g_app;
    delete g_platform;
}
