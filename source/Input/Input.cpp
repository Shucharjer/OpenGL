#include "Input/Input.h"
#include <GLFW/glfw3.h>
#include <utility>


std::map<int, KeyState> KeyInput::key_state_map;

void KeyInput::Update()
{
    for (auto& i : key_state_map)
    {
        i.second.pressed = false;
        i.second.released = false;
    }
}

bool KeyInput::IsHold(int key)
{
    return key_state_map[key].hold;
}

bool KeyInput::IsPressed(int key)
{
    return key_state_map[key].pressed;
}

bool KeyInput::IsReleased(int key)
{
    return key_state_map[key].released;
}

void KeyInput::Toggle(int key, bool &val)
{
    if (IsPressed(key)) val = !val;
}