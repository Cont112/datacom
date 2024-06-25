#include "ConnSection.hpp"

ConnSection::ConnSection(){
}

ConnSection::~ConnSection(){

}

void ConnSection::init(bool isClient){
    isClient = isClient;
    if(isClient){
        initClient();
    } else {
        initServer();
    }
}

void ConnSection::initClient(){
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

void ConnSection::initServer(){
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

void ConnSection::onButtonClick(){
    //BOTAO CONECTAR
    //ENVIAR CONNDATA
    if(isClient){
        client = new Client(conn.first, stoi(conn.second));
    }
    else{
        server = new Server(stoi(conn.second));
    }

}

void ConnSection::update(){
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

pair<string,string> ConnSection::getConnData(){
    return conn;
}