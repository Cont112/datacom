#include "../stdafx.hpp"
#include "Component.hpp"
using namespace std;
typedef pair<int,int> ii;
#define MAX 512

class Plot: public Component {
private:
    vector<int> data;
    ii yplotX[MAX];
    ii yplotY[MAX];
    int st = 0; 


public:
    Plot();
    ~Plot();

    Plot(vector<int>& data, float posX, float posY, float width, float height);

    void convert();
    void draw();
    void init();
    void update();

    void setData(vector<int>& data) {this->data = data;convert();}

    Rectangle* getBox() {return &box;}
};
