#pragma once
#include "../stdafx.hpp"
#include "../Components/Component.hpp"
#include "../Components/Textbox.hpp"
#include "../Sections/Section.hpp"

using namespace std;

class InputManager {
    private:
        bool mouseClick;
        bool mouseCollision;

        int currentSelected;

        map<int, Component*> allComponents;

        // Singleton
        static InputManager *instance;
        InputManager();
    public:
        ~InputManager();

        static InputManager* getInstance();
        void deleteInstance();

        void setMap(map<int, Component*> m) { allComponents = m; }

        void select();
        void getKeys();


        void resetSelected() { currentSelected = -1; }
        void execute();
};