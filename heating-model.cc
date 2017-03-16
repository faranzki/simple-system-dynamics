#include <iostream>
#include <fstream>
#include <iomanip>

//naming convention: all capital for stocks, lower case for variables, rates (flows) and constants

int main(int argc, char ** charv){

//exogenous inputs

//constants
float combustion_time = 5;
float desired_temperature = 20;
float heat_diffustion_time = 1;
float cooling_time = 7;
float outside_temperature = 0;
//initial stock values
float start_temperature = 0;
float start_wood_in_oven = 0;
//model setting constants
float final_time = 100;
float time_step = 0.5;
//output file name
std::string filename = "outputfile";

//endogenous variables

float firing_rate;
float WOOD_IN_OVEN;
float combustion_rate;
float heating_rate;
float TEMPERATURE;
float cooling_rate;

//model - illustrating a simple system generating oscillations and a steady state error.
//example: heating a cabin with a wood stove

//initialising the model
TEMPERATURE = start_temperature;
WOOD_IN_OVEN = start_wood_in_oven;
//initialising the output file (comma separated)
std::ofstream outputfile(filename.c_str());
outputfile << "Time" << "," << "Temperature" << "," << "Desired temperature" << std::endl;
outputfile << 0 << "," << TEMPERATURE << "," << desired_temperature << std::endl;
//starting the iterations
for (float i = 1; i * time_step < final_time; i++){
	firing_rate = desired_temperature - TEMPERATURE;
	combustion_rate = WOOD_IN_OVEN / combustion_time;
	WOOD_IN_OVEN += (firing_rate - combustion_rate) * time_step;
	heating_rate = combustion_rate / heat_diffustion_time;
	cooling_rate = (TEMPERATURE - outside_temperature) / cooling_time;
	TEMPERATURE += (heating_rate - cooling_rate) * time_step;
	//writing the output of the iteration to file
	outputfile << i * time_step << "," << TEMPERATURE << ";" << desired_temperature << std::endl;
}

outputfile.close();

return 0;
}