#ifndef PLAYER2_H
#define PLAYER2_H

#include <iostream>
#include <cstdlib>
#include <ctime>

extern const int shipLength;
extern const int shipCount;
extern const int boardLength;
extern const int nearbyTiles;
extern double heatmap[8][8];
extern int shipTiles1;
extern int lastHit_x;
extern int lastHit_y;

class Player2 {
public:
    int Board2[8][8] = {0};
    void showBoard();
    void showBoard2();
    void Setup2();
    void updateHeatMap();
    void Turn2(int& x2, int& y2);
};

extern Player2 p2;

#endif