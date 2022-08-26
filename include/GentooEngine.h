// C++
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>

// SDL2
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include "SDL_include.h"

// Math
#include "Timer.h"
#include "Vec2.h"

// Engine System
#include "Rect.h"
#include "GameObject.h"
#include "Camera.h"
#include "InputManager.h"
#include "Collision.h"
#include "Component.h"
#include "Resources.h"

// Engine Components
#include "CameraFollower.h"
#include "Collider.h"
#include "Sprite.h"
#include "TileSet.h"
#include "TileMap.h"
#include "Music.h"
#include "Sound.h"

// Engine Core
#include "State.h"
#include "Game.h"