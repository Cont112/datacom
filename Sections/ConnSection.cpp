#include "ConnSection.hpp"

ConnSection::ConnSection(){
    init();
}

ConnSection::~ConnSection(){

}

void ConnSection::init(){
    float posX = OUTER_PADDING;
    float posY = OUTER_PADDING;
    float width = SCREEN_WIDTH * RATIO_2_5 - 2 * OUTER_PADDING;
    float height = SCREEN_HEIGHT * RATIO_1_2 - 2 * OUTER_PADDING; 

    setTitle("Client.c");
    setPosition(posX, posY);
    setSize(width, height);
    updateBox();

    Textbox* tb = new Textbox("REMOTE IP:",posX + INNER_PADDING, posY+INNER_PADDING+110, width - 2*INNER_PADDING, 60);
    
    Textbox* tb2 = new Textbox("PORT:",posX+ INNER_PADDING, posY+INNER_PADDING+200, width/3, 60);

    addComponent((Component *)tb);
    addComponent((Component *)tb2);
      //CONNECT
    // connBox = {posX + width/2 - 100, posY+INNER_PADDING+320, 200, 40};
    // DrawRectangleRec(connBox, GRAY);
    // DrawRectangleLinesEx(connBox, 1, LIGHTGRAY);
    // DrawText("CONNECT", posX + width/2 - 100 + 40, posY+INNER_PADDING+320 + 8, 26, LIGHTGRAY);


}