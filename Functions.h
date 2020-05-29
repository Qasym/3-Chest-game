#pragma once

struct Chest {

	Chest() {//a simple constructor;
		treasure = false;
		picked = false;
	}

	void putTreasure() { //putting treasure into the chest;
		treasure = true;
	}

	void pick() { //true if we pick this chest;
		picked = true;
	}

	bool treasureHere() { //returns true if treasure is here;
		return treasure;
	}

	bool isPicked() {//true if chest is picked;
		return picked;
	}

	bool check() {
		//checks whether booleans are equal;
		//if it's true, we either know that chest is picked and contains treasure
		//or we know that chest is not picked and there is no treasure;
		return treasure == picked;
	}

	friend void swapPicks(Chest& ch1, Chest& ch2);//declaring a friend function to give access to private variables;

private:
	bool treasure;//keeps track of existense of the treasure inside the chest;
	bool picked;//keeps track of picking by user;
};

void swapPicks(Chest& ch1, Chest& ch2) { //a function to change the pick from one chest to another;
	bool temp = ch1.picked;				 //made specifically for the case of 3 chests and changing picks;
	ch1.picked = ch2.picked;
	ch2.picked = temp;
}

void swappingChests(int& hits, int simulations) {
	std::vector<Chest> vec;//our vector to store chests;

	auto seed = std::chrono::steady_clock::now().time_since_epoch().count();//seed is the current time;
	std::default_random_engine gen(seed);
	std::uniform_int_distribution<int> distr(0, 2); //random number generator, range [0, 2];

	for (unsigned int i = 0; i < simulations; i++) {

		vec.push_back(Chest());
		vec.push_back(Chest());
		vec.push_back(Chest());//putting chests into the vector;

		vec[distr(gen)].putTreasure(); //we put treasure inside of a chest;

		vec[distr(gen)].pick(); //we pick a chest;

		for (unsigned j = 0; j < 3; j++) {
			//running through all of the chests, to delete the one which
			//is not picked nor contains treasure;
			if (!vec[j].treasureHere() && !vec[j].isPicked()) { //if treasure not here and is not picked;
				vec.erase(vec.begin() + j);//deleting the chest;
				break;//exit the loop;
			}
		}
		//since we know that only 2 chests left, we can simply swap their pick values;
		swapPicks(vec[0], vec[1]);

		if (vec[0].check()) { 
			//if one of the chests has equal values of treasure and picked,
			//then it definitely means that second one also has same values for them;
			hits++;
			//it means that we picked the chest with treasure;
		}

		vec.clear();//clear the chest;
	}
}

void notSwappingChests(int& hits, int simulations) { //this function is the same swappingChests function, but with no swap;

	//Please look at the comments of swappingChests() function;
	std::vector<Chest> vec;

	auto seed = std::chrono::steady_clock::now().time_since_epoch().count();
	std::default_random_engine gen(seed);
	std::uniform_int_distribution<int> distr(0, 2); //random number generator;

	for (unsigned int i = 0; i < simulations; i++) {

		vec.push_back(Chest());
		vec.push_back(Chest());
		vec.push_back(Chest());//putting chests into one vector;

		vec[distr(gen)].putTreasure(); //we put treasure inside of a chest;

		vec[distr(gen)].pick(); //we pick a chest;

		for (unsigned j = 0; j < 3; j++) {
			if (!vec[j].treasureHere() && !vec[j].isPicked()) {
				vec.erase(vec.begin() + j);
				break;
			}
		}

		if (vec[0].check()) {
			hits++;
		}

		vec.clear();//clear the chest;
	}
}

void tryYourself() {
	//We let user to make a choice;
	int user_pick;
	do {
		std::cout << "Which chest do you want to choose? 1, 2 or 3?\n";
		std::cin >> user_pick;
		if (user_pick == 1 || user_pick == 2 || user_pick == 3) {
			break;
		}
		else {
			std::cout << "Wrong type of input!\n";
		}
	} while (true);
	user_pick--; //since we use 0-indexed system;

	std::vector<Chest> vec;
	vec.push_back(Chest());
	vec.push_back(Chest());
	vec.push_back(Chest());//putting chests into the vector;

	auto seed = std::chrono::steady_clock::now().time_since_epoch().count();//current time is the seed;
	std::default_random_engine gen(seed);//generator takes the seed;
	std::uniform_int_distribution<int> distr(0, 2); //random number generator, range [0, 2];

	vec[distr(gen)].putTreasure(); //we put treasure into one of the chests;

	for (int i = 0; i < 3; i++) {
		if (!vec[i].treasureHere() && i != user_pick) {//treasure is not here and user did not pick;
			vec.erase(vec.begin() + i);//erasing the chest matching the conditions;
			break;
		}
	}

	std::cout << "One of the empty chests was removed.\n";
	
	//asking user to change pick or not;
	int answer;
	do {
		std::cout << "Do you want to change your pick? Yes-1, No-2\n";
		std::cin >> answer;
		if (answer == 1 || answer == 2) {
			break;
		}
		else {
			std::cout << "Wrong type of input!\n";
		}
	} while (true);
	answer--;
	//Yes is 0, which is boolean false;
	//No is 1, which is boolean true;

	if (!answer) { //if not false;
		swapPicks(vec[0], vec[1]);
		std::cout << "Choice changed!\n";
	}

	if (vec[0].check()) {//check out the comments on Chest::check();
		std::cout << "Congratulations! Treasure is yours!\n";
	}
	else {
		std::cout << "Unfortunately, you lost.\n";
	}

	std::cout << "Do you want to play again?\n";
	do {
		std::cout << "Yes-1, No-2\n";
		std::cin >> user_pick;
		if (user_pick == 1 || user_pick == 2) {
			break;
		}
		else {
			std::cout << "Wrong type of input!\n";
		}
	} while (true);
	user_pick--;//since it is simple to use booleans;

	if (!user_pick) {
		tryYourself();
	}

}
void simulator() {
	int simulations;
	int hits1 = 0;
	int hits2 = 0;

	std::cout << "Please, enter the number of simulations: ";
	std::cin >> simulations;

	swappingChests(hits1, simulations);
	notSwappingChests(hits2, simulations);

	std::cout << "For a given number of simulations, you win in " << hits1 << " cases, if you change your choice.\n";
	std::cout << "For a given number of simulations, you win in " << hits2 << " cases, if you do not change your choice.\n";
}