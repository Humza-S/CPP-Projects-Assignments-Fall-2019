/*
	Name: Humza Salman
	Net ID: MHS180007
*/

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <regex>

#include "Player.h"
#include "HashMap.h"

//enum for the all the league leader categories
enum class LeagueLeaderCategories {
	BATTING_AVERAGE, ON_BASE_PERCENTAGE,
	HITS, WALKS, STRIKEOUTS, HIT_BY_PITCH
};

using namespace std;

// outputting functions prototypes
void outputPlayers(ofstream& out, const unordered_map<string, Player*>& players, const vector<Player*>& sortedPlayers);
void outputLeagueLeaders(ofstream& out, const unordered_map<string, Player*>& players, const vector<Player*>& sortedPlayers);
template <typename T>
void outputTopThree(ofstream& out, const unordered_map<string, Player*>& players, LeagueLeaderCategories category, T type, bool strikeouts, const vector<Player*>& sortedPlayers);
void outputCategory(ofstream& out, LeagueLeaderCategories category);
template <typename T>
int outputPlayerNames(ofstream& out, const unordered_map<string, Player*>& players, const T& value, LeagueLeaderCategories category, const vector<Player*>& sortedPlayers);

// helper functions prototypes
bool sortAlphabetically(Player* a, Player* b);
template <typename T>
void setValueBasedOnCategory(Player* p, T& value, LeagueLeaderCategories category);
template <typename T>
bool checkValueBasedOnCategory(Player* p, const T& value, LeagueLeaderCategories category);
int findMaxStrikeouts(const unordered_map<string, Player*>& players);

int main()
{
	ifstream input;
	input.open("keyfile.txt"); // opens the input file for the key codes
	
	unordered_map<string, string> codes; // used to store the key codes
	if (input) {
		regex categoryPattern(R"((?:\W\W)\s(\w+\s?\w+?\s?\w+?)\s(?:\W\W))"); // regex pattern to match the cattegory, e.g. ## HITS ## would make the category = HITS
		smatch categoryMatch;
		string category; // stores the category
		string line;
		while (getline(input, line)) {
			if (!line.empty() && line[line.size() - 1] == '\r') // used to remove the \r found at the end of each line 
				line.erase(line.size() - 1); 

			if (line.empty()) // ignored empty lines
				continue;

			else if (regex_search(line, categoryMatch, categoryPattern)) { // assigns the category
				category = categoryMatch.str(1); 
			}
			else {
				pair<string, string> code(line, category); // inputs the key code with respective category into the map
				codes.insert(code);
			}
		}
	}
	input.close(); // closes the input file

	unordered_map<string, Player*> players; // map to store player names as keys and player objects as values

	string filename;
	cin >> filename; // retrieves filename for input
	input.open(filename); // opens the input file

	if (input) {
		regex playerPattern(R"((\w) (.+) (.+))"); // regex pattern for player: team, name, and key code
		smatch playerMatch;

		while (!input.eof()) {
			string line;
			getline(input, line); // gets a line from the input file
			
			if (line.empty()) // if the line is empty stops executing
				break;

			Player* p;

			if (regex_search(line, playerMatch, playerPattern)) { // if the line matches the player regex pattern
				string team = playerMatch.str(1); // assigns team
				string name = playerMatch.str(2); // assigns name
				string code = playerMatch.str(3); // assigns code

				if (players[name]) { // if the player already exists, update the batting record
					players[name]->updateStatistics(codes[code]);
				}
				else { // if the player does not exist, create a new player and update the batting record
					p = new Player(name, team);
					p->updateStatistics(codes[code]);
					players[name] = p;
				}
			}
		}
	}

	input.close(); // closes the input file
	
	ofstream out;
	out.open("leaders.txt"); // opens the output file to output data
	
	vector<Player*> sortedPlayers; // stores player objects

	for (auto pair : players)
		sortedPlayers.push_back(pair.second); // puts player objects into the vector

	sort(sortedPlayers.begin(), sortedPlayers.end(), sortAlphabetically); // sorts the vector by name using the sortAlphabetically function

	outputPlayers(out, players, sortedPlayers); // outputs the players
	out << "\n";
	outputLeagueLeaders(out, players, sortedPlayers); // outputs the leageu leaders

	out.close(); // closes the output file
}

