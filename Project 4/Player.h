/*
	Name: Humza Salman
	NET ID: MHS180007
*/

#ifndef Player_H
#define Player_H

#include <math.h>
#include <string>
#include <fstream>
#include <iostream>

class Player
{
private:
	std::string name, team;
	int hits, outs, walks, strikeouts, hitByPitch, sacrifices, errors;
public:
	//constructors
	Player() {
		name = team = "";
		hits = outs = walks = strikeouts = hitByPitch = sacrifices = errors = 0;
	};
	Player(std::string n) {
		name = n;
		team = "";
		hits = outs = walks = strikeouts = hitByPitch = sacrifices = errors = 0;
	};
	Player(std::string n, std::string t) {
		name = n;
		team = t;
		hits = outs = walks = strikeouts = hitByPitch = sacrifices = errors = 0;
	};

	//destructor
	~Player() {};

	//helper functions
	void updateStatistics(std::string line);
	std::string nameToLower();

	//overloaded constructors
	bool operator==(Player& p);
	bool operator>(Player& p);
	bool operator<(Player& p);
	friend std::ostream& operator<<(std::ostream& out, Player* const player);
	friend std::ofstream& operator<<(std::ofstream& out, Player* const player);

	//functions to calculate statistics
	int calculateAtBats() { // calculates the mistakes
		return hits + outs + strikeouts;
	};
	int calculatePlateAppearences() { // calculates the plate appearences
		return calculateAtBats() + walks + hitByPitch + sacrifices + errors;
	};
	double calculateBattingAverage() { // calculates the BA
		double atBats = calculateAtBats();
		double battingAverage = atBats <= 0 ? 0 : hits / atBats;
		return battingAverage;
	};
	double calculateOnBasePercentage() { // calculates the OB%
		double plateAppearances = calculatePlateAppearences();
		double onBasePercentage = plateAppearances <= 0 ? 0 : ((double)hits + (double)walks + (double)hitByPitch) / plateAppearances;
		return onBasePercentage;
	};

	//accessors
	std::string getName() { return name; };
	std::string getTeam() { return team; };
	int getHits() { return hits; };
	int getOuts() { return outs; };
	int getWalks() { return walks; };
	int getStrikeouts() { return strikeouts; };
	int getHitByPitch() { return hitByPitch; };
	int getSacrifices() { return sacrifices; };

	//mutators
	void setName(std::string n) { name = n; };
	void setTeam(std::string t) { team = t; };
	void setHits(int h) { hits = h; };
	void setOuts(int o) { outs = o; };
	void setWalks(int w) { walks = w; };
	void setStrikeouts(int s) { strikeouts = s; };
	void setHitByPitch(int p) { hitByPitch = p; };
	void setSacrifices(int s) { sacrifices = s; };
};
#endif // !Player_H