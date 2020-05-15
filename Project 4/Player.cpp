/*
	Name: Humza Salman
	NET ID: MHS180007
*/

#include "Player.h"
#include <iostream>
#include <iomanip>

// takes the statistics and updates it
void Player::updateStatistics(std::string stat) {
	/*
	 H – hit
	 O – out
	 K – strikeout
	 W – walk
	 P – hit by pitch
	 S – sacrifice
	*/
	if (stat == "HITS")
		hits++;
	else if (stat == "OUTS")
		outs++;
	else if (stat == "STRIKEOUT")
		strikeouts++;
	else if (stat == "WALK")
		walks++;
	else if (stat == "SACRIFICE")
		sacrifices++;
	else if (stat == "HIT BY PITCH")
		hitByPitch++;
	else if (stat == "ERRORS")
		errors++;
}

//makes a copy of the name of the player and transforms it into a lowercase copy and returns it
std::string Player::nameToLower()
{
	std::string lowercaseName = name;
	for (int i = 0; i < (int)lowercaseName.length(); i++) {
		if (lowercaseName[i] >= 'A' && lowercaseName[i] <= 'Z')
			lowercaseName[i] = lowercaseName[i] + 32;
	}
	return lowercaseName;
}

//overloads the == operator so that two players are equal if their names are the same
bool Player::operator==(Player& p)
{
	return name == p.getName();
}

//overloads the > operator so that players are compared through their lowercase (case insensitive) names
bool Player::operator>(Player& p) {
	return nameToLower() > p.nameToLower();
}

//overloads the < operator so that players are compared through their lowercase (case insensitive) names
bool Player::operator<(Player& p) {
	return nameToLower() < p.nameToLower();
}

//overloads the << operator so that the console output for player prints statistics
std::ostream& operator<<(std::ostream& out, Player* const player)
{
	out << std::setprecision(3) << std::fixed;
	out << player->getName() << "\t";
	out << player->calculateAtBats() << "\t";
	out << player->getHits() << "\t";
	out << player->getWalks() << "\t";
	out << player->getStrikeouts() << "\t";
	out << player->getHitByPitch() << "\t";
	out << player->getSacrifices() << "\t";
	out << player->calculateBattingAverage() << "\t";
	out << player->calculateOnBasePercentage();
	return out;
}

//overloads the << operator so that the file output for player outputs statistics
std::ofstream& operator<<(std::ofstream& out, Player* const player)
{
	out << std::setprecision(3) << std::fixed;
	out << player->getName() << "\t";
	out << player->calculateAtBats() << "\t";
	out << player->getHits() << "\t";
	out << player->getWalks() << "\t";
	out << player->getStrikeouts() << "\t";
	out << player->getHitByPitch() << "\t";
	out << player->getSacrifices() << "\t";
	out << player->calculateBattingAverage() << "\t";
	out << player->calculateOnBasePercentage();
	return out;
}