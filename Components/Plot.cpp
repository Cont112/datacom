#include "Plot.hpp"

Plot::Plot(){
    setPosition(0.0,0.0);
    setSize(0.0,0.0);
    init();
}


Plot::Plot(vector<int>& data, float posX, float posY, float width, float height): Component(posX,posY,width,height){
    init();
    this->data = data;
    convert();
}

Plot::~Plot() {}


void Plot::init(){
}

void Plot::update(){
    draw();
}

void Plot::convert(){
    st = 0;
  for(int i = 0; i < data.size(); i++){
    if(i != 0){
      yplotX[st] = ii(i, i);
      yplotY[st++] = ii(data[i-1], data[i]);
    }
    yplotX[st] = ii(i, i+1);
    yplotY[st++] = ii(data[i], data[i]);
  }
}
void Plot::draw() {
    // Desenhar eixos
    DrawLine(posX, posY, posX, posY + height, BLACK); // Eixo Y
    DrawLine(posX, posY + height / 2, posX + width, posY + height / 2, BLACK); //Eixo X

        DrawLine(posX - 5, posY + height / 2, posX, posY + height / 2, BLACK); // Pequena linha no eixo
        DrawText(TextFormat("%d", 0), posX - 30, posY + height / 2 - 10, 15, BLACK); // Valor


    // Valores fixos para o eixo Y
    const std::vector<int> yValues = {-3, -1, 1, 3};


    int minVal = -3; // O valor mínimo é o oposto do máximo em valor absoluto


    // Calcular escala Y
    float yScale = (float)height / (yValues.back() - yValues.front());

    // Desenhar valores no eixo Y
    for (int i = 0; i < yValues.size(); ++i) {
        int yPos = posY + height - (yValues[i] - minVal) * yScale;
        DrawLine(posX - 5, yPos, posX, yPos, BLACK); // Pequena linha no eixo
        DrawText(TextFormat("%d", yValues[i]), posX - 30, yPos - 10, 15, BLACK); // Valor
    }

    for (int i = 0; i < st; i++) {
        int x1 = posX + yplotX[i].first * width / (data.size());
        int y1 = posY + height  - (yplotY[i].first - minVal) * yScale; // Ajustar para minVal
        int x2 = posX + yplotX[i].second * width / (data.size() );
        int y2 = posY + height  - (yplotY[i].second - minVal) * yScale; // Ajustar para minVal

        DrawLine(x1, y1, x2, y2, RED);
    }


}