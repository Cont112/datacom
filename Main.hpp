#pragma once
#include "stdafx.hpp"
#include "Components/Component.hpp"
#include "Components/Section.hpp"
#include "Components/Textbox.hpp"

using namespace std;


class Main {
private:
    bool running;



public:
    Main();
    ~Main();

    void init();
    void run();
    void update();
    void draw();
    void close();

};