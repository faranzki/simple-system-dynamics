#include <iostream>
#include <fstream>
#include <iomanip>

//naming convention: all capital for stocks, lower case for variables, rates (flows) and constants

int main(int argc, char ** charv){

//exogenous inputs

//constants
float carrying_capacity = 1000;
//initial stock values
float start_population = 20;

//settings

//model setting constants
float final_time = 100;
float time_step = 1;

//output file name
std::string filename = "outputfile";

//endogenous variables

float population_stress;
float fertility_rate;
float mortality_rate;
float birth_rate;
float death_rate;
float POPULATION;


//model - illustrating a simple system showing shifting dominances of reinforcing and balancing feedback and s-shaped growth.
//example: the evolution of a population in an environment with a natural carrying capacity. 

//initialising the model
POPULATION = start_population;
//initialising the output file (comma separated)
std::ofstream outputfile(filename.c_str());
outputfile << "Time" << "," << "Population" << std::endl;
outputfile << 0 << "," << POPULATION << std::endl;
//starting the iterations
for (float i = 1; i * time_step < final_time; i++){
	population_stress = POPULATION / carrying_capacity;
	fertility_rate = (1 - population_stress) * 0.1;
	mortality_rate = population_stress * 0.1;
	birth_rate = POPULATION * fertility_rate;
	death_rate = POPULATION * mortality_rate;
	float net_flow = birth_rate - death_rate;
	POPULATION += net_flow * time_step;	
	//writing the output of the iteration to file
	outputfile << i * time_step << "," << POPULATION << std::endl;
}

outputfile.close();

return 0;
}
