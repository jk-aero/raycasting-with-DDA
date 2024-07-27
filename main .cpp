
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


bool RaycastWithDDA(float mouse_x,float mouse_y,float endX,float endY) {

    Vector2 rayStart{ mouse_x/30,mouse_y/30 };
    endX /= 30; endY /= 30;
    

    Vector2 RayDirection = normalise((mouse_x-endX), ( mouse_y-endY));
    //std::cout << "mouse: x:" << rayStart.x << "  y:" << rayStart.y << "end x:" << endX << "  y:" << endY << "   normalised x:" << RayDirection.x << "   Y:"<<RayDirection.y << "\n";

    Vector2 unitStepSize{
        //this vector contain the unit setp size (x,y) to the  direction vector
        //to find hypotenuse we are gonna multiply this thing with scalar units
        std::sqrt(1 + (RayDirection.y / std::abs(1 / RayDirection.x)) * (RayDirection.y / std::abs(1 / RayDirection.x))),
        std::sqrt(1 + (RayDirection.x / std::abs(1 / RayDirection.y)) * (RayDirection.x / std::abs(1 / RayDirection.y)))
    };

    Vector2 MapCheck{ (int)rayStart.x,(int)rayStart.y };//this is used as the current working cell-------+++++++++++++++++++++++++++++++++++++++++++++++++++++----->here some corretion to make thigs in 123 order and we need floatng point to get the relative position//done i guess
    //std::cout << "    x:" << MapCheck.x << "   y : " << MapCheck.y<< "\n";

    Vector2 RayLength1d;//stores the length of hypotenuse x and y correspondingly
    //which we got by multiplying wth unitStepSize


    Vector2 Step;//to change the direction based on angle (ie to go up or down)

    if (RayDirection.x < 0)
    {
        Step.x = -1;
        //calculating rhe relative position of the player wth respect to the cell;
        // here we are multiplying the unit vec with the scalar to get the hypotenuse
        // and storing it in the raylength vector
        RayLength1d.x = (rayStart.x - float(MapCheck.x) * unitStepSize.x);//----------++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++-multiplying the relative value with unit vec to get the hypotenuse

    }
    else
    {
        Step.x = 1;
        //calculating rhe relative position of the player wth respect to the cell;
        // here we are multiplying the unit vec with the scalar to get the hypotenuse
        // and storing it in the raylength vector
        RayLength1d.x = (float(MapCheck.x+1) - rayStart.x) * unitStepSize.x;
    }
    if (RayDirection.y < 0)
    {
        Step.y = -1;
        //calculating rhe relative position of the player wth respect to the cell;
        // here we are multiplying the unit vec with the scalar to get the hypotenuse
        // and storing it in the raylength vector
        RayLength1d.y = (rayStart.y - float(MapCheck.y) * unitStepSize.y);
    }
    else
    {
        Step.y = 1;
        //calculating rhe relative position of the player wth respect to the cell;
        // here we are multiplying the unit vec with the scalar to get the hypotenuse
        // and storing it in the raylength vector
        RayLength1d.y = ( float(MapCheck.y+1) - rayStart.y )* unitStepSize.y;
    }
    bool Tilefound = 0;
    float maxDistance = 100.0f;
    float Distance = 0;

    //std::cout << "raylengt:" << RayLength1d.x << "  y:" << RayLength1d.y << '\n';
    //int i = 0;

    while (!Tilefound and Distance < maxDistance)
    {   //walk  

        if (RayLength1d.x < RayLength1d.y)
        {
            MapCheck.x += Step.x;//moves to rhe next cell or stores that we  go to next cell
            Distance = RayLength1d.x;
            RayLength1d.x += unitStepSize.x;


        }
        else {
            MapCheck.y += Step.y;//moves to rhe next cell or stores that we  go to next cell
            Distance = RayLength1d.y;
            RayLength1d.y += unitStepSize.y;
        }
        if (MapCheck.x >= 0 && MapCheck.x < numOfCellX && MapCheck.y >= 0 && MapCheck.y < numOfCellY)
        {
            if (grids[MapCheck.x + MapCheck.y * numOfCellX].type == 1)//and here is the main step to check  this also need correction           cor
            {
                
                grids[MapCheck.x + MapCheck.y * numOfCellX].Color= PURPLE;
                Tilefound = 1;
                

            }
            else { Tilefound = 0;// grids[MapCheck.x + MapCheck.y * numOfCellX].Color = DARKPURPLE;
            }

        }
        
    }

   // i += 1;
    if (Tilefound)
    {
        std::cout << "tile Found    x:"<< MapCheck.x<<"  y:"<< MapCheck.y<<'\n';
        intersection.x = rayStart.x+ RayDirection.x * Distance;
        intersection.y = rayStart.y + RayDirection.y * Distance;
        //intersection.x = (MapCheck.x)*30; intersection.y = (MapCheck.y)*30;
    }

    return Tilefound;

}


