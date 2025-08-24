#include "Opponent.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

void Opponent::rememberMoves() {

    for (auto move = movesThisGame.begin(); move != movesThisGame.end(); ++move) {
        if (movesWins.find(move->first) == movesWins.end()) 
            movesWins[move->first] = std::vector<int>(possibleMoves.size(), 0);

        if(winner)
            movesWins[move->first][move->second] += 1;
        else
            movesWins[move->first][move->second] -= 1;
    }

    std::ofstream pastMoves;
    pastMoves.open("moves.csv");
    for (auto moveWins = movesWins.begin(); moveWins != movesWins.end(); ++moveWins) {
		std::string key = moveWins->first;
		std::vector<int> wins = moveWins->second;
		pastMoves << key << ",";
        for(auto win : wins) {
            pastMoves << win << ",";
		}
		pastMoves << "\n";
    }
}

void Opponent::learnFromPastMoves() {
    std::ifstream file("moves.csv");
    if (!file.is_open())
        return;

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);

        std::string key;
        std::getline(ss, key, ',');

        int record = 0;
		std::vector<int> recordVec;
        std::string recordStr;
        while (std::getline(ss, recordStr, ',')) {
            try {
                record = std::stoi(recordStr);
                recordVec.push_back(record);
            }
            catch (const std::invalid_argument& e) {
                std::cout << "Invalid argument: " << e.what() << std::endl;
                continue; // Skip this line if conversion fails
            }
        }
		
        movesWins[key] = recordVec;
    }

    std::cout << movesWins.size() << std::endl; 
}

Opponent::Opponent(std::vector<std::vector<int>>* possibleMoves) {
	this->possibleMoves = *possibleMoves;
	learnFromPastMoves();
}

Opponent::~Opponent() {
    rememberMoves();
    std::cout << "Opponent destructor called" << std::endl;
}


bool Opponent::yourMove(Board* gameBoard) {
    gameBoard->toString(); 

	int move = determineMove(gameBoard);
	
	int y = possibleMoves[move][0];
	int x = possibleMoves[move][1];
	
    if (gameBoard->checkForWinner(y, x, Mark::O)) {
        winner = true;
        return true;
    }
	
	std::string* key = gameBoard->getKey();
    movesThisGame[*key] = move; 
	delete key;

	gameBoard->set_mark(y, x, Mark::O);
    return false; 
}

int Opponent::determineMove(Board* gameBoard) {
    std::cout << "Calculating possible moves....." << std::endl;
    
    int oneMove = Outcome_Calculator::determineIfOneMoveAway(gameBoard);
    if (oneMove != -1) return oneMove;

	std::string* key = gameBoard->getKey();
    std::vector<std::vector<float>> outcomes(Dem::ROWS, std::vector<float>(Dem::COLS, 0));
	std::priority_queue<PossibleMove, std::vector<PossibleMove>, MoveComparator> bestMoves;
    Outcome_Calculator::determineOutcomes(gameBoard, &outcomes);

	for (int spot = 0; spot < possibleMoves.size(); spot++) {
        int wins = 0;
        if (movesWins.find(*key) != movesWins.end()) {
            std::vector<int> moves = movesWins[*key];
            wins = movesWins[*key][spot];
        }
                
       bestMoves.push(PossibleMove(spot, outcomes[possibleMoves[spot][0]][possibleMoves[spot][1]], wins));
    }

    delete key;
    return bestMoves.top().spot;
}