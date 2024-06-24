#include "raylib.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800
#define OUTER_PADDING 5
#define INNER_PADDING 10
#define RATIO_2_5 2./5
#define RATIO_3_5 3./5
#define RATIO_1_2 1./2

void ConnectionBox();
void MessageBox();
void PlotBox();

void HandleIPInput();

Rectangle ipBox = {0,0,0,0};
Rectangle portBox = {0,0,0,0};
Rectangle connBox = {0,0,0,0};

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "DataCom");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        HandleIPInput();

        BeginDrawing();
            ClearBackground(RAYWHITE);

            ConnectionBox();
            MessageBox();
            PlotBox();
            

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

char name[21234];
int letterCount = 0;

void HandleIPInput(){
    int mouseOnText;
    if (CheckCollisionPointRec(GetMousePosition(), ipBox)) mouseOnText = true;
    else mouseOnText = false;

    if (mouseOnText)
    {
        // Set the window's cursor to the I-Beam
        SetMouseCursor(MOUSE_CURSOR_IBEAM);

        // Get char pressed (unicode character) on the queue
        int key = GetCharPressed();

        // Check if more characters have been pressed on the same frame
        while (key > 0)
        {
            // NOTE: Only allow keys in range [32..125]
            if ((key >= 32) && (key <= 125) && (letterCount < 20))
            {
                name[letterCount] = (char)key;
                name[letterCount+1] = '\0'; // Add null terminator at the end of the string.
                letterCount++;
            }

            key = GetCharPressed();  // Check next character in the queue
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            letterCount--;
            if (letterCount < 0) letterCount = 0;
            name[letterCount] = '\0';
        }
    }
    else SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}

void ConnectionBox(){
    //Main Box
    float posX = OUTER_PADDING;
    float posY = OUTER_PADDING;
    float width = SCREEN_WIDTH * RATIO_2_5 - 2 * OUTER_PADDING;
    float height = SCREEN_HEIGHT * RATIO_1_2 - 2 * OUTER_PADDING; 

    Rectangle connRec = {posX, posY, width, height};

    DrawRectangleLinesEx(connRec, 5, GRAY);

    //Title
    DrawText("Client.c", posX + INNER_PADDING, posY+INNER_PADDING, 30, GRAY);

    //IP
    DrawText("Remote IP", posX + INNER_PADDING, posY+INNER_PADDING+110, 26, GRAY);

    ipBox = {posX + INNER_PADDING, posY+INNER_PADDING+140, width - 2*INNER_PADDING, 40};
    DrawRectangleRec(ipBox, LIGHTGRAY);
    DrawRectangleLinesEx(ipBox, 1, DARKGRAY);
    DrawText(name, posX + INNER_PADDING + 30, posY+INNER_PADDING+140 + 8, 26, GRAY);
    
    //PORT
    DrawText("PORT", posX + INNER_PADDING, posY+INNER_PADDING+200, 26, GRAY);

    portBox = {posX + INNER_PADDING, posY+INNER_PADDING+230, width/3, 40};
    DrawRectangleRec(portBox, LIGHTGRAY);
    DrawRectangleLinesEx(portBox, 1, DARKGRAY);


    //CONNECT
    connBox = {posX + width/2 - 100, posY+INNER_PADDING+320, 200, 40};
    DrawRectangleRec(connBox, GRAY);
    DrawRectangleLinesEx(connBox, 1, LIGHTGRAY);
    DrawText("CONNECT", posX + width/2 - 100 + 40, posY+INNER_PADDING+320 + 8, 26, LIGHTGRAY);
}
void MessageBox(){
    float posX = SCREEN_WIDTH * RATIO_2_5 + OUTER_PADDING;
    float posY = OUTER_PADDING;
    float width = SCREEN_WIDTH * RATIO_3_5 - 2 * OUTER_PADDING;
    float height = SCREEN_HEIGHT * RATIO_1_2 - 2 * OUTER_PADDING; 

    Rectangle messRec = {posX, posY, width, height};

    DrawRectangleLinesEx(messRec, 5, GRAY);
}
void PlotBox(){
    float posX = OUTER_PADDING;
    float posY = SCREEN_HEIGHT * RATIO_1_2 + OUTER_PADDING;
    float width = SCREEN_WIDTH - 2 * OUTER_PADDING;
    float height = SCREEN_HEIGHT * RATIO_1_2 - 2 * OUTER_PADDING; 

    Rectangle plotRec = {posX, posY, width, height};

    DrawRectangleLinesEx(plotRec, 5, GRAY);
}