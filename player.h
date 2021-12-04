#pragma once
#include "weapon.h"
//#include "scoreboard.h"
#include <list>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

class player
{
	private:

		string name;
		//This should hold the player’s name
		int MaxHealth;
		//This should hold the maximum health of the player
		int HealthPoints;
		//This should hold the current health of the player
		int AttackDamageMod;
		//This should hold the attack damage of the player
		int currency;

		int genRandNum(int a, int b);

		list<weapon> weaponList;
		

		//new:
		int score;

		int diffMod;

		int floor;


		// Password is now being used to name save files. (instead of the player name)
		string password;






	public:
		//default constructor
		player();
		player(string playerName, int myDiff);
		
		string getName();
		int getMaxHP();
		//returns the maximum health
		int getHP();
		//returns the current health
		int getDMG();
		//returns the current damage
		int getCurr();

		int getScore();

		int getDiffMod();

		int getFloor();

		string getPassword();

		void printWeaponList();

		string getWeaponIndexName(int index);
		
		//returns the player's currency
		void setCurr(int c);
		
		void setName(string n);


		void setMaxHP(int h);

		void setScore(int s);

		void setPassword(string password);

		void setDiffMod(int d);

		void setFloor(int f);


		// adds new upgraded weapons to shop available to use. Called per level increase and game start
		void upgradeWeaponList();

		

		list<weapon> getWeaponList();

		//action Attack: returns damage done (or -1 if invalid) requires weaponList index (ex. 1: fists, 2: iron) returns damage done + manages weapon loss 
		int actAttack(int);

		int buyWeapon(int i);

		//sets the current health
		void setHP(int h);

		//sets the current damage	
		void setDMG(int d);

		//Increments or decrements the player’s health by the input value
		void ModifyHealth(int h);

		//Increments or decrements the player’s attack damage by the input value
		void ModifyDamage(int h);

		//Increments or decrements the player’s currency by the input value
		void ModifyCurrency(int c);

		
		//Increments or decrements the player’s current floor by the input value
		void ModifyFloor(int f);


		//Increments or decrements the player’s current score by the input value
		void ModifyScore(int s);

		//same as modScore
		void addScore(int s);


		//Print player vals
		void print();






		//Sends String data to an output stream (ex: cout << p1; or fileOut << p1; )
		friend ostream & operator <<(ostream& os, player& p);



		//Sends String data to an output stream (ex: cout << p1; or fileOut << p1; )
		friend istream& operator >>(istream& os, player& p);



		string getDiffName();

};