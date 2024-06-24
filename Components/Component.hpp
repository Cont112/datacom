#pragma once
#include "../stdafx.hpp"

using namespace std;

class Component {
protected:
    string label;
    Rectangle box;
    int id;
    static int idCounter;

    float posX, posY, width, height;

public:
    Component();
    Component(float posX, float posY, float width, float height);
    ~Component();

    void setPosition(float px, float py) {posX = px; posY = py;}
    void setSize(float w, float h) {width = w; height = h;}

    void setLabel(const char * l) {label = l;} 
    string getLabel() {return label;}

    inline int getId() {return id;}
    static int getIdCounter() {return idCounter;}

    virtual Rectangle* getBox() = 0;

    virtual void draw() = 0;
};