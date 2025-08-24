#ifndef OPPONENT_H
#define OPPONENT_H

#include "Outcome_Calculator.h";
#include <vector>
#include <unordered_map>
#include<queue>
class Opponent
{
private:
	std::unordered_map<std::string, std::vector<int>> movesWins;
	std::unordered_map<std::string, int> movesThisGame;
	std::vector<std::vector<int>> possibleMoves;

	struct PossibleMove {
		int spot;
		float percentage;
		int wins;

		PossibleMove(int s, float p, int w) : spot(s), percentage(p), wins(w) {}
	};

	struct MoveComparator {
		bool operator()(const PossibleMove& a, const PossibleMove& b) const {
			if (a.wins != b.wins)
				return a.wins < b.wins; // Higher wins has higher priority

			return a.percentage < b.percentage; // Higher percentage has higher priority
		}
	};
	
	bool winner = false;
	void rememberMoves(); 
	void learnFromPastMoves(); 
	int determineMove(Board* gameBoard); 
public:
	Opponent(std::vector<std::vector<int>>* possibleMoves);
	~Opponent(); 
	bool yourMove(Board* gameBoard);


};

#endif OPPONENT_H