void outputPlayers(ofstream& out, const unordered_map<string, Player*> &players, const vector<Player*>& sortedPlayers)
{
	// outputs the AWAY team first
	out << "AWAY\n";
	for (Player* p : sortedPlayers) {
		if (p->getTeam() == "A")
			out << p << endl;
	}

	//outputs the HOME team second
	out << "\nHOME\n";
	for (Player* p : sortedPlayers) {
		if (p->getTeam() == "H")
			out << p << endl;
	}
}

//outputs all top three places in specified categories related to league leaders
void outputLeagueLeaders(ofstream& out, const unordered_map<string, Player*>& players, const vector<Player*>& sortedPlayers) {
	out << "LEAGUE LEADERS\n";
	outputTopThree(out, players, LeagueLeaderCategories::BATTING_AVERAGE, 0.00, false, sortedPlayers); // 0.00 to specify a double
	out << "\n";
	outputTopThree(out, players, LeagueLeaderCategories::ON_BASE_PERCENTAGE, 0.00, false, sortedPlayers);
	out << "\n";
	outputTopThree(out, players, LeagueLeaderCategories::HITS, 0, false, sortedPlayers); // 0 to specify an int
	out << "\n";
	outputTopThree(out, players, LeagueLeaderCategories::WALKS, 0, false, sortedPlayers);
	out << "\n";
	outputTopThree(out, players, LeagueLeaderCategories::STRIKEOUTS, findMaxStrikeouts(players), true, sortedPlayers);
	out << "\n";
	outputTopThree(out, players, LeagueLeaderCategories::HIT_BY_PITCH, 0, false, sortedPlayers);
	out << "\n";
}

//outputs the top three places in each category
template <typename T>
void outputTopThree(ofstream& out, const unordered_map<string, Player*>& players, LeagueLeaderCategories category, T type, bool strikeouts, const vector<Player*>& sortedPlayers)
{
	T first, second, third, value;

	// for calculating strikeouts since they require minimum values
	if (strikeouts) {
		first = second = third = findMaxStrikeouts(players); // sets the type and maximum value for strikeouts

		for (auto pair : players) {
			setValueBasedOnCategory(pair.second, value, category);

			//assigning first, second and third values
			if (value < first) {
				third = second;
				second = first;
				first = value;
			}
			else if ((value < second) && (value != first)) {
				third = second;
				second = value;
			}
			else if ((value < third) && (value != second) && (value != first)) {
				third = value;
			}
		}
	}
	else {
		//specifies the type for first, second, and third values since they can either be int or double
		first = second = third = type; // type is either 0 or 0.00 (int or double)

		for (auto pair : players) {
			setValueBasedOnCategory(pair.second, value, category);

			//assigning first, second and third values
			if (value > first) {
				third = second;
				second = first;
				first = value;
			}
			else if ((value > second) && (value != first)) {
				third = second;
				second = value;
			}
			else if ((value > third) && (value != second) && (value != first)) {
				third = value;
			}
		}
	}

	//outputs the category to the output file
	outputCategory(out, category);

	//keeps track of first and second place ties
	int firstPlaceTies, secondPlaceTies = -1;

	//outputs first place players and updates first place ties
	out << first << "\t";
	firstPlaceTies = outputPlayerNames(out, players, first, category, sortedPlayers);

	//outputs second place players if there are less than 3 players ties for third place and more than 1 player exists
	if (!(firstPlaceTies >= 2) && (players.size() > 1)) {
		out << second << "\t";
		secondPlaceTies = outputPlayerNames(out, players, second, category, sortedPlayers);
	}

	//outputs third place players if there are no ties in first or second place and more than 1 player exists
	if ((firstPlaceTies == 0) && (secondPlaceTies == 0) && (players.size() > 1)) {
		out << third << "\t";
		outputPlayerNames(out, players, third, category, sortedPlayers);
	}
}

