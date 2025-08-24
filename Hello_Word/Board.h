#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <cstdlib>
#include <string>
#include <iostream>

const enum Dem : int {
    ROWS = 3,
    COLS = 3
};

const enum Mark : char {
    EMPTY = '_',
    X = 'X',
    O = 'O'

};


class Board {
private:
    std::vector<std::vector<Mark>> gameBoard;
    char toMarkString(const Mark mark, const char num) const {
        if (mark == Mark::EMPTY) return num;
		return mark;
    }


public:
    Board() {
        std::vector<std::vector<Mark>> gameBoard(ROWS, std::vector<Mark>(COLS, Mark::EMPTY));
        this->gameBoard = gameBoard;
    }
    void set_mark(const int y, const int x, const Mark mark) { gameBoard[y][x] = mark; }
    Mark get_mark(const int y, const int x) const { return gameBoard[y][x]; }
    bool checkForWinner(const int y, const int x, Mark mark) {
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

    std::string* getKey() const {
        std::string key = "";
        for (int y = 0; y < Dem::ROWS; y++) {
            for (int x = 0; x < Dem::COLS; x++) {
				key += gameBoard[y][x];
            }
        }
        
		return new std::string(key);
	}

    void toString() const {
        std::cout << std::endl;
        std::cout << toMarkString(gameBoard[0][0], '1') << "|" << toMarkString(gameBoard[0][1], '2') << "|" << toMarkString(gameBoard[0][2], '3') << std::endl;
        std::cout << "------" << std::endl;
        std::cout << toMarkString(gameBoard[1][0], '4') << "|" << toMarkString(gameBoard[1][1], '5') << "|" << toMarkString(gameBoard[1][2], '6') << std::endl;
        std::cout << "------" << std::endl;
        std::cout << toMarkString(gameBoard[2][0], '7') << "|" << toMarkString(gameBoard[2][1], '8') << "|" << toMarkString(gameBoard[2][2], '9') << std::endl;
        std::cout << std::endl; 
    }
};


#endif
