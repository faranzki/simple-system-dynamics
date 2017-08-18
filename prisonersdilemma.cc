#include <vector>
#include <iostream>
#include <stdlib.h> 

int play(int strategy, int opponent_last_move, int trigger_grim){
	// 1 - defect; 0 - cooperate
	if (strategy == 1){
		return 1;
	}
	else if (strategy == 2){
		return 0;
	}
	else if (strategy == 3){
		if (opponent_last_move == 1){
			return 1;
		}
		else {
			return 0;
		}
	}
	else if (strategy == 4){
		if (trigger_grim >= 1){
			return 1;
		}
		else {
			return 0;
		}
	}
	if (strategy == 5){
		return rand()% 2;
	}

	else {
		std::cout << "Invalid strategy" << std::endl;
		return 0;
	}
}



int main(int argc, char ** charv){

std::cout << "Iterative prisoners' dilemma with 2 players. All strategies will be played against each other." << std::endl;
std::cout << std::endl;
std::cout << "Strategies: " << std::endl; 
std::cout << "1 - always defect" << std::endl;
std::cout << "2 - always cooperate" << std::endl;
std::cout << "3 - tit for tat" << std::endl;
std::cout << "4 - grim" << std::endl;
std::cout << "5 - random 0.5" << std::endl;
std::cout << std::endl;
std::cout << "Payoff matrix:" << std::endl;
std::cout << "all defect = 1" << std::endl;
std::cout << "all cooperate = 3" << std::endl;
std::cout << "one defects - defectant = 5" << std::endl;
std::cout << "one defects - cooperator = 0" << std::endl;
std::cout << std::endl;

//Number of iterations:
int n_iter;
std::cout << "Please indicate the number of iterations: " << std::endl;
std::cin >> n_iter;

//Set up strategies's scores:
std::vector<int> strategies_scores(5);

//Set up players:
for (int n = 1; n < 6; n++){
	int strategy_1 = n;
	for (int m = n; m < 6; m++){
		int strategy_2 = m;
		std::cout << "Strategy player 1 is " << n << " and strategy player 2 is " << m << std::endl;
		//Set up behaviour records:
		std::vector<std::vector<int> > behaviour_record(2);		
		//Set up players' payoff records:
		std::vector<std::vector<int> > payoff_records(2);		

		//Start tournament:		

		//first round of tournament:

		//Play		
		int behaviour1 = play(strategy_1, 0, 0);
		int behaviour2 = play(strategy_2, 0, 0);
		//Update behaviour record
		behaviour_record[0].push_back(behaviour1);
		behaviour_record[1].push_back(behaviour2);
		//Update payoff record
		if (behaviour_record[0][0] == 0 && behaviour_record[1][0] == 0){
			payoff_records[0].push_back(3);
			payoff_records[1].push_back(3);
		}
		else if (behaviour_record[0][0] == 0 && behaviour_record[1][0] == 1){
			payoff_records[0].push_back(0);
			payoff_records[1].push_back(5);
		}
		else if (behaviour_record[0][0] == 1 && behaviour_record[1][0] == 0){
			payoff_records[0].push_back(5);
			payoff_records[1].push_back(0);
		}
		else if (behaviour_record[0][0] == 1 && behaviour_record[1][0] == 1){
			payoff_records[0].push_back(1);
			payoff_records[1].push_back(1);
		}
		else {
			std::cout << "Invalid behaviour combination" << std::endl;
		}

		//Calculate strategies' scores
		strategies_scores[n] += payoff_records[0][0];
		strategies_scores[m] += payoff_records[1][0];

		//Consecutive rounds of tournament:		

		for (int i = 1; i < n_iter; i++){
			//Sum up previous strategies of both players to identify the grim trigger
			int sum_strategies_player1;
			std::vector<int> behaviour_player1 = behaviour_record[0];
			for(std::vector<int>::iterator it = behaviour_player1.begin(); it != behaviour_player1.end(); ++it){
		    	sum_strategies_player1 += *it;
			}
			int sum_strategies_player2;
			std::vector<int> behaviour_player2 = behaviour_record[1];
			for(std::vector<int>::iterator it = behaviour_player2.begin(); it != behaviour_player2.end(); ++it){
		    	sum_strategies_player2 += *it;
			}
			//Play
			int behaviour1 = play(strategy_1, behaviour_record[1][i-1], sum_strategies_player2);
			int behaviour2 = play(strategy_2, behaviour_record[0][i-1], sum_strategies_player1);
			//Update behaviour record
			behaviour_record[0].push_back(behaviour1);
			behaviour_record[1].push_back(behaviour2);
			//Update payoff record
			if (behaviour1 == 0 && behaviour2 == 0){
				payoff_records[0].push_back(3);
				payoff_records[1].push_back(3);
			}
			else if (behaviour1 == 0 && behaviour2 == 1){
				payoff_records[0].push_back(0);
				payoff_records[1].push_back(5);
			}
			else if (behaviour1 == 1 && behaviour2 == 0){
				payoff_records[0].push_back(5);
				payoff_records[1].push_back(0);
			}
			else if (behaviour1 == 1 && behaviour2 == 1){
				payoff_records[0].push_back(1);
				payoff_records[1].push_back(1);
			}
			else {
				std::cout << "Invalid behaviour combination" << std::endl;
			}
		} // i loop		

		//Calculate players' scores
		int score_player1 = 0;
		std::vector<int> scores_player1 = payoff_records[0];
		for(std::vector<int>::iterator it = scores_player1.begin(); it != scores_player1.end(); ++it){
		   	score_player1 += *it;
		}
		int score_player2 = 0;
		std::vector<int> scores_player2 = payoff_records[1];
		for(std::vector<int>::iterator it = scores_player2.begin(); it != scores_player2.end(); ++it){
		   	score_player2 += *it;
		}

		//Calculate strategies' scores
		strategies_scores[n] += score_player1;
		strategies_scores[m] += score_player2;

		//Provide output
		std::vector<int> behaviour_record_1 = behaviour_record[0];
		std::cout << "Player 1 played: ";
		for(std::vector<int>::iterator it = behaviour_record_1.begin(); it != behaviour_record_1.end(); ++it){
		   	std::cout << *it << " " ;
		}
		std::cout << std::endl;
		std::vector<int> behaviour_record_2 = behaviour_record[1];
		std::cout << "Player 2 played: ";
		for(std::vector<int>::iterator it = behaviour_record_2.begin(); it != behaviour_record_2.end(); ++it){
		   	std::cout << *it << " " ;
		}
		std::cout << std::endl;
		std::cout << "Player 1 scored " << score_player1 << std::endl;
		std::cout << "Player 2 scored " << score_player2 << std::endl;
		std::cout << "Total payoff both players is " << score_player1 + score_player2 << std::endl;
	} //m loop
} //n loop
std::cout << std::endl;
std::cout << "Always defect scored " << strategies_scores[1] << std::endl;
std::cout << "Always cooperate scored " << strategies_scores[2] << std::endl;
std::cout << "Tit for tat scored " << strategies_scores[3] << std::endl;
std::cout << "Grim scored " << strategies_scores[4] << std::endl;
std::cout << "Random scored " << strategies_scores[5] << std::endl;

return 0;
}