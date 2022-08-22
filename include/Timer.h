#ifndef TIMER_H
#define TIMER_H

class Timer {
    private:
        float resetTime, currentTime;
    
    public:
        Timer(float resetTime=0.0f, float startTime=0.0f);
        void SetResetTime(float time);
        void Update(float dt);
        void Reset();
        float Get();
        bool IsOver();
        bool IsOver(float dt);
        bool HasReset();
        bool HasResetAndIsOver(float dt);
};

#endif