#include "PlotSection.hpp"

PlotSection::PlotSection(){
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

    std::vector<int> dados = {0};
    data = dados;

    Plot* p = new Plot(dados, posX+50,posY+50,width-100,height-100);
    p->setSelectable(false);

    Button* b = new Button("Prova Real", posX+width-250, posY+height/2-20, 200,40);

    addComponent((Component*) p);
    addComponent((Component*) b);
}

void PlotSection::onButtonClick(){
    if(provaReal){
        provaReal = false;
    } else {
        provaReal = true;
    }
}

void PlotSection::update() {
    DrawText(title.c_str(), posX + INNER_PADDING, posY+INNER_PADDING, 30 ,GRAY);
    DrawRectangleLinesEx(border, 5, GRAY);

    for (int i = 0; i < components.size(); i++) {
        components[i]->update();
        if(components[i]->getType() == 2){
            Button* b = (Button*)components[i];
            if(b->isSelected()){
                onButtonClick();
                b->setSelected(false);
            }
        }
    }

    if(provaReal){
        Plot* p = (Plot* ) components[0]; //plot
        string bin = "0011011001";
        vector<int> d;

        char cod[256];
        int cod_len;

        bin_to_c2b1q(bin.data(),bin.length(),cod,&cod_len);
        for(int i =0 ; i < cod_len; i++){
        switch (cod[i]){
            case 'a':
                d.push_back(-3);
                break;
            case 'b':
                d.push_back(-1);
                break;
            case 'c':
                d.push_back(1);
                break;
            case 'd':
                d.push_back(3);
                break;
                
        }
        }
        p->setData(d);
    
    }else {
        Plot* p = (Plot* ) components[0]; //plot
        p->setData(data);   
    }
}
