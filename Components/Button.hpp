#pragma once
#include "../stdafx.hpp"

#include "Component.hpp"

#define FONT_SIZE 26

using namespace std;


class Button : public Component {
private:

public: 
    Button(const char* label, float posX, float posY, float width, float height);
    ~Button();

    void draw();
    Rectangle* getBox() {return &box;}
    void update();
};