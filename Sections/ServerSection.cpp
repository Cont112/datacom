#include "ServerSection.hpp"

ServerSection::ServerSection(){
}

ServerSection::~ServerSection(){
}

void ServerSection::init(){
    float posX = OUTER_PADDING;
    float posY = OUTER_PADDING;
    float width = SCREEN_WIDTH * RATIO_2_5 - 2 * OUTER_PADDING;
    float height = SCREEN_HEIGHT * RATIO_1_2 - 2 * OUTER_PADDING; 

    setTitle("Server.c");
    setPosition(posX, posY);
    setSize(width, height);
    updateBox();

    Textbox* tb = new Textbox("PORT:",posX + INNER_PADDING, posY+INNER_PADDING+110, width - 2*INNER_PADDING, 60);
    
    Button* tb2 = new Button("START", posX + width/2 - 100, posY+INNER_PADDING+320, 180, 40);

    addComponent((Component *)tb);
    addComponent((Component *)tb2);
}


void ServerSection::onButtonClick(){
    //BOTAO CONECTAR
    //ENVIAR CONNDATA

    Server * server = Server::getInstance();
     if(conn != ""){
         if(!server->getScoketCreated())
             server->createSocket(stoi(conn));

         server->start();
         clientSocket = server->getClientSocket();
     } else {
         server->closeConnection();
     }
 }


void ServerSection::update(){
    DrawText(title.c_str(), posX + INNER_PADDING, posY+INNER_PADDING, 30 ,GRAY);
    DrawRectangleLinesEx(border, 5, GRAY);
    for(int i = 0; i < components.size(); i++){
        components[i]->update();

        if(components[i]->getType() == 2){
            Button* b = (Button*)components[i];
            if(b->isSelected()){
                onButtonClick();
                b->setSelected(false);
            }
        } else if(i == 0){
            Textbox* tb = (Textbox*)components[i];
            conn = (tb->getText());
        }
    }
}



string ServerSection::getConnData(){
    return conn;
}