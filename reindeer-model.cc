//Note: the experiment and the original model were developed by Prof. Erling Moxnes, Universitetet i Bergen.
//The results of the original experiment were published in E. Moxnes (2004). Misperceptions of basic dynamics: the case of renewable resource management. System Dynamics Review, Vol. 20, p. 139-162

#include <iostream>
#include <fstream>
#include <iomanip>

//naming convention: all capital for stocks, lower case for variables, rates (flows) and constants

int main(int argc, char ** charv){

//exogenous inputs

//user input
int desired_herd_size;
//constants
float grazing_per_animal = 0.004;
float calving_fraction = 0.85;
float female_fraction = 0.9;
float sex_ratio_calves = 0.5;
float max_sustainable_yield_lichen = 30;
//initial stock values
float start_lichen = 24.4;
int start_heard_size = 1900;
//model setting onstants
float final_time = 15;
float time_step = 1;
//output file name
std::string filename = "outputfile";

//endogenous variables
float LICHEN;
float growth_rate;
float grazing_rate;
int HERD_SIZE;
int slaughtering_rate;
int recruitment_rate;
int slaughtering;
int calves;
int slaughtering_calves;

//model - a model which serves to illustrate that even experienced people are unable to manage scarce renewable resources successfully, even if instant feedback is provided
//example: managing a reindeer herd depending on grazing on lichen (with lichen being the scarce renewable resource)

//providing user instructions
std::cout << "Your task: Maximise the herd size without overgrazing on lichen. You can steer the herd size via slaughtering by defining your desired herd size every year. You have 15 years to manage the herd." << std::endl;
std::cout << "Over the last years, the herd size has increased from 1150 to 1900 animals, and the lichen thickness has decreased from 50 to 24.4mm" << std::endl;

//initialising the model
LICHEN = start_lichen;
HERD_SIZE = start_heard_size;
//initialising the output file (comma separated)
std::ofstream outputfile(filename.c_str());
outputfile << "Time" << "," << "HERD_SIZE" << "," << "LICHEN" << "," << "SLAUGHTERING" << std::endl;
outputfile << 0 << "," << HERD_SIZE << "," << LICHEN << "," << 0 << std::endl;
//starting the iterations
for (float i = 1; i * time_step < final_time; i++){
	//getting user input
	std::cout << "Please provide the desired herd size for this year." << std::endl;
	std::cin >> desired_herd_size; 
	//start the simulation
	grazing_rate = HERD_SIZE * grazing_per_animal;
	calves = HERD_SIZE * calving_fraction * female_fraction;
	recruitment_rate = calves * sex_ratio_calves + 0.1 * calves * sex_ratio_calves;
	if (desired_herd_size <= HERD_SIZE){
		slaughtering_rate = HERD_SIZE + recruitment_rate - desired_herd_size;
	}
	else{
		slaughtering_rate = 0;
	}
	if (LICHEN < HERD_SIZE * grazing_per_animal){
		HERD_SIZE = LICHEN / grazing_per_animal;
	}
	else{
		HERD_SIZE += (recruitment_rate - slaughtering_rate) * time_step;
	}
	slaughtering_calves = 0.9 * calves * sex_ratio_calves;
	slaughtering = slaughtering_rate + slaughtering_calves;
	if (LICHEN < max_sustainable_yield_lichen){
		growth_rate = LICHEN / max_sustainable_yield_lichen * 5;
	}
	else if (LICHEN > max_sustainable_yield_lichen){
		growth_rate = max_sustainable_yield_lichen / LICHEN * 5;
	}
	else {
		growth_rate = 5;
	}
	LICHEN += (growth_rate - grazing_rate) * time_step;
	//writing the output of the iteration to file
	outputfile << i * time_step << "," << HERD_SIZE << "," << LICHEN << "," << slaughtering << std::endl;
	//informing the user of the current system state
	std::cout << "You currently have " << HERD_SIZE << " reindeers, the lichen thickness is " << LICHEN << "mm, and you slaughtered " << slaughtering << " animals." << std::endl;
}

//inform user of the end of the programme
std::cout << "You have reached the end of the programme. The optimal herd size would have been 1250 animals, and the optimal lichen thickness 30mm." << std::endl;

outputfile.close();

return 0;
}