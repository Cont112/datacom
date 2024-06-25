#include "InputManager.hpp"

using namespace std;

InputManager *InputManager::instance = NULL;

InputManager* InputManager::getInstance(){
    if(instance == NULL){
        instance = new InputManager();
    }
    return instance;
}

InputManager::InputManager(){
    mouseClick = false;
    mouseCollision = false;
    currentSelected = -1;
}

InputManager::~InputManager(){
    deleteInstance();
}

void InputManager::deleteInstance(){
    if(instance){
        delete instance;
        instance = NULL;
    }
}

void InputManager::execute(){
    select();
    getKeys();
}
void InputManager::getKeys(){
    if(currentSelected != -1){
        Textbox* t = (Textbox*) allComponents[currentSelected];
        if(IsKeyPressed(KEY_BACKSPACE)){
            t->removeChar();
        }else if(IsKeyPressed(KEY_ENTER)){
            t->addChar('\n');
        }else if(IsKeyPressed(KEY_SPACE)){
            t->addChar(' ');
        }else if(IsKeyPressed(KEY_DELETE)){
            t->clear();
        }else{
            for(int i = 32; i < 128; i++){
                if(IsKeyPressed(i)){
                    t->addChar(i);
                }
            }
        }
    }
}

void InputManager::select(){
//iterar lista de componentes
    //iterar todas as textbox, ver se o mouse colidiu com alguma e se clicou, setar selected para true
    //se clicou fora de todas, setar selected para false

    mouseCollision = false;
    mouseClick = false;
    int id = -1;
    

    for(int i = 0; i < Component::getIdCounter(); i++){
        Component* c = allComponents[i];

        if(CheckCollisionPointRec(GetMousePosition(), *c->getBox())){
            mouseCollision = true;
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                id = c->getId();
                mouseClick = true;
            }
        } 
    }

    if(mouseCollision){
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
        if(mouseClick){
            if(id != -1 && id != currentSelected){
            Textbox* t = (Textbox*) allComponents[id];
            t->setSelected(true);

            if(currentSelected != -1){
                t = (Textbox*) allComponents[currentSelected];
                t->setSelected(false);
            }
            currentSelected = id;
        }
        }
    }else{
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            if(currentSelected != -1){
                Textbox* t = (Textbox*) allComponents[currentSelected];
                t->setSelected(false);
                currentSelected = -1;
            }
        }
    }

}