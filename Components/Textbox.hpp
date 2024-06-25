#pragma once
#include "../stdafx.hpp"
#include "Component.hpp"

#define FONT_SIZE 26
#define LIMIT 20
using namespace std;


class Textbox: public Component { 
    private:
        string text;
        Rectangle textBox;
        int letterCount;
        int charLimit;


    public:
        Textbox();
        ~Textbox();

        Textbox(float posX, float posY, float width, float height);
        Textbox(const char* label, float posX, float posY, float width, float height);

        inline string getText() {return text;}
        inline void setText(const char* t) {text = t;}

        void addChar(unsigned char c);
        void removeChar();
        void clear();

        void calcCharLimit();


        Rectangle* getBox() {return &textBox;}

        void draw();
        void init();
        void update();

};