#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <cstdlib>
#include <string>
#include <iostream>

enum class Mark {
    EMPTY = 0,
    X = 1,
    O = -1

};


class Board {
private:
    std::vector<std::vector<Mark>> gameBoard;
    std::string toMarkString(Mark mark, std::string num) {
        if (mark == Mark::EMPTY) return num;
        if (mark == Mark::X) return "X";
        return "O";
    }


public:
    Board() {
        std::vector<std::vector<Mark>> gameBoard(3, std::vector<Mark>(3, Mark::EMPTY));
        this->gameBoard = gameBoard;
    }
    void set_mark(int y, int x, Mark mark) { gameBoard[y][x] = mark; }
    Mark get_mark(int y, int x) { return gameBoard[y][x]; }
    bool checkForWinner(int y, int x, Mark mark) {
        //check horizontal 
        gameBoard[y][x] = mark;
        bool won = false;
        if (gameBoard[y][0] == mark && gameBoard[y][1] == mark && gameBoard[y][2] == mark)
            won = true;
        //check vert
        if (gameBoard[0][x] == mark && gameBoard[1][x] == mark && gameBoard[2][x] == mark)
            won = true;

        //check diag
        if (gameBoard[0][0] == mark && gameBoard[1][1] == mark && gameBoard[2][2] == mark)
            won = true;

        //check diag
        if (gameBoard[2][0] == mark && gameBoard[1][1] == mark && gameBoard[0][2] == mark)
            won = true;

        gameBoard[y][x] = Mark::EMPTY; 
        return won;
    }

    void toString() {
        std::cout << std::endl;
        std::cout << toMarkString(gameBoard[0][0], "1") << "|" << toMarkString(gameBoard[0][1], "2") << "|" << toMarkString(gameBoard[0][2], "3") << std::endl;
        std::cout << "------" << std::endl;
        std::cout << toMarkString(gameBoard[1][0], "4") << "|" << toMarkString(gameBoard[1][1], "5") << "|" << toMarkString(gameBoard[1][2], "6") << std::endl;
        std::cout << "------" << std::endl;
        std::cout << toMarkString(gameBoard[2][0], "7") << "|" << toMarkString(gameBoard[2][1], "8") << "|" << toMarkString(gameBoard[2][2], "9") << std::endl;
        std::cout << std::endl; 
    }
};


#endif
