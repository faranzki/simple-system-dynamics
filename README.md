# simple-system-dynamics
A collection of simple system dynamics models to illustrate basic system behaviours at easy examples

Aim: 
This repository is aimed at people interested in system dynamics modelling. Its aim is i) to provide simple illustrative models for analysing basic system behaviour types, and ii) to provide an entry point to free system dynamics from its dependence on paid software, by showing simple examples of how models can be written in basic programming languages (for the it is C++). 

Use of the models:
Each model comes with a makefile (compile with 'make'). The name of the executable can be consulted in the corresponding makefile. Each model writes its output to file (comma separated). For visualisation, use whichever tool or language you are familiar with (R, python, MS Excel...). The name of the output files is outputfile. 
Note that each model and makefile need to be saved to an individual folder! The output file is generated in the same folder as the model and the makefile. 
For the time being, all model constants and model settings are preset in the code, but can easily be adjusted based upon the needs of the user directly in the code. 
For each model, an exemplary output graph as well as a system visualisation as a stock flow diagram is provided for illustration and information. 
