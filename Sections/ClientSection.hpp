#pragma once
#include "Section.hpp"
#include "../Client/Client.hpp"

using namespace std;


class ClientSection : public Section {
private:
    pair<string, string> conn;
    bool isClient;
    Client* client = nullptr;

public:
    ClientSection();
    ~ClientSection();

    void init();

    void onButtonClick();

    pair<string,string> getConnData();
    void update();

};