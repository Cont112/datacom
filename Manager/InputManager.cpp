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
            unsigned char c = GetCharPressed();
            if(c != 0){
                t->addChar(c);
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
    

    if(currentSelected != -1 && allComponents[currentSelected]->isSelected() == false){
        currentSelected = -1; //SE FOR BOTAO VOLTAR PARA -1
    }

    for(int i = 0; i < Component::getIdCounter(); i++){
        Component* c = allComponents[i];
        if(c->getSelectable() == false){
            continue;
        }
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
            allComponents[id]->setSelected(true);

            if(currentSelected != -1){
                allComponents[currentSelected]->setSelected(false);
            }
            currentSelected = id;
        }
        }
    }else{
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            if(currentSelected != -1){
                allComponents[currentSelected]->setSelected(false);
                
                currentSelected = -1;
            }
        }
    }

}