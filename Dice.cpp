#include "Dice.h"

Dice::Dice(string query) {
	// seed the random number generator
	srand(time(nullptr));
	smatch values_mathed; 
	// check if query is valid
	if (!regex_match(query, values_mathed, DICE)) {
		string e = "Query '" + query + "' is invalid\n";
		throw invalid_argument(e);
	}
	// if the addition part is matched, save value
	if (values_mathed[3].matched) {
		const string s = values_mathed[3];
		if (s != "") {
			this->addition = stoi(s);
		}
	}
	// save x and y
	string leading_multiplier_string = values_mathed[1];
	string die_sides_string = values_mathed[2];
	this->leading_multiplier = stoi(leading_multiplier_string);
	this->die_sides = stoi(die_sides_string);

}

int Dice::roll() {
	int rolls = 0;
	// roll the `die_sides` sided dice `leading_multiplier` times
	for (int i = 0; i < leading_multiplier; i++) {
		rolls += (rand() % die_sides + 1);
	}
	// then add the addition value
	return rolls + addition;
}
Dice::Dice() {
	srand(time(nullptr));
}
int Dice::roll(string query) {
	// same as constructor. Used for single dice rolls, not associated with other existing objects.
	smatch values_mathed;
	if (!regex_search(query, values_mathed, DICE)) {
		string e = "Query '" + query + "' is invalid\n";
		throw invalid_argument(e);
	}
	int addition = 0;
	int rolls = 0;
	if (values_mathed[3].matched) {
		const string s = values_mathed[3];
		if (s != "") {
			addition = stoi(s);
		}
	}
	string leading_multiplier_string = values_mathed[1];
	string die_sides_string = values_mathed[2];
	int leading_multiplier = stoi(leading_multiplier_string);
	int die_sides = stoi(die_sides_string);
	for (int i = 0; i < leading_multiplier; i++) {
		rolls += (rand() % die_sides + 1);
	}
	return rolls + addition;
}

int Dice::roll_with_advantage() {
	int r1, r2;
	r1 = roll();
	r2 = roll();
	return max(r1,r2);
}
int Dice::roll_with_disadvantage() {
	int r1, r2;
	r1 = roll();
	r2 = roll();
	return min(r1,r2);
}


int Dice::roll_with_advantage(string query) {
	int r1, r2;
	r1 = Dice::roll(query);
	r2 = Dice::roll(query);
	return max(r1,r2);
}
int Dice::roll_with_disadvantage(string query) {
	int r1, r2;
	r1 = Dice::roll(query);
	r2 = Dice::roll(query);
	return min(r1,r2);
}

void Dice::add_die() {
	add_die(1);
}
void Dice::add_die(int amount) {
	this->leading_multiplier += amount;
}

std::string Dice::get_string()
{
	std::string t_str = "";
	t_str += std::to_string(leading_multiplier);
	t_str += "d";
	t_str += std::to_string(die_sides);
	return t_str;
}

int Dice::get_addition(){return addition;}
int Dice::get_die_sides(){return die_sides;}
int Dice::get_leading_multiplier(){return leading_multiplier;}
