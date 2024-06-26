#pragma once
#include "Section.hpp"
#include "../Server/Server.hpp"

using namespace std;


class ServerSection : public Section {
private:
    string conn;
    int clientSocket = -1;

public:
    ServerSection();
    ~ServerSection();



    void init();

    void onButtonClick();

    string getConnData();
    void update();
    void updateServer();

};