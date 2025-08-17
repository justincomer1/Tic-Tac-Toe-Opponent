#include "Board.h"

class Outcome_Calculator
{

private:
	 
	static Mark opposite(Mark mark);
	static void outcome(Board* gameBoard, Mark mark);
	 
public:
	static int determineIfOneMoveAway(Board* gameBoard); 
	static std::vector<std::vector<float>> determineOutcomes(Board* gameBoard); 
};

