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
		std::cout << "Simulate-1, Try yourself-2\n";
		std::cin >> answer;
		if (answer == 1 || answer == 2) {
			break;
		}
		else {
			std::cout << "Wrong type of input!\n";
		}
	} while (true);
	answer--;//after this answer is either 0 or 1;

	std::system("CLS");//to clear out the console;

	if (!answer) { //if it is not 0, setting the expression to true, we choose simulation;
		simulator();
	}
	else {//if it is not 1, setting the expression to false, we choose tryYourself;
		tryYourself();
	}
	return 1;
}