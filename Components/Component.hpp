#pragma once
#include "../stdafx.hpp"
using namespace std;


class Component {
protected:
    string label;
    Rectangle box;
    int id;
    int type;
    static int idCounter;
    bool selected;
    bool selectable;


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

    void setSelected(bool s) {selected = s;}
    bool isSelected() {return selected;}

    void setSelectable(bool s) {selectable = s;}
    bool getSelectable() {return selectable;}

    int getType(){return type;}
    
    virtual Rectangle* getBox() = 0;

    virtual void draw() = 0;
    virtual void update() = 0;
};