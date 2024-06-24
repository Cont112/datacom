#include "Component.hpp"

using namespace std;

int Component::idCounter = 0;

Component::Component(){
    setPosition(0.0,0.0);
    setSize(0.0,0.0);

    label = "";
    box = {0,0,0,0};

    id = idCounter++;
}

Component::Component(float posX, float posY, float width, float height){
    setPosition(posX, posY);
    setSize(width, height);

    label = "";
    box = {posX, posY, width, height};
    id = idCounter++;
}

Component::~Component(){
}
