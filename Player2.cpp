#include "Player2.h"
#include "Player1.h"

void Player2::showBoard2() {
    std::cout << "Board 2:\n" << "  1 2 3 4 5 6 7 8\n";
    for (int i = 0; i < boardLength; i++) {
        std::cout << i + 1 << " ";
        for (int j = 0; j < boardLength; j++) {
            if (p1.Board1[i][j] != 1) {
                if (p1.Board1[i][j] == 0) {
                    std::cout << "\033[36m0 \033[0m";
                } else if (p1.Board1[i][j] == 2) {
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

void Player2::showBoard() {
    std::cout << "\n" << "  1 2 3 4 5 6 7 8" << "\n";
    for (int i = 0; i < boardLength; i++) {
        std::cout << i + 1 << " ";
        for (int j = 0; j < boardLength; j++) {
            if (Board2[i][j] == 0) {
                std::cout << "\033[36m0 \033[0m";
            } else if (Board2[i][j] == 1) {
                std::cout << "\033[1;33m1 \033[0m";
            } else if (Board2[i][j] == 2) {
                std::cout << "\033[31m2 \033[0m";
            } else {
                std::cout << "\033[35m3 \033[0m";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void Player2::Setup2() {
    int start_x, start_y;
    bool orient;

    for (int shipsPlaced = 0; shipsPlaced < shipCount; shipsPlaced++) {
        bool valid = false;

        while (!valid) {
            orient = std::rand() % 2;

            if (orient == 0) {
                start_y = std::rand() % (boardLength - shipLength);
                start_x = std::rand() % boardLength;

                if (start_y >= 0 && start_y + shipLength <= boardLength && start_x >= 0 && start_x < boardLength) {
                    valid = true;
                    for (int i = start_y; i < start_y + shipLength; i++) {
                        if (Board2[i][start_x] == 1) {
                            valid = false;
                            break;
                        }
                    }
                    if (valid) {
                        for (int i = start_y; i < start_y + shipLength; i++) {
                            Board2[i][start_x] = 1;
                        }
                    }
                }
            } else {
                start_x = std::rand() % (boardLength - shipLength);
                start_y = std::rand() % boardLength;

                if (start_y >= 0 && start_y < boardLength && start_x >= 0 && start_x + shipLength <= boardLength) {
                    valid = true;
                    for (int i = start_x; i < start_x + shipLength; i++) {
                        if (Board2[start_y][i] == 1) {
                            valid = false;
                            break;
                        }
                    }
                    if (valid) {
                        for (int i = start_x; i < start_x + shipLength; i++) {
                            Board2[start_y][i] = 1;
                        }
                    }
                }
            }
        }
    }
}

void Player2::Turn2(int& x2, int& y2) {
    bool valid = false;

    while (!valid) {
        updateHeatMap();

        double totalProbability = 0.0;
        for (int r = 0; r < boardLength; r++) {
            for (int c = 0; c < boardLength; c++) {
                totalProbability += heatmap[r][c];
            }
        }

        double randomValue = static_cast<double>(rand()) / RAND_MAX * totalProbability;
        double accumulatedProbability = 0.0;

        for (int r = 0; r < boardLength; r++) {
            for (int c = 0; c < boardLength; c++) {
                accumulatedProbability += heatmap[r][c];
                if (accumulatedProbability >= randomValue) {
                    x2 = c;
                    y2 = r;
                    valid = true;
                    break;
                }
            }
            if (valid) break;
        }

        if (p1.Board1[y2][x2] == 1) {
            p1.Board1[y2][x2] = 2;
            shipTiles1--;
            lastHit_x = x2;
            lastHit_y = y2;
            p1.resetBoards();
            std::cout << "Player 2 striked at: [" << x2 + 1 << ", " << y2 + 1 << "] \nHit!\n";
        } else if (p1.Board1[y2][x2] == 2 || p1.Board1[y2][x2] == 3) {
            valid = false;
        } else {
            p1.Board1[y2][x2] = 3;
            p1.resetBoards();
            std::cout << "Player 2 striked at: [" << x2 + 1 << ", " << y2 + 1 << "] \nMiss!\n";
            lastHit_x = -1;
            lastHit_y = -1;
        }
    }
}

void Player2::updateHeatMap() {
    double totalProbability = 0.0;

    for (int r = 0; r < boardLength; r++) {
        for (int c = 0; c < boardLength; c++) {

            int leftEdge = std::max(0, c - (shipLength - 1));
            int rightEdge = std::min(boardLength - shipLength, c);
            int possibleHorizontalPlacements = rightEdge - leftEdge + 1;

            int topEdge = std::max(0, r - (shipLength - 1));
            int bottomEdge = std::min(boardLength - shipLength, r);
            int possibleVerticalPlacements = bottomEdge - topEdge + 1;

            int possiblePlacements = possibleVerticalPlacements + possibleHorizontalPlacements;
            heatmap[r][c] = static_cast<double>(possiblePlacements);
            totalProbability += heatmap[r][c];
      
            heatmap[r][c] /= totalProbability;

            if (p1.Board1[r][c] == 2 || p1.Board1[r][c] == 3) {
                heatmap[r][c] = 0.0;
            }
        }
    }

    if (lastHit_x != -1 && lastHit_y != -1) {
        int targetR1 = lastHit_y + 1;
        int targetR2 = lastHit_y - 1;
        int targetC1 = lastHit_x + 1;
        int targetC2 = lastHit_x - 1;
        double increase = 0.1;

        if (targetR1 >= 0 && targetR1 < boardLength) {
            heatmap[targetR1][lastHit_x] = std::min(heatmap[targetR1][lastHit_x] + increase, 1.0);
        }
        if (targetR2 >= 0 && targetR2 < boardLength) {
            heatmap[targetR2][lastHit_x] = std::min(heatmap[targetR2][lastHit_x] + increase, 1.0);
        }
        if (targetC1 >= 0 && targetC1 < boardLength) {
            heatmap[lastHit_y][targetC1] = std::min(heatmap[lastHit_y][targetC1] + increase, 1.0);
        }
        if (targetC2 >= 0 && targetC2 < boardLength) {
            heatmap[lastHit_y][targetC2] = std::min(heatmap[lastHit_y][targetC2] + increase, 1.0);
        }

        double remainingProbability = 0.0;
        for (int r = 0; r < boardLength; r++) {
            for (int c = 0; c < boardLength; c++) {
                if ((r != targetR1 || c != lastHit_x) && (r != targetR2 || c != lastHit_x) &&
                    (r != lastHit_y || c != targetC1) && (r != lastHit_y || c != targetC2)) {
                    remainingProbability += heatmap[r][c];
                }
            }
        }

        double adjustmentFactor = (1.0 - (heatmap[targetR1][lastHit_x] + heatmap[targetR2][lastHit_x] +
                                          heatmap[lastHit_y][targetC1] + heatmap[lastHit_y][targetC2])) / remainingProbability;

        for (int r = 0; r < boardLength; r++) {
            for (int c = 0; c < boardLength; c++) {
                if ((r != targetR1 || c != lastHit_x) && (r != targetR2 || c != lastHit_x) &&
                    (r != lastHit_y || c != targetC1) && (r != lastHit_y || c != targetC2)) {
                    heatmap[r][c] *= adjustmentFactor;
                }
                std::cout << heatmap[r][c] << " ";
            }
            std::cout << "\n";
        }
    }
}