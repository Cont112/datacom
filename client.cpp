#include "raylib.h"
#include "Components/Textbox.hpp"
#include "Components/Component.hpp"
#include "Sections/Section.hpp"
#include "Sections/ClientSection.hpp"
#include "Sections/MsgSection.hpp"
#include "Sections/PlotSection.hpp"
#include "Manager/InputManager.hpp"


void getAllComponents();


ClientSection client;

PlotSection plot;
MsgSection msg;
map<int, Component*> allComponents;

InputManager* pInput = InputManager::getInstance();


int main(void)
{
    cin.tie(0);
    ios_base::sync_with_stdio();
    
    bool isclient;


    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "DataCom");
    
    client.init();
    plot.init();
    msg.init(&plot);
    msg.setIsClient(true);

    SetTargetFPS(60);

    getAllComponents();

    pInput->setMap(allComponents);

    while (!WindowShouldClose())
    {

        BeginDrawing();
            ClearBackground(RAYWHITE);
            client.update();
            msg.update();
            plot.update();
        EndDrawing();

        pInput->execute();
    }

    CloseWindow();

    return 0;
}

void getAllComponents(){
    int i = 0;
    vector<Component*> c = client.getComponents();
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

