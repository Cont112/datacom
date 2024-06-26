#pragma once
#include "Section.hpp"
#include "../Client/Client.hpp"

using namespace std;


class ClientSection : public Section {
private:
    pair<string, string> conn;
    Client* client = nullptr;
    int clientSocket = -1;

public:
    ClientSection();
    ~ClientSection();

    void init();

    void onButtonClick();

    pair<string,string> getConnData();
    void update();

};