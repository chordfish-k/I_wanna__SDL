#pragma once
#ifndef _TIMER_H_
#define _TIMER_H_

#include <SDL.h>
class LTimer
{
public:
    //Initializes variables
    LTimer();

    //各种时钟操作
    void start();
    void stop();
    void pause();
    void unpause();

    //获取定时器的时间
    Uint32 getTicks();

    //检查定时器的状态
    bool isStarted();
    bool isPaused();

private:
    //定时器开始时的时间
    Uint32 mStartTicks;

    //定时器暂停时的时间
    Uint32 mPausedTicks;

    //定时器状态
    bool mPaused;
    bool mStarted;
};


#endif