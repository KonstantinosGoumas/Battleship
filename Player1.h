#ifndef PLAYER1_H
#define PLAYER1_H

#include <iostream>
#include <cstdlib>
#include <ctime>

extern const int shipLength;
extern const int shipCount;
extern const int boardLength;
extern int shipTiles2;

class Player1 {
public:
    int Board1[8][8] = {0};
    void showBoard2();
    void showBoard1();
    void Setup1();
    void Turn1(int& x1, int& y1);
    void resetBoards();
};

extern Player1 p1;

#endif