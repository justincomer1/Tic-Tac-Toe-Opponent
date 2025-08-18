#include "Board.h"

class Outcome_Calculator
{

private:
	 
	static Mark opposite(Mark mark);
	static void outcome(Board* gameBoard, Mark mark);
	 
public:
	static int determineIfOneMoveAway(Board* gameBoard); 
	static void determineOutcomes(Board* gameBoard, std::vector<std::vector<float>>* outcomes);
};

