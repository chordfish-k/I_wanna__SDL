#pragma once
#ifndef _TIMER_H_
#define _TIMER_H_

#include <SDL.h>
class LTimer
{
public:
    //Initializes variables
    LTimer();

    //����ʱ�Ӳ���
    void start();
    void stop();
    void pause();
    void unpause();

    //��ȡ��ʱ����ʱ��
    Uint32 getTicks();

    //��鶨ʱ����״̬
    bool isStarted();
    bool isPaused();

private:
    //��ʱ����ʼʱ��ʱ��
    Uint32 mStartTicks;

    //��ʱ����ͣʱ��ʱ��
    Uint32 mPausedTicks;

    //��ʱ��״̬
    bool mPaused;
    bool mStarted;
};


#endif