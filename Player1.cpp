#include "Player1.h"
#include "Player2.h"

void Player1::showBoard2() {
    std::cout << "Board 2:\n" << "  1 2 3 4 5 6 7 8\n";
    for (int i = 0; i < boardLength; i++) {
        std::cout << i + 1 << " ";
        for (int j = 0; j < boardLength; j++) {
            if (p2.Board2[i][j] != 1) {
                if (p2.Board2[i][j] == 0) {
                    std::cout << "\033[36m0 \033[0m";
                } else if (p2.Board2[i][j] == 2) {
                    std::cout << "\033[31m2 \033[0m";
                } else {
                    std::cout << "\033[35m3 \033[0m";
                }
            } else {
                std::cout << "\033[36m0 \033[0m";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void Player1::showBoard1() {
    std::cout << "\nBoard 1:\n" << "  1 2 3 4 5 6 7 8\n";
    for (int i = 0; i < boardLength; i++) {
        std::cout << i + 1 << " ";
        for (int j = 0; j < boardLength; j++) {
            if (Board1[i][j] == 0) {
                std::cout << "\033[36m0 \033[0m";
            } else if (Board1[i][j] == 1) {
                std::cout << "\033[1;33m1 \033[0m";
            } else if (Board1[i][j] == 2) {
                std::cout << "\033[31m2 \033[0m";
            } else {
                std::cout << "\033[35m3 \033[0m";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void Player1::resetBoards(){
    system("cls");
    p1.showBoard1();
    p1.showBoard2();
}

void Player1::Setup1() {
    int input_x, input_y;
    char orient;

    for (int shipsPlaced = 0; shipsPlaced < shipCount; shipsPlaced++) {
        bool valid = false;

        while (!valid) {
            std::cout << "Player 1, place your ship (" << shipCount - shipsPlaced << " remaining). Enter start [x y] and orientation [h/v]: ";
            std::cin >> input_x >> input_y >> orient;

            if (std::cin.fail() || input_x < 1 || input_x > boardLength || input_y < 1 || input_y > boardLength || (orient != 'h' && orient != 'v')) {
                std::cout << "Invalid input! Please enter numbers (1-8) and orientation (h or v).\n";
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                continue;
            }
            int start_x = input_x - 1;
            int start_y = input_y - 1;
            bool validPlacement = true;

            if (orient == 'v') {
                if (start_y + shipLength > boardLength) {
                    std::cout << "Ship goes out of bounds. Try again.\n";
                    continue;
                }
                for (int i = start_y; i < start_y + shipLength; i++) {
                    if (Board1[i][start_x] == 1)
                        validPlacement = false;
                }
            } else {
                if (start_x + shipLength > boardLength) {
                    std::cout << "Ship goes out of bounds. Try again.\n";
                    continue;
                }
                for (int i = start_x; i < start_x + shipLength; i++) {
                    if (Board1[start_y][i] == 1)
                        validPlacement = false;
                }
            }

            if (!validPlacement) {
                std::cout << "Space occupied. Try again.\n";
                continue;
            }

            if (orient == 'v') {
                for (int i = start_y; i < start_y + shipLength; i++) {
                    Board1[i][start_x] = 1;
                }
            } else {
                for (int i = start_x; i < start_x + shipLength; i++) {
                    Board1[start_y][i] = 1;
                }
            }

            valid = true;
        }

        system("cls");
        p1.showBoard1();
    }
}

void Player1::Turn1(int& x1, int& y1) {
    int x, y;
    bool valid = false;
    while (!valid) {
        std::cout << "Player 1, enter attack coordinates [x y]: ";
        std::cin >> x >> y;

        if (std::cin.fail() || x < 1 || x > boardLength || y < 1 || y > boardLength) {
            std::cout << "Invalid input. Please enter numbers between 1 and 8.\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        x1 = x - 1;
        y1 = y - 1;

        if (p2.Board2[y1][x1] == 2 || p2.Board2[y1][x1] == 3) {
            std::cout << "You already targeted this location. Try again.\n";
            continue;
        }

        if (p2.Board2[y1][x1] == 1) {
            p2.Board2[y1][x1] = 2;
            shipTiles2--;
        } else {
            p2.Board2[y1][x1] = 3;
        }

        valid = true;
    }
}