#include "MsgSection.hpp"

MsgSection::MsgSection(): receivedMessage(""){
}

MsgSection::~MsgSection(){

}

void MsgSection::init(PlotSection* p){
    plot = p;
    float posX = SCREEN_WIDTH * RATIO_2_5 + OUTER_PADDING;
    float posY = OUTER_PADDING;
    float width = SCREEN_WIDTH * RATIO_3_5 - 2 * OUTER_PADDING;
    float height = SCREEN_HEIGHT * RATIO_1_2 - 2 * OUTER_PADDING; 
    isClient = false;

    setTitle("Message");
    setPosition(posX, posY);
    setSize(width, height);
    updateBox();

    Textbox* tb = new Textbox("Send Message:",posX + INNER_PADDING, posY+INNER_PADDING+40, width - 2*INNER_PADDING, 60);
    
    Textbox* tb2 = new Textbox("Response:",posX+ INNER_PADDING, posY+INNER_PADDING+110, width - 2*INNER_PADDING, 60);
    Textbox* tb3 = new Textbox("Encrypted:",posX+ INNER_PADDING, posY+INNER_PADDING+180, width - 2*INNER_PADDING, 60);
    Textbox* tb4 = new Textbox("Binary:",posX+ INNER_PADDING, posY+INNER_PADDING+250, width - 2*INNER_PADDING, 60);
    tb2->setSelectable(false);
    tb3->setSelectable(false);
    tb4->setSelectable(false);
    
    Button* tb5 = new Button("SEND", posX + width/2 - 100, posY+INNER_PADDING+320, 180, 40);

    addComponent((Component *)tb);// i =0 message
    addComponent((Component *)tb2);
    addComponent((Component *)tb3);
    addComponent((Component *)tb4);
    addComponent((Component *)tb5);


}
void MsgSection::onButtonClick(){
    cout << "message Button Clicked" << endl;


    char bin[512];
    int bin_len;

    char cod[256];
    int cod_len;

    //encrypt(message.data(),message.length(),p,m);
    string encoded  = encryptTemp(message,24);

    str_to_bin(encoded.data(), encoded.length(), bin, &bin_len);

    bin_to_c2b1q(bin,bin_len,cod,&cod_len);


    if(isClient){
        Client* c = Client::getInstance();
        c->sendMessage(cod);
    } else{
        Server* s = Server::getInstance();
        s->sendMessage(cod);
    }

    vector<int> data;
    convertToVector(data,cod);
    plot->setData(data);


}

void MsgSection::update() {
    Client* cli = Client::getInstance();
    Server* ser = Server::getInstance();
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
        if(i == 0){
            Textbox* tb = (Textbox*)components[i];
            message = tb->getText();
        }
    }

    updateMessages();
}

void MsgSection::updateMessages() {
    Textbox* tb4 = (Textbox*)components[3]; // Obter a caixa de texto "Binary"

    if (isClient) {
        Client* c = Client::getInstance();
        if(c->getScoketCreated()){
            receivedMessage = c->receiveMessage();
            if (!receivedMessage.empty()) {
                convertResponse();
            }
        }
    } else {
        Server* s = Server::getInstance();
        if(s->getScoketCreated()){ 
        receivedMessage = s->receiveMessage();
        if (!receivedMessage.empty()) {
            convertResponse();
        }
        }
    }
}


void MsgSection::convertResponse(){
    vector<int> d;
    for(int i = 0; i < receivedMessage.length(); i++){
        switch (receivedMessage[i]){
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
    plot->setData(d);

    Textbox* tb4 = (Textbox*)components[3]; //binary
    Textbox* tb3 = (Textbox*)components[2]; // Obter a caixa de texto "Encrypted"
    Textbox* tb2 = (Textbox*)components[1]; // Obter a caixa de texto "Response"

    //decrypt()
    char bin[512];//32CARACTERES
    int bin_len;

    char str[256];
    int str_len;

    char res[256];
    int res_len;

    c2b1q_to_bin(receivedMessage.data(), receivedMessage.length(),bin, &bin_len);
    tb4->setText(bin);

    bin_to_str(bin,bin_len,str,&str_len);
    tb3->setText(str);

    string msg(str);
    msg = decryptTemp(msg, 24);
    tb2->setText(msg.c_str());


    //decrypt();
}