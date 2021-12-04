#include <iostream>
#include <iomanip>
#include <list>
#include <time.h>
#include <stdlib.h>
#include <string>
#include "player.h"
//#include "scoreboard.h"
#include "weapon.h"
using namespace std;


void player::upgradeWeaponList()
{
    switch (weaponList.size())
    {
    case 0:
        weaponList.push_back(weapon("Wooden", 5, 1, 0));
        break;
    case 1:
        weaponList.push_back(weapon("Stone", 10, 2, 0));
        break;
    case 2:
        weaponList.push_back(weapon("Iron", 20, 3, 0));
        break;
    case 3:
        weaponList.push_back(weapon("Gold", 30, 4, 0));
    case 4:
        weaponList.push_back(weapon("Diamond", 50, 5, 0));
        break;

    default:
        cout << "[ERROR]: upgradeWeaponList weapon list.size() switch beyond excepted cases" << endl;
        break;

    }


}


player::player()
{
    diffMod = 0;

    //fillWeaponList();

    name = "";

    MaxHealth = 25;
    HealthPoints = 25;
    AttackDamageMod = 0;
    floor = 1;
    score = 0;
    diffMod = 0;
    currency = 0;
}

player::player(string playerName, int myDiff)
{
    diffMod = myDiff;

    //fillWeaponList();

    name = playerName;
    MaxHealth = 25;
    HealthPoints = 25;
    AttackDamageMod = 0;
    currency = 0;
    floor = 1;
    score = 0;
    diffMod = 0;


}


int player::genRandNum(int a, int b)
{
   // srand(time(0));
    return (rand() % (b - a + 1) + a);
}



//action Attack: returns damage done (or -1 if invalid). requires weaponList index (ex. 0: fists, 1: iron) returns damage done + manages weapon loss 

/*

int player::actAttack(int weaponIndex)
{
    int tempDMG = 0;
    if ((weaponIndex < 0) || (weaponList.size() - 1 < weaponIndex)) //is it a valid index?
    {
        return -1;
    }

    if ((weaponList[weaponIndex].getAmountOwned() <= 0) && (weaponIndex != 0))  // user doesn't have any of that weapon left
    {
        return 0;
    }

    
   

    if (genRandNum(1,3)  == 3)
    {

        tempDMG = genRandNum(1, 3);
        cout << "The way you jolt towards your enemy strengthens your blow\n+" << tempDMG << " damage added to attack" << endl;
    }
    else if (genRandNum(1, 4) == 1)
    {
        tempDMG = genRandNum(1, 3);
        AttackDamageMod += tempDMG;
        cout << "As you attack, you get better at damaging your opponents\n+" << tempDMG << " permanent damage added to player" << endl;
    }

    if (weaponIndex == 0)    //using Fists
    {
        return (AttackDamageMod + weaponList[0].getDMG() + tempDMG);
    }

    

 
    weaponList[weaponIndex].decAmount();

    return (AttackDamageMod + weaponList[weaponIndex].getDMG() + tempDMG);



}

*/




void player::printWeaponList()
{
    int x = 0;
    const int nameWidth = 20;
    const char separator = ' ';
    cout << "     ";
    cout << left << setw(nameWidth) << setfill(separator) << "Weapon Type:";
    cout << left << setw(nameWidth) << setfill(separator) << "Damage:";
    cout << left << setw(nameWidth) << setfill(separator) << "Cost:";
    cout << left << setw(nameWidth) << setfill(separator) << "Currently Owned:" << endl;


    for (weapon wep : weaponList)
    {
        cout << "(" << x++ << ")  ";
        cout << left << setw(nameWidth) << setfill(separator) <<  wep.getName() ;
        cout << left << setw(nameWidth) << setfill(separator) << to_string(wep.getDMG()) ;
        cout << left << setw(nameWidth) << setfill(separator) <<  "$"  + to_string(wep.getCost()) ;
        cout << left << setw(nameWidth) << setfill(separator) << to_string(wep.getAmountOwned());
        cout << endl;
    }
}





string player::getName() {
    return name;
}

int player::getMaxHP() {
    return MaxHealth;
}
//returns the maximum health
int player::getHP() {
    return HealthPoints;
}
//returns the current health

int player::getDMG() {
    return AttackDamageMod;
}
//returns the current damage

int player::getCurr() {
    return currency;
}

int player::getScore()
{
    return score;
}

string player::getPassword()
{
    return password;
}

int player::getDiffMod()
{
    return diffMod;
}

int player::getFloor()
{
    return floor;
}


//sets the name
void player::setPassword(string password) {
    this->password = password;
}


