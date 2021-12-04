#pragma once
#include <iostream>
#include <string>
using namespace std;

class scoreNode
{
	private:

		//Name of the player
		string name;
		
		//(*Note: Higher level enemies should give more points.)
		//score of the player. Score should increase after the player defeats an enemy or through some custom method designed by you.
		int score;
	
		

	public:
		//default constructor
		scoreNode();
		scoreNode(string myName, int myScore);

		~scoreNode();
		
		void setName(string n);
		void setScore(int s);
		
		string getName();
		int getScore();
		

		//outputs score to the player 
		void print(); 

		bool operator <(const scoreNode& nodeToComp);


		//string getScoreLine();
		friend ostream& operator <<(ostream& os, scoreNode& s);

		friend istream& operator >>(istream& is, scoreNode& s);
		//outputs score data to the file



};