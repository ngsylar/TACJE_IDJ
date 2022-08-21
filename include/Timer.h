#ifndef TIMER_H
#define TIMER_H

class Timer {
    private:
        float time;
    
    public:
        Timer();
        void Update(float dt);
        bool IsReady(float cooldown);
        void Restart();
        float Get();
};

#endif