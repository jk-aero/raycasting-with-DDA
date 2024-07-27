
#include "raylib.h"
#include<iostream>
#include<cmath>
#include<vector>

////
// there are some minor issues with the code that is it only gives the output when staring point is changes
// no matter at whatever end position the  output cell value dont change
// also the y cordinate outputting is one less than the actual value
// 
// idk whyy
////


const int screenWidth = 600;
const int screenHeight = 600;
const int cellSize = 30;
const int numOfCellX = screenWidth / cellSize;
const int numOfCellY = screenHeight / cellSize;


class Grid {
public:
    int posX, posY; bool type; Color GRAY;
    Grid(int x, int y) :posX(x), posY(y) {}
    //type 1 means obstruction 

};

std::vector<Grid> grids(numOfCellY* numOfCellX, Grid(0, 0));
std::vector<Vector2>points;
Vector2 intersection;//this gives the intersection point of the ray with the wall


Vector2 normalise(float x, float y) {
    float length = std::sqrt(x * x + y * y);

    // Return a zero vector if the length is zero
    if (length == 0.0f) {
        return Vector2{ 0.0f, 0.0f };
    }

    return Vector2{ x / length, y / length };
}


int main() {

    // Initialization
    //--------------------------------------------------------------------------------------

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    for (int i = 0; i < numOfCellX; i++) {
        for (int j = 0; j < numOfCellY; j++)
        {
            grids[j * numOfCellX + i] = Grid{ i * cellSize,j * cellSize };
         

        }
    };

    bool setStart = 1;
    bool setEnd = 1;
    float startX = 0; float startY = 0;

    float endX = 380; float endY = 250;
 

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
         int mouse_x = GetMousePosition().x;
         int mouse_y = GetMousePosition().y;

 
        
         Raycast(mouse_x, mouse_y, endX, endY);

        
     
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        

        for (int x = 0; x < screenWidth; x += cellSize) {
            for (int y = 0; y < screenHeight; y += cellSize) {
                
                DrawCircle(mouse_x, mouse_y, 10, GREEN);//player
                DrawCircle(endX, endY, 10, ORANGE);// ending postion

                if(IsKeyDown(KEY_W)) {endY -= 0.05;}
                if (IsKeyDown(KEY_S)){endY += 0.05;}
                if (IsKeyDown(KEY_A)){endX -= 0.05;}
                if (IsKeyDown(KEY_D)){endX += 0.05;}
                if (endX < 0) { endX = 0; };
                if (endY < 0) { endY = 0; }
                if (endX >= 600) { endX = 600; }
                if (endY >= 600) { endY = 600; }

                if ((mouse_x >= x && mouse_x <= x + cellSize) && (mouse_y >= y && mouse_y <= y + cellSize))
                {
                   
                    if (IsMouseButtonReleased(1)) {
                        grids[(x / cellSize) + (y/ cellSize) * numOfCellY].type = !grids[(x/ cellSize) + (y/ cellSize) * numOfCellY].type;
                        if (grids[(x/ cellSize) + (y/ cellSize) * numOfCellY].type == 0) { grids[(x / cellSize) + (y / cellSize) * numOfCellY].Color = GRAY; }
                        else if (grids[(x / cellSize) + (y / cellSize) * numOfCellY].type == 1) { grids[(x / cellSize) + (y/ cellSize) * numOfCellY].Color = DARKPURPLE; }
                    }
                }







                DrawRectangle(x, y, cellSize - 1, cellSize - 1, grids[(x / cellSize) + (y / cellSize) * numOfCellY].Color);
                if (setStart && setEnd)
                {
               
                    if (IsMouseButtonDown(0)) {
                        DrawLine(mouse_x, mouse_y, endX, endY, BLUE);
                        //std::cout << "mouse Postion x:" << mouse_x << "  Y:" << mouse_y << "  endx:" << endX << "   endY:" << endY << '\n';
                        /*if (Tilefound)
                        {
                            DrawCircleV(intersection, 5, ORANGE);
                            std::cout << intersection.x << " " << intersection.y << '\n';


                        }*/
                    }
                }
            }
        }
        



        EndDrawing();
        //----------------------------------------------------------------------------------



    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
