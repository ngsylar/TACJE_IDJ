#ifndef STATE_H
#define STATE_H

#include "GameObject.h"

class State {
    protected:
        bool debugMode, started, /*paused,*/ popRequested, quitRequested;
        std::vector<std::shared_ptr<GameObject>> objectArray;

        // // sylar's extra layer rendering
        // std::vector<std::weak_ptr<GameObject>> renderingArray;
        // bool scheduleLayerSort;
    
    public:
        State();
        virtual ~State();
        virtual void LoadAssets();
        virtual void StartBase();
        virtual void Start();
        virtual void UpdateBase(float dt);
        virtual void Update(float dt);
        virtual void RenderBase();
        virtual void Render();
        virtual void Pause();
        virtual void Resume();
        virtual std::weak_ptr<GameObject> AddObject(GameObject* object);
        virtual std::weak_ptr<GameObject> GetObjectPtr(GameObject* object);
        virtual std::weak_ptr<GameObject> GetObjectPtr(std::string label);
        virtual void RemoveObject(int objectId, int renderingId);
        void DetectCollisions();
        bool Debugging();
        // bool Started();
        // bool Paused();
        bool PopRequested();
        bool QuitRequested();
};

#endif