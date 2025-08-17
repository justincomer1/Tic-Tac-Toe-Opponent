#include "Outcome_Calculator.h"

float games = 0;
float wins = 0;

//move to header 
Mark Outcome_Calculator::opposite(Mark mark) {
    if (mark == Mark::X) return Mark::O;
    return Mark::X;
}


int Outcome_Calculator::determineIfOneMoveAway(Board* gameBoard) {

    int index = 0; 
    //see if you are one move away 
    for (int y = 0; y < Dem::ROWS; y++) {
        for (int x = 0; x < Dem::COLS; x++) {
            if (gameBoard->get_mark(y, x) == Mark::EMPTY && gameBoard->checkForWinner(y, x, Mark::O))
                return index;

            index++; 

        }
    }

    index = 0;
    //are they one move away? 
    for (int y = 0; y < Dem::ROWS; y++) {
        for (int x = 0; x < Dem::COLS; x++) {
            if (gameBoard->get_mark(y, x) == Mark::EMPTY && gameBoard->checkForWinner(y, x, Mark::X))
                return index;

            index++;
        }
    }
    return -1; 
}

void Outcome_Calculator::determineOutcomes(Board* gameBoard, std::vector<std::vector<float>>* outcomes) {

    //determine all possible outcomes 
    for (int y = 0; y < Dem::ROWS; y++) {
        for (int x = 0; x < Dem::COLS; x++) {
            if (gameBoard->get_mark(y, x) != Mark::EMPTY)
                continue;

            gameBoard->set_mark(y, x, Mark::O);
            outcome(gameBoard, Mark::X);
            if (games == 0 || wins == 0)
                (*outcomes)[y][x] = -100;
            else {
                std::cout << games << " ";
                std::cout << wins << " ";
                std::cout << wins / games;
                (*outcomes)[y][x] = wins / games;
            }

            std::cout << std::endl; 
            games = 0;
            wins = 0;
            gameBoard->set_mark(y, x, Mark::EMPTY);
        }
    }


}


//move to header 
void Outcome_Calculator::outcome(Board* gameBoard, Mark mark) {

    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (gameBoard->get_mark(y, x) != Mark::EMPTY)
                continue;

            if (gameBoard->checkForWinner(y, x, mark)) {
                if (mark == Mark::O) wins += 1;
                games += 1;
                continue;
            }

            gameBoard->set_mark(y, x, mark);
            outcome(gameBoard, opposite(mark));
            gameBoard->set_mark(y, x, Mark::EMPTY);

        }
    }

}
