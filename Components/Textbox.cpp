#include "Textbox.hpp"

Textbox::Textbox(): Component(){
    setPosition(0.0,0.0);
    setSize(0.0,0.0);
    init();
}

Textbox::~Textbox(){

}

Textbox::Textbox(float posX, float posY, float width, float height): Component(posX,posY,width,height){
    init();
    textBox = {posX, posY+FONT_SIZE, width, height-FONT_SIZE};
}

Textbox::Textbox(const char* l, float posX, float posY, float width, float height): Component(posX,posY,width,height){
    label = l;
    init();
    textBox = {posX, posY+FONT_SIZE, width, height-FONT_SIZE};
}

void Textbox::init(){
    text = "";
    letterCount = 0;
    mouseOnText = false;
    selected = false;
    textBox = {0.0,0.0,0.0,0.0};
    
}

void Textbox::draw(){
    DrawRectangleRec(textBox, LIGHTGRAY);
    if(selected){
        DrawRectangleLinesEx(textBox, 1, RED);
    }
    else{
        DrawRectangleLinesEx(textBox, 1, DARKGRAY);
    
    }

    DrawText(label.c_str(), posX,posY, FONT_SIZE, GRAY);
    DrawText(text.c_str(), posX+10, posY+5+FONT_SIZE, FONT_SIZE, GRAY);
}

void Textbox::addChar(char c){
    if(letterCount < LIMIT){
        text += c;
        letterCount++;
    }
}

void Textbox::removeChar(){
    if(letterCount > 0){
        text.pop_back();
        letterCount--;
    }
}

void Textbox::clear(){
    text = "";
    letterCount = 0;
}