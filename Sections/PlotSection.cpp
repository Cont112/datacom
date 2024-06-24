#include "PlotSection.hpp"

PlotSection::PlotSection(){
    init();
}

PlotSection::~PlotSection(){

}

void PlotSection::init(){
    float posX = OUTER_PADDING;
    float posY = SCREEN_HEIGHT * RATIO_1_2 + OUTER_PADDING;
    float width = SCREEN_WIDTH - 2 * OUTER_PADDING;
    float height = SCREEN_HEIGHT * RATIO_1_2 - 2 * OUTER_PADDING; 

    setTitle("Plot");
    setPosition(posX, posY);
    setSize(width, height);
    updateBox();

}