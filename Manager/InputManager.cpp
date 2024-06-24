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

void InputManager::select(){
//iterar lista de componentes


}