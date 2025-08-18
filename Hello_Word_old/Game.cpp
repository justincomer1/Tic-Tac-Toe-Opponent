#include "Board.h"
#include "Outcome_Calculator.h"

#include <cassert>
#include <iostream>


int determineMove(Board* gameBoard) {
    std::cout << "Calculating possible moves....." << std::endl; 
    
    int oneMove = Outcome_Calculator::determineIfOneMoveAway(gameBoard);
    if (oneMove != -1) return oneMove; 
    
    std::vector<std::vector<float>> outcomes(Dem::ROWS, std::vector<float>(Dem::COLS, 0));
    Outcome_Calculator::determineOutcomes(gameBoard, &outcomes);
    int move = -1;
    int move_index = 0;
    float percentage = 0; 
    for (int y = 0; y < Dem::ROWS; y++) {
        for (int x = 0; x < Dem::COLS; x++) {
             
            //set to first valid move, after check for better 
            if ((gameBoard->get_mark(y, x) == Mark::EMPTY && move == -1) || outcomes[y][x] > percentage) {
                std::cout << "hello: " << outcomes[y][x] << std::endl; 
                percentage = outcomes[y][x];
                move = move_index;
            }
         
            move_index++; 
        }
    }
    return move; 
}

void populateMoves(std::vector<std::vector<int>>* possibleMoves) {
    
    int index = 0; 
    for (int y = 0; y < Dem::ROWS; y++) {
        for (int x = 0; x < Dem::COLS; x++) {
            (*possibleMoves)[index][0]  = y;
            (*possibleMoves)[index][1] = x;
            index++; 
        }
    }
}


/* 
* TODO:
* 1. clean up main function, possibly break up into a sepaqrate class called game? 
* 4. draw a line when there is a winner across the winning line
* 
*3. peristant memory 
* 4. find a way to track winning and losing moves so that the it can learn over time 
*
*/
int main()
{
    int moves_left = 9;
    bool winner = false; 

    Board gameBoard; 
    std::vector<std::vector<int>> possibleMoves(9, std::vector<int>(2, 0));
	populateMoves(&possibleMoves);
    int move = 0;

    while (true) {
        

        gameBoard.toString(); 
        std::cout << "Enter your move: ";
        std::cin >> move;
       
        move -= 1; 

        int y = possibleMoves[move][0];
        int x = possibleMoves[move][1];

        if (gameBoard.checkForWinner(y, x, Mark::X)) {
            winner = true; 
            std::cout << "PLAYER WINS!!!!!!" << std::endl;
            break; 
        }

        gameBoard.set_mark(y, x, Mark::X); 
        moves_left--;

        if (moves_left == 0)
            break; 

        move = determineMove(&gameBoard);
       
        y = possibleMoves[move][0];
        x = possibleMoves[move][1];

        if (gameBoard.checkForWinner(y, x, Mark::O)) {
            winner = true;
            std::cout << "COMPUTER WINS!!!!!!" << std::endl;
            break;
        }

        gameBoard.set_mark(y, x, Mark::O);
        moves_left--;

    }

    if (moves_left == 0 && !winner)
        std::cout << "ITS A TIE!!!!!!" << std::endl;
    
    
}