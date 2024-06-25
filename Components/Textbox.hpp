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
        bool mouseOnText;
        bool selected;


    public:
        Textbox();
        ~Textbox();

        Textbox(float posX, float posY, float width, float height);
        Textbox(const char* label, float posX, float posY, float width, float height);

        inline string getText() {return text;}
        inline void setText(const char* t) {text = t;}

        void addChar(char c);
        void removeChar();
        void clear();

        void setSelected(bool s) {selected = s;}

        Rectangle* getBox() {return &textBox;}

        void draw();
        void init();

};