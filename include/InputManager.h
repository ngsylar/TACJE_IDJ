#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <unordered_map>

#define INCLUDE_SDL
#include "SDL_include.h"

#define MOUSE_BUTTON_LEFT   SDL_BUTTON_LEFT
#define MOUSE_BUTTON_RIGHT  SDL_BUTTON_RIGHT
#define KEY_ARROW_UP        SDLK_UP
#define KEY_ARROW_DOWN      SDLK_DOWN
#define KEY_ARROW_LEFT      SDLK_LEFT
#define KEY_ARROW_RIGHT     SDLK_RIGHT
#define KEY_SPACE           SDLK_SPACE
#define KEY_ESCAPE          SDLK_ESCAPE

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