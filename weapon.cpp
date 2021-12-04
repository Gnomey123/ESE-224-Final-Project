#include <iostream>
#include <string>
#include <iomanip>
#include "weapon.h"
using namespace std;


//default weapon
weapon::weapon()
{
    name = "";
    dmg = 5;
    amount = 0;
}

weapon::~weapon()
{
    
}





//weapon parameter
weapon::weapon(string str, int Dmg, int Cost, int Amount)
{
    name = str;
    dmg = Dmg;
    cost = Cost;
    amount = Amount;
}


void weapon::incAmount()
{
    if (name == "Fist")
    {
        return;
    }
    amount++;
}

void weapon::decAmount()
{
    if (name == "Fist")
    {
        return;
    }
    amount--;
}


//setting weapon name
void weapon::setItem(string str)
{
    name = str;
}

int weapon::getAmountOwned()
{
    return amount;
}

//adding dmg
void weapon::setDMG(int d)
{
    dmg = d;
}

 // adds cost
void weapon::setCost(int c)
{
    cost = c;
}





//getting a weapons name
string weapon::getName()
{
    return name;
}


//getting a weapons dmg
int weapon::getDMG()
{
    return dmg;
}


 // get cost of weapon
int weapon::getCost()
{
    return cost;
}


ostream& operator<<(ostream& os, weapon& w)
{
    os << w.name << " " << w.dmg << " " << w.cost << " " << w.amount;
    return os;
}



istream& operator>>(istream& is, weapon& w)
{
    is >> w.name >> w.dmg >> w.cost  >> w.amount;
    return is;
}

/*
        string W_item;
       
        int W_damage;

        int cost;

        */