#include "Board.h"
#include "Outcome_Calculator.h"

#include <cassert>
#include <iostream>


int determineMove(Board* gameBoard) {
    std::cout << "Calculating possible moves....." << std::endl; 
    
    int oneMove = Outcome_Calculator::determineIfOneMoveAway(gameBoard);
    if (oneMove != -1) return oneMove; 
    
    std::vector<std::vector<float>> outcomes = Outcome_Calculator::determineOutcomes(gameBoard);
    int move = -1;
    int move_index = 0;
    float percentage = 0; 
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
             
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

std::vector<std::vector<int>> populateMoves() {
    std::vector<std::vector<int>> moves(9, std::vector<int>(2, 0));
    int index = 0; 
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            moves[index][0] = y;
            moves[index][1] = x;
            index++; 
        }
    }

    return moves; 
}


/* 
* TODO:
* 1. clean up main function, possibly break up into a sepaqrate class called game? 
* 2. Handle when there is no way for computer to win, have it pick a valid position 
* 3. pass 2d vectors using pointers 
* 
*3. peristant memory 
*
*/
int main()
{
    int moves_left = 9;
    bool winner = false; 

    Board gameBoard; 
    std::vector<std::vector<int>> possibleMoves = populateMoves(); 
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