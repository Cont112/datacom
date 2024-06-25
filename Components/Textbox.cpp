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
    calcCharLimit();
    type =1;

}

Textbox::Textbox(const char* l, float posX, float posY, float width, float height): Component(posX,posY,width,height){
    label = l;
    init();
    textBox = {posX, posY+FONT_SIZE, width, height-FONT_SIZE};
    calcCharLimit();
    type = 1;


}

void Textbox::init(){
    text = "";
    letterCount = 0;
    selected = false;
    textBox = {0.0,0.0,0.0,0.0};
    charLimit = 0;
    
}

void Textbox::update(){
    draw();
}

void Textbox::draw(){

    if(selectable)
        DrawRectangleRec(textBox, LIGHTGRAY);
    
    if(selected){
        DrawRectangleLinesEx(textBox, 1, RED);
    }
    else{
        DrawRectangleLinesEx(textBox, 1, DARKGRAY);
    
    }


    DrawText(label.c_str(), posX,posY, FONT_SIZE,GRAY);
    DrawText(text.c_str(), posX+10, posY+5+FONT_SIZE, FONT_SIZE,BLACK);
    //DrawTextCodepoints(GetFontDefault(), (int*)text.c_str(), text.length(),{posX+10, posY+5+FONT_SIZE}, FONT_SIZE, 0.6, BLACK);

}

void Textbox::addChar(unsigned char c){
    if(letterCount < charLimit){
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

void Textbox::calcCharLimit(){
    charLimit = (int)(textBox.width - 2*10)/(FONT_SIZE*0.6);
    std::cout << charLimit << endl;
}

void Textbox::clear(){
    text = "";
    letterCount = 0;
}