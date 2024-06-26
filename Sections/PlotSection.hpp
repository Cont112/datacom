#pragma once
#include "Section.hpp"
using namespace std;


class PlotSection : public Section {
private:
    bool provaReal = false;
    vector<int> data;
    vector<int> prevData;
public:
    PlotSection();
    ~PlotSection();

    void init();

    void onButtonClick();

    void update();

    void setData(vector<int>&data) {this->data = data;}

};