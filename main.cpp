#include "raylib.h"
#include "Components/Textbox.hpp"
#include "Components/Component.hpp"
#include "Sections/Section.hpp"
#include "Sections/ConnSection.hpp"
#include "Sections/MsgSection.hpp"
#include "Sections/PlotSection.hpp"
#include "Manager/InputManager.hpp"



void getAllComponents();
void select(); // VAI PARA O INPUT

ConnSection con;
MsgSection msg;
PlotSection plot;
map<int, Component*> allComponents;

InputManager* pInput = InputManager::getInstance();

int currentSelected = -1; 

int main(void)
{


    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "DataCom");

    SetTargetFPS(60);

    getAllComponents();

    pInput->setMap(allComponents);

    while (!WindowShouldClose())
    {

        BeginDrawing();
            ClearBackground(RAYWHITE);
            con.draw();
            msg.draw();
            plot.draw();
        EndDrawing();

        pInput->execute();
    }

    CloseWindow();

    return 0;
}

void getAllComponents(){
    int i = 0;
    vector<Component*> c = con.getComponents();
    vector<Component*> m = msg.getComponents();
    vector<Component*> p = plot.getComponents();

    for(int i = 0; i < c.size(); i++){
        allComponents[c[i]->getId()] = c[i];
    }

    for(int i = 0; i < m.size(); i++){
        allComponents[m[i]->getId()] = m[i];
    }

    for(int i = 0; i < p.size(); i++){
        allComponents[p[i]->getId()] = p[i];
    }

}



void select(){
    //iterar todas as textbox, ver se o mouse colidiu com alguma e se clicou, setar selected para true
    //se clicou fora de todas, setar selected para false

    int mouseColision = false;
    int mouseClick = false;
    int id = -1;
    

    for(int i = 0; i < Component::getIdCounter(); i++){
        Component* c = allComponents[i];

        if(CheckCollisionPointRec(GetMousePosition(), *c->getBox())){
            mouseColision = true;
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                id = c->getId();
                mouseClick = true;
            }
        } 
    }

    if(mouseColision){
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
