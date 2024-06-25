#include "raylib.h"
#include "Components/Textbox.hpp"
#include "Components/Component.hpp"
#include "Sections/Section.hpp"
#include "Sections/ConnSection.hpp"
#include "Sections/MsgSection.hpp"
#include "Sections/PlotSection.hpp"
#include "Manager/InputManager.hpp"


void getAllComponents();


ConnSection con;
MsgSection msg;
PlotSection plot;
map<int, Component*> allComponents;

InputManager* pInput = InputManager::getInstance();


int main(void)
{
    bool client;

    cout << "Client(1) or Server(0)? ";
    cin >> client;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "DataCom");

    con.init(client);
    msg.init();
    plot.init();

    SetTargetFPS(60);

    getAllComponents();

    pInput->setMap(allComponents);

    while (!WindowShouldClose())
    {

        BeginDrawing();
            ClearBackground(RAYWHITE);
            con.update();
            cout << con.getConnData().first << " " << con.getConnData().second << endl;
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

