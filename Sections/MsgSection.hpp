#pragma once
#include "Section.hpp"
using namespace std;


class MsgSection : public Section {

public:
    MsgSection();
    ~MsgSection();

    void init();
    void onButtonClick();
};