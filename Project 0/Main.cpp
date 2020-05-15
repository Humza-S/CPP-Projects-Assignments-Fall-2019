/*
   Name: Humza Salman
   NET ID: MHS180007
*/

#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

//global variables
int const MAX_INDEX = 30;

//prototypes
void parseBattingRecord(string, int[], int[], int[], int[], int&, int&, int);
void displayPlayerData(ofstream&, string[], double[], double[], int[], int[], int[], int[], int);
double findBestValue(double[], int);
int findBestValue(int[], int, bool);
void displayLeader(ofstream&, string[], string, double[], double, int);
void displayLeader(ofstream&, string[], string, int[], int, int);

int main(){
   string filename;
   ifstream inputFile;
   ofstream outputFile;

   //arrays to store player statistics in parallel.
   string playerNames[MAX_INDEX] = {};
   double playerBattingAverages[MAX_INDEX] = {};
   double playerOnBase[MAX_INDEX] = {};
   int playerHits[MAX_INDEX] = {};
   int playerWalks[MAX_INDEX] = {};
   int playerStrikeouts[MAX_INDEX] = {};
   int playerHitsByPitch[MAX_INDEX] = {};

   //reads in file name and opens
   cin >> filename;
   inputFile.open(filename.c_str());

   //keep track of index to help with element count
   int index = 0;

   //checks to validate if file opens, if true, then runs the program
   if(inputFile){
      //reads to end of file.
      while (!inputFile.eof()){
         //reads in and stores line
         string line;
         getline(inputFile, line);

         //checks for empty lines at end of file
         if(line.empty())
            break;

         //parsing the line <Name><Space><Batting Record>
         int gapIndex = line.find(' ', 0);
         playerNames[index] = line.substr(0, gapIndex); //stores player name to corresponding index
         string battingRecord = line.substr(gapIndex);

         //variables to store outs and sacrifices
         int countO, countS;
         countO = countS = 0;

         //pass in batting record, arrays, and index to increment corresponding values
         parseBattingRecord(battingRecord, playerHits,playerWalks, playerStrikeouts,
                            playerHitsByPitch, countO, countS, index);

         //calculate at bats, plate appearances, batting average, and on-base percentage.
         double atBats = static_cast<double>(playerHits[index]) + countO + playerStrikeouts[index];
         double plateAppearances = atBats + playerWalks[index] + playerHitsByPitch[index] + countS;
         playerBattingAverages[index] = atBats <= 0 ? 0: playerHits[index] / atBats;
         playerOnBase[index] = plateAppearances <= 0 ? 0: (playerHits[index] + playerWalks[index] + playerHitsByPitch[index]) / plateAppearances;

         //rounds batting average and on-base percentage to 3 decimal places
         playerBattingAverages[index] = round(playerBattingAverages[index]*1000)/1000;
         playerOnBase[index] = round(playerOnBase[index]*1000)/1000;

         index++;
      }
   }
   inputFile.close();

   //opens output file (creates if one does not exist)
   outputFile.open("leaders.txt");

   //outputs player data(name and statistics)
   displayPlayerData(outputFile, playerNames, playerBattingAverages, playerOnBase, playerHits,
                     playerWalks, playerStrikeouts, playerHitsByPitch, index);

   //following lines of code displays League Leaders
   outputFile << "LEAGUE LEADERS" << endl;

   //each of the following functions outputs the leader(s) for their respective statistic

   //Batting Averages Leader(s)
   displayLeader(outputFile, playerNames, "BA: ", playerBattingAverages, findBestValue(playerBattingAverages, index), index);

   //On-Base Percentages Leader(s)
   displayLeader(outputFile, playerNames, "OB%: ", playerOnBase, findBestValue(playerOnBase, index), index);

   //Hits Leader(s)
   displayLeader(outputFile, playerNames, "H: ", playerHits, findBestValue(playerHits, index, false), index);

   //Walks Leader(s)
   displayLeader(outputFile, playerNames, "BB: ", playerWalks, findBestValue(playerWalks, index, false), index);

   //Strikeout Leader(s)
   displayLeader(outputFile, playerNames, "K: ", playerStrikeouts, findBestValue(playerStrikeouts, index, true), index);

   //Hit By Pitch Leader(s)
   displayLeader(outputFile, playerNames, "HBP: ", playerHitsByPitch, findBestValue(playerHitsByPitch, index, false), index);

   outputFile.close();

   return 0;
}

void parseBattingRecord(string battingRecord, int hits[], int walks[], int strikeouts[],
                         int hitsByPitch[], int& countO, int& countS, int index){
   /*
    H – hit
    O – out
    K – strikeout
    W – walk
    P – hit by pitch
    S – sacrifice
   */

   //iterates through batting record letter by letter to increment valid values
   for(char c: battingRecord){
      if(c == 'H')
         hits[index]++;
      else if(c == 'O')
         countO++;
      else if(c == 'K')
         strikeouts[index]++;
      else if(c == 'W')
         walks[index]++;
      else if(c == 'P')
         hitsByPitch[index]++;
      else if(c == 'S')
         countS++;
   }
}

void displayPlayerData(ofstream& output, string names[], double BA[], double OB[], int H[],
                       int BB[], int K[], int HBP[], int elements){

   //goes through and print each player and their respective statistics.
   output << setprecision(3) << fixed;
   for(int i = 0; i < elements; i++){
      output << names[i] << endl;
      output << "BA: " << BA[i] << endl;
      output << "OB%: " << OB[i] << endl;
      output << "H: " << H[i] << endl;
      output << "BB: " << BB[i] << endl;
      output << "K: " << K[i] << endl;
      output << "HBP: " << HBP[i] << endl << endl;
   }
}

double findBestValue(double arr[], int elements){

   //initial max value
   double maxValue = arr[0];

   //finds the max value in the array passed in and returns it
   for(int i = 1; i < elements; i++){
      double currentValue = arr[i];
      if(currentValue > maxValue)
         maxValue = currentValue;
   }
   return maxValue;
}

int findBestValue(int arr[], int elements, bool strikeouts){
   //initial max and min values
   int maxValue, minValue;
   maxValue = minValue = arr[0];

   //checks to see if calculating for strikeouts
   if(strikeouts){
      //finds the lowest value in the array and returns it
      for(int i = 1; i < elements; i++){
         int currentValue = arr[i];
         if(currentValue < minValue)
            minValue = currentValue;
      }
      return minValue;
   }
   //finds the max value in the array and returns it
   for(int i = 0; i < elements; i++){
      int currentValue = arr[i];
      if(currentValue > maxValue)
         maxValue = currentValue;
   }
   return maxValue;
}

//displays the leader of the statistic(type double)
void displayLeader(ofstream& output, string names[], string statistic, double arr[],
                        double value, int elements){
   output << statistic;
   string delimiter = "";//helps to format the ", "(comma space) between multiple leaders
   for(int i = 0; i < elements; i++){
      if(value == arr[i]){
         output << delimiter << names[i];
         delimiter = ", ";
      }
   }
   output << " " << value << endl;
}

//displays the leader of the statistic(type int)
void displayLeader(ofstream& output, string names[], string statistic, int arr[],
                        int value, int elements){
   output << statistic;
   string delimiter = "";//helps to format the ", "(comma space) between multiple leaders
   for(int i = 0; i < elements; i++){
      if(value == arr[i]){
         output << delimiter << names[i];
         delimiter = ", ";
      }
   }
   output << " " << value << endl;
}
