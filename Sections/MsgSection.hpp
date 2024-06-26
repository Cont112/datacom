#pragma once
#include "Section.hpp"
#include "../Client/Client.hpp"
#include "../Server/Server.hpp"
#include "../stdafx.hpp"
#include "PlotSection.hpp"

using namespace std;


class MsgSection : public Section {
private:
    string message;
    bool isClient;
    string receivedMessage;
    vector<int> receivedSignal;
    int clientSocket = -1;

    PlotSection* plot = nullptr;

public:
    MsgSection();
    ~MsgSection();

    void init(PlotSection* p);
    void onButtonClick();
    void update();
    void updateMessages();
    void setIsClient(bool isClient) {this->isClient = isClient;}

    void convertResponse();

};