bool RaycastWithsnoAlgo(float mouse_x, float mouse_y, float endX, float endY) 
{   
    Vector2 RayDirection = normalise((mouse_x - endX), (mouse_y - endY));
    bool TileFound = 0;
    float distance = 1;
    float madistance = 100;
    while (!TileFound || distance<madistance  )
    {
        
        RayDirection.x *= distance;
        distance += 1;
    }
    return false;

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

 
        
         

        
     
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        

        for (int x = 0; x < screenWidth; x += cellSize) {
            for (int y = 0; y < screenHeight; y += cellSize) {
                
                DrawCircle(mouse_x, mouse_y, 10, GREEN);//player
                DrawCircle(endX, endY, 10, ORANGE);// ending postion

                if(IsKeyDown(KEY_W)) {endY -= 0.03;}
                if (IsKeyDown(KEY_S)){endY += 0.03;}
                if (IsKeyDown(KEY_A)){endX -= 0.03;}
                if (IsKeyDown(KEY_D)){endX += 0.03;}
                if (endX < 0) { endX = 0; };
                if (endY < 0) { endY = 0; }
                if (endX >= 600) { endX = 600; }
                if (endY >= 600) { endY = 600; }

                if ((mouse_x >= x && mouse_x <= x + cellSize) && (mouse_y >= y && mouse_y <= y + cellSize))
                {
                   
                    if (IsMouseButtonDown(1)) {// changes the color and type of all cell based on user input;
                        grids[(x / cellSize) + (y/ cellSize) * numOfCellY].type = !grids[(x/ cellSize) + (y/ cellSize) * numOfCellY].type;
                        if (grids[(x/ cellSize) + (y/ cellSize) * numOfCellY].type == 0) { grids[(x / cellSize) + (y / cellSize) * numOfCellY].Color = GRAY; }
                        else if (grids[(x / cellSize) + (y / cellSize) * numOfCellY].type == 1) { grids[(x / cellSize) + (y/ cellSize) * numOfCellY].Color = DARKPURPLE; }
                    }
                }







                DrawRectangle(x, y, cellSize - 1, cellSize - 1, grids[(x / cellSize) + (y / cellSize) * numOfCellY].Color);//Draws all the Rectangle



                if (setStart && setEnd)
                {
               
                    if (IsMouseButtonDown(0)) {
                        bool found =RaycastWithDDA(mouse_x, mouse_y, endX, endY);
                        DrawLine(mouse_x, mouse_y, endX, endY, BLUE);
                        //std::cout << "mouse Postion x:" << mouse_x << "  Y:" << mouse_y << "  endx:" << endX << "   endY:" << endY << '\n';
                        if (found)
                        {
                            DrawCircleV(intersection, 5, ORANGE);
                            //std::cout << intersection.x << " " << intersection.y << '\n';


                        }
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
