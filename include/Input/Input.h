#pragma once
#include <map>
#include <vector>
#include "IApplication.h"

struct KeyState
{
    bool pressed = false;
    bool hold = false;
    bool released = false;
};

class KeyInput
{
    friend class IApplication;
    private:
    static std::map<int, KeyState> key_state_map;
    static void Update();
    public:
    static bool IsPressed(int key);
    static bool IsHold(int key);
    static bool IsReleased(int key);
    static void Toggle(int key, bool& val);
};

class CursorInput
{
    friend class IApplication;
    private:
    static std::map<int, KeyState> cursor_state_map;
    static void Update();
    public:
    static bool IsPressed(int btn);
    static bool IsHold(int btn);
    static bool IsReleased(int btn);
};
