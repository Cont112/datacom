#pragma once
#include "Section.hpp"
#include "../Client/Client.hpp"
#include "../Server/Server.hpp"

using namespace std;


class ConnSection : public Section {
private:
    pair<string, string> conn;
    bool isClient;
    Client* client;
    Server* server;

public:
    ConnSection();
    ~ConnSection();

    void initClient();
    void initServer();
    void init(bool isClient);

    void onButtonClick();

    pair<string,string> getConnData();
    void update();

};