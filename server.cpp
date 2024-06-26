#include "raylib.h"
#include "Components/Textbox.hpp"
#include "Components/Component.hpp"
#include "Sections/Section.hpp"
#include "Sections/MsgSection.hpp"
#include "Sections/PlotSection.hpp"
#include "Sections/ServerSection.cpp"
#include "Manager/InputManager.hpp"
#include "Server/Server.hpp"


void getAllComponents();


ServerSection server;

MsgSection msg;
PlotSection plot;
map<int, Component*> allComponents;

InputManager* pInput = InputManager::getInstance();


int main(void)
{
    cin.tie(0);
    ios_base::sync_with_stdio();
    

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "DataCom");
    

    server.init();

    plot.init();
    msg.init(&plot);
    msg.setIsClient(false);

    SetTargetFPS(60);

    getAllComponents();

    pInput->setMap(allComponents);

    while (!WindowShouldClose())
    {

        BeginDrawing();
            ClearBackground(RAYWHITE);
            server.update();
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
    vector<Component*> c = server.getComponents(); //server.
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

