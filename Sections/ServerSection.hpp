#pragma once
#include "Section.hpp"
#include "../Server/Server.hpp"

using namespace std;


class ServerSection : public Section {
private:
    string conn;
    bool isClient;
    Server* server = nullptr;


public:
    ServerSection();
    ~ServerSection();



    void init();

    void onButtonClick();

    string getConnData();
    void update();

};