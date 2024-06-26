#include "ClientSection.hpp"

ClientSection::ClientSection(){
}

ClientSection::~ClientSection(){
}

void ClientSection::init(){
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

    Button* tb3 = new Button("CONNECT", posX + width/2 - 100, posY+INNER_PADDING+320, 200, 40);

    addComponent((Component *)tb);
    addComponent((Component *)tb2);
    addComponent((Component *)tb3);
}


void ClientSection::onButtonClick(){
    if(conn.first != "" && conn.second != ""){
        client = Client::getInstance();
        if(!client->getScoketCreated())
            client->createSocket(conn.first, stoi(conn.second));
        client->connectToServer();
        while(!client->checkConnectionStatus());
        if (client->checkConnectionStatus()) {
         clientSocket = client->getClientSocket(); // Obter o socket do cliente
         cout << "Conectado ao servidor" << endl;
    }
    } 
}

void ClientSection::update(){
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
            conn.first = (tb->getText());
        } else if(i == 1){
            Textbox* tb = (Textbox*)components[i];
            conn.second = (tb->getText());
        }
    }
    

}

pair<string,string> ClientSection::getConnData(){
    return conn;
}