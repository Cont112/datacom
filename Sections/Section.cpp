#include "Section.hpp"

using namespace std;

Section::Section() {

    setPosition(0.0, 0.0);
    setSize(0.0, 0.0);
    border = {0, 0, 0, 0};
    title = "";
}

Section::~Section() {
    for(int i = 0; i < components.size(); i++){
        cout << "Componente " << components[i]->getId() << " deletada!" << endl;
        delete components[i];
    }
    std::cout << "Componentes deletadas!" << endl;
    components.clear();
}

Section::Section(const char* t, float px, float py, float w, float h) {
    setPosition(px, py);
    setSize(w, h);
    border = {px, py, w, h};
    title = t;
}


void Section::addComponent(Component* c) {
    components.push_back(c);
}

void Section::update() {
    DrawText(title.c_str(), posX + INNER_PADDING, posY+INNER_PADDING, 30 ,GRAY);
    DrawRectangleLinesEx(border, 5, GRAY);

    for (int i = 0; i < components.size(); i++) {
        components[i]->update();
        if(components[i]->getType() == 2){
            Button* b = (Button*)components[i];
            if(b->isSelected()){
                onButtonClick();
                b->setSelected(false);
            }
        }
    }
}