//sets the name
void player::setName(string n) {
    name = n;
}

string player::getWeaponIndexName(int index)
{
    if ((index < 0) || (index > weaponList.size()))
    {
        return "";
    }

    auto wpListPtr = weaponList.begin();

    //advance iterator to proper index
    advance(wpListPtr, index);
   

    return (*wpListPtr).getName();
    
}

int player::buyWeapon(int i)
{
   
    //Check invalid entry
    if ((i < 0) || (i > weaponList.size()) )
    {
        return -1;
    }

    auto wpListPtr = weaponList.begin();

    //advance iterator to proper index
    advance(wpListPtr, i);


    //Check if player can afford weapon
    if ((*wpListPtr).getCost() <= currency)
    {
        currency -= (*wpListPtr).getCost();
        (*wpListPtr).incAmount();
        return 1;
    }

    //Assume Player cant afford weapon
    return 0;
}

void player::setMaxHP(int h) {
    MaxHealth = h;
}

void player::setCurr(int c)
{
    currency = c;
}

void player::setHP(int h) {
    HealthPoints = h;
}
//sets the current health

void player::setDMG(int d) {
    AttackDamageMod = d;
}
//sets the current damage


void player::setScore(int s)
{
    score = s;
}

void player::setDiffMod(int d)
{
    diffMod = d;
}

void player::setFloor(int f)
{
    floor = f;
}


//Increments or decrements the player’s health by the input value
void player::ModifyHealth(int h) {
    HealthPoints += h;
}


//Increments or decrements the player’s attack damage by the input value
void player::ModifyDamage(int h) {
    AttackDamageMod += h;
}

void player::ModifyCurrency(int c) {
    currency += c;
}


//Increments or decrements the player’s current floor by the input value
void player::ModifyFloor(int f)
{
    floor += f;
}


//Increments or decrements the player’s current score by the input value
void player::ModifyScore(int s)
{
    score += s;
}

void player::addScore(int s)
{
    score += s;
}


list<weapon> player::getWeaponList()
{
    return weaponList;
}

string player::getDiffName() {
    switch (diffMod)
    {
    case 1:
        return "Easy";
        break;
    case 2:
        return "Medium";
        break;
    case 3:
        return "Hard";
        break;
    default:
        cout << "\n[ERROR]: getting difficulty Name from diffMod caused unexpected result" << endl;
        return "[FAILED_GETTING_DIFF_NAME]";
        break;

    }
}



void player::print()
{

    const char separator = ' ';
    const int nameWidth = 20;

    cout << "[User Info]: "<< name << "\n" << endl;
    cout << left << setw(nameWidth) << setfill(separator) << "Difficulty:";
    cout << left << setw(nameWidth) << setfill(separator) << getDiffName() << endl;
    cout << left << setw(nameWidth) << setfill(separator) << "HP:";
    cout << left << setw(nameWidth) << setfill(separator) << to_string(HealthPoints) + "/" + to_string(MaxHealth) << endl;
    cout << left << setw(nameWidth) << setfill(separator) << "DMG mod:";
    cout << left << setw(nameWidth) << setfill(separator) << AttackDamageMod << endl;
    cout << left << setw(nameWidth) << setfill(separator) << "Money:";
    cout << left << setw(nameWidth) << setfill(separator) << "$" + to_string(currency) << endl;
    cout << left << setw(nameWidth) << setfill(separator) << "Floor:";
    cout << left << setw(nameWidth) << setfill(separator) << floor << endl;
    cout << left << setw(nameWidth) << setfill(separator) << "Score:";
    cout << left << setw(nameWidth) << setfill(separator) << score << endl;
    cout << endl;
}

ostream& operator<<(ostream& os, player& p)
{
    os << p.name << " " << p.floor << " " << p.diffMod << " " << p.MaxHealth << " " << p.HealthPoints << " " << p.AttackDamageMod << " " << p.currency << " " << p.score << " " << p.password << " ";

    os << p.weaponList.size() << " ";

    for (weapon w : p.getWeaponList())
    {
        os << w << " ";
    }

    return os;
}




istream& operator>>(istream& is, player & p)
{

    int t;
    is >> p.name >> p.floor >> p.diffMod >> p.MaxHealth >> p.HealthPoints >> p.AttackDamageMod >> p.currency  >> p.score >> p.password;

    is >> t;

    //clear weapon list
    p.weaponList.clear();
    
    weapon w;
  
    for (int x = 0; x < t; x++)
    {
        is >> w;
        p.weaponList.push_back(w);
    }

    return is;
}


