#pragma once
#include <iostream>
#include <string>

using namespace std;

class weapon
{
	private:

		//Name of the weapon item
		string name;
		
		//Attack damage to the item. This can be added or removed by the player
		int dmg;

		// Cost of new weapon
		int cost;
		
		int amount;

	public:
		weapon();
		weapon(string str, int, int, int amount);
		~weapon();


		void setItem(string i);
		void setDMG(int d);
		void setCost(int c);
	
	
		string getName();
		int getDMG();
		int getCost();

		void incAmount();

		void decAmount();

		int getAmountOwned();

		friend ostream& operator<<(ostream& os, weapon&);

		friend istream& operator>>(istream& is, weapon&);
};