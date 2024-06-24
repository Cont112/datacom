#pragma once
#include "../stdafx.hpp"
#include "Components/Component.hpp"
#include "Components/Textbox.hpp"
#include "Components/Section.hpp"

using namespace std;

class InputManager {
    private:
        bool mouseClick;
        bool mouseCollision;

        int currentSelected;

        map<int, Component> allComponents;

        // Singleton
        static InputManager *instance;
        InputManager();
    public:
        ~InputManager();

        static InputManager* getInstance();
        void deleteInstance();

        void select();

        void execute();
};