//uses the passed in category to output the category to the file
void outputCategory(ofstream& out, LeagueLeaderCategories category) {
	if (category == LeagueLeaderCategories::BATTING_AVERAGE)
		out << "BATTING AVERAGE\n";
	else if (category == LeagueLeaderCategories::ON_BASE_PERCENTAGE)
		out << "ON-BASE PERCENTAGE\n";
	else if (category == LeagueLeaderCategories::HITS)
		out << "HITS\n";
	else if (category == LeagueLeaderCategories::WALKS)
		out << "WALKS\n";
	else if (category == LeagueLeaderCategories::STRIKEOUTS)
		out << "STRIKEOUTS\n";
	else if (category == LeagueLeaderCategories::HIT_BY_PITCH)
		out << "HIT BY PITCH\n";
}

//outputs the player names to the file
template <typename T>
int outputPlayerNames(ofstream& out, const unordered_map<string, Player*> &players, const T& value, LeagueLeaderCategories category, const vector<Player*>& sortedPlayers)
{
	int ties = -1; // ties set to -1 so that when only one player outputted to the file, there are no ties.
	string delim = ""; // delimeter to help with formatting

	// outputs all away players alphabetically who match value and category
	for (Player* p : sortedPlayers) {
		if (p->getTeam() == "A" && checkValueBasedOnCategory(p, value, category)) {
			ties++;
			out << delim << p->getName();
			delim = ", ";
		}
	}
	// outputs all home players alphabetically who match value and category
	for (Player* p : sortedPlayers) {
		if (p->getTeam() == "H" && checkValueBasedOnCategory(p, value, category)) {
			ties++;
			out << delim << p->getName();
			delim = ", ";
		}
	}
	out << "\n";

	return ties; // returns ties to allow to keep track of ties for first and second place
}

// returns the lower value of the two players
bool sortAlphabetically(Player* a, Player* b) {
	return a->nameToLower() < b->nameToLower();
}

//sets value to the current player's value based on the category
template <typename T>
void setValueBasedOnCategory(Player* p, T& value, LeagueLeaderCategories category) {
	if (category == LeagueLeaderCategories::BATTING_AVERAGE)
		value = p->calculateBattingAverage();
	else if (category == LeagueLeaderCategories::ON_BASE_PERCENTAGE)
		value = p->calculateOnBasePercentage();
	else if (category == LeagueLeaderCategories::HITS)
		value = p->getHits();
	else if (category == LeagueLeaderCategories::WALKS)
		value = p->getWalks();
	else if (category == LeagueLeaderCategories::STRIKEOUTS)
		value = p->getStrikeouts();
	else if (category == LeagueLeaderCategories::HIT_BY_PITCH)
		value = p->getHitByPitch();
}

//checks if the value passed in is equal to the value of the player passed in based on the category
template <typename T>
bool checkValueBasedOnCategory(Player* p, const T& value, LeagueLeaderCategories category) {
	if (category == LeagueLeaderCategories::BATTING_AVERAGE)
		return (p->calculateBattingAverage() == value) ? true : false;
	else if (category == LeagueLeaderCategories::ON_BASE_PERCENTAGE)
		return (p->calculateOnBasePercentage() == value) ? true : false;
	else if (category == LeagueLeaderCategories::HITS)
		return (p->getHits() == value) ? true : false;
	else if (category == LeagueLeaderCategories::WALKS)
		return (p->getWalks() == value) ? true : false;
	else if (category == LeagueLeaderCategories::STRIKEOUTS)
		return (p->getStrikeouts() == value) ? true : false;
	else if (category == LeagueLeaderCategories::HIT_BY_PITCH) {
		return (p->getHitByPitch() == value) ? true : false;
	}
	return false;
}


//finds and returns the player with the most strikeouts
int findMaxStrikeouts(const unordered_map<string, Player*> &players) {
	int max = 0;
	for (auto pair : players) {
		(max < pair.second->getStrikeouts()) ? max = pair.second->getStrikeouts() : max = max; // assigns the max for player strikeouts
	}
	return max;
}