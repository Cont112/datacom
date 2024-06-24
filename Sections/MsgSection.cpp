#include "MsgSection.hpp"

MsgSection::MsgSection(){
    init();
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


}