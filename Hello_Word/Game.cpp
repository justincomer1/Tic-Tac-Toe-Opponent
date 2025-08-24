#include "Board.h"
#include "Opponent.h" 

#include <cassert>




void populateMoves(std::vector<std::vector<int>>* possibleMoves) {
    
    int index = 0; 
    for (int y = 0; y < Dem::ROWS; y++) {
        for (int x = 0; x < Dem::COLS; x++) {
            (*possibleMoves)[index][0] = y;
            (*possibleMoves)[index][1] = x;
            index++; 
        }
    }
}


/* 
* TODO:
* 1. draw a line when there is a winner across the winning line
* 
*
*/
int main()
{
    Board gameBoard;

    std::vector<std::vector<int>> possibleMoves(9, std::vector<int>(2, 0));
    populateMoves(&possibleMoves);

    Opponent opponent(&possibleMoves);

    int moves_left = 9; 
    int move = 0;

    while (moves_left > 0) {
        
        gameBoard.toString(); 
        std::cout << "Enter your move: ";
        std::cin >> move;
       
        move -= 1; 

        int y = possibleMoves[move][0];
        int x = possibleMoves[move][1];

        if (gameBoard.checkForWinner(y, x, Mark::X)) {
            std::cout << "PLAYER WINS!!!!!!" << std::endl;
            break; 
        }

        gameBoard.set_mark(y, x, Mark::X); 
        moves_left--;

        if (moves_left == 0)
            break; 


        if (opponent.yourMove(&gameBoard)) {
            std::cout << "COMPUTER WINS!!!!!!" << std::endl;
            break;
        }

        moves_left--;

    }

    if (moves_left == 0)
        std::cout << "ITS A TIE!!!!!!" << std::endl;
    
}