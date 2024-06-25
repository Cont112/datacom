#include "MsgSection.hpp"

MsgSection::MsgSection(){
}

MsgSection::~MsgSection(){

}

void MsgSection::init(){
    float posX = SCREEN_WIDTH * RATIO_2_5 + OUTER_PADDING;
    float posY = OUTER_PADDING;
    float width = SCREEN_WIDTH * RATIO_3_5 - 2 * OUTER_PADDING;
    float height = SCREEN_HEIGHT * RATIO_1_2 - 2 * OUTER_PADDING; 

    setTitle("Message");
    setPosition(posX, posY);
    setSize(width, height);
    updateBox();

    Textbox* tb = new Textbox("Send Message:",posX + INNER_PADDING, posY+INNER_PADDING+110, width - 2*INNER_PADDING, 60);
    
    Textbox* tb2 = new Textbox("Response:",posX+ INNER_PADDING, posY+INNER_PADDING+200, width - 2*INNER_PADDING, 60);
    tb2->setSelectable(false);
    
    Button* tb3 = new Button("SEND", posX + width/2 - 100, posY+INNER_PADDING+320, 180, 40);

    addComponent((Component *)tb);
    addComponent((Component *)tb2);
    addComponent((Component *)tb3);


}
void MsgSection::onButtonClick(){
    cout << "message Button Clicked" << endl;
}