#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Player1.h"
#include "Player2.h"

const int shipLength = 3;
const int shipCount = 5;
const int boardLength = 8;
const int nearbyTiles = 4;
double heatmap[8][8] = {0};
int shipTiles1 = shipCount * shipLength;
int shipTiles2 = shipCount * shipLength;
int lastHit_x = -1;
int lastHit_y = -1;

Player1 p1;
Player2 p2;

int main() {
    srand(time(0));
    std::cout << "This game is related to Battleship. To play you must first place 5 ships (each is 3 tiles in length) on an 8*8 grid.\n"
              << "You can enter coordinates from 1,1 to 8,8. The game ends when a player takes out all the other player's ships.\n"
              << "This is an example of the board the game uses (the coordinates of each square are on the sides of the board).\n"
              << "On the board will be certain values. "
              << "0 means the tile is either water or a ship that still stands. 1 means the tile has a ship standing on it.\n"
              << "2 means the tile has a ship that was hit on it. 3 means the tile is water that was hit.\n";
    p2.updateHeatMap();
    p1.showBoard1();
    p1.Setup1();
    p2.Setup2();

    int x1, y1, x2, y2;
    while (shipTiles1 > 0 && shipTiles2 > 0) {
        p1.Turn1(x1, y1);
        if (shipTiles2 == 0) {
            std::cout << "Player 1 wins!\n";
            return 0;
        }
        
        p2.Turn2(x2, y2);
        if (shipTiles1 == 0) {
            std::cout << "Player 2 wins!\n";
            return 0;
        }
    }

    return 0;
}