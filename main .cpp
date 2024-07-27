
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

