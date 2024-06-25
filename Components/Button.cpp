#include "Button.hpp"

Button::Button(const char* label, float posX, float posY, float width, float height): Component(posX,posY,width,height){
    setLabel(label);
    type = 2;
}

Button::~Button(){

}

void Button::update(){
    draw();
}

void Button::draw(){

    DrawRectangleRec(box, LIGHTGRAY);

    if(selected){
        DrawRectangleLinesEx(box, 1, WHITE);
    }
    else{
        DrawRectangleLinesEx(box, 1, DARKGRAY);
    
    }
    
    DrawText(label.c_str(), posX+40,posY+8, FONT_SIZE, GRAY);
}

