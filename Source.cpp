#include<iostream>
#include<vector>
#include<random>
#include<chrono>
#include<stdlib.h>
#include"Functions.h"

int main() {

	std::cout << "Hello! Welcome to my 3 chests game!\n";//greeting message;

	int answer;

	do {
		do {
			std::cout << "Simulate-1, Try yourself-2, Exit-3\n";
			std::cin >> answer;
			if (answer == 1 || answer == 2 || answer == 3) {
				break;
			}
			else {
				std::cout << "Wrong type of input!\n";
			}
		} while (true);

		std::system("CLS");//to clear out the console;

		if (answer == 1) { //if it is not 0, setting the expression to true, we choose simulation;
			simulator();
		}
		else if (answer == 2) {//if it is not 1, setting the expression to false, we choose tryYourself;
			tryYourself();
		}
	} while (answer != 3);
	
	return 1;
}