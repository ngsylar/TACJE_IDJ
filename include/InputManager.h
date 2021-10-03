#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <unordered_map>

#define INCLUDE_SDL
#include "SDL_include.h"

#define LEFT_MOUSE_BUTTON   SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON  SDL_BUTTON_RIGHT
#define UP_ARROW_KEY        SDLK_UP
#define DOWN_ARROW_KEY      SDLK_DOWN
#define LEFT_ARROW_KEY      SDLK_LEFT
#define RIGHT_ARROW_KEY     SDLK_RIGHT
#define SPACE_KEY           SDLK_SPACE
#define ESCAPE_KEY          SDLK_ESCAPE

class InputManager {
    private:
        std::unordered_map<int,bool> keyState;
        std::unordered_map<int,int> keyUpdate;
        bool mouseState[6];
        int mouseUpdate[6];
        int mouseX, mouseY;
        int updateCounter;
        bool quitRequested;
    
    public:
        static InputManager& GetInstance();
        InputManager();
        ~InputManager();
        void Update();
        bool KeyPress(int key);
        bool KeyRelease(int key);
        bool IsKeyDown(int key);
        bool MousePress(int button);
        bool MouseRelease(int button);
        bool IsMouseDown(int button);
        int GetMouseX();
        int GetMouseY();
        bool QuitRequested();
};

#endif