#pragma once
#include "../stdafx.hpp"
#include "../Components/Component.hpp"
#include "../Components/Textbox.hpp"
#include "../Components/Button.hpp"
#include "../Components/Plot.hpp"

using namespace std;


class Section {
protected:
    string title;
    Rectangle border;
    vector<Component*> components; //lista de componentes
    float posX, posY, width, height;

public:
    Section();
    ~Section();

    Section(const char* t,  float px, float py, float w, float h);

    void addComponent(Component* c);
    vector<Component*> getComponents() {return components;}
    void update();

    void init();

    void setTitle(const char* t) {title = t;}
    inline string getTitle() {return title;}

    void setPosition(float px, float py) {posX = px; posY = py;}
    void setSize(float w, float h) {width = w; height = h;}

    void updateBox(){border={posX,posY,width,height};}
    virtual void onButtonClick() = 0;
};