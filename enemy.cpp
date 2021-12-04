#include <iostream>
#include <fstream>
#include <string>
#include "enemy.h"
using namespace std;

enemy::enemy()
{
	Name = "Slime";
	MaxHealth = 10;
	HealthPoints = 10;
	AttackDamage = 1;
	level = 1;
	currency = 5;
}
enemy::enemy(string n, int maxH, int health, int attack, int lev, int curr)
{
	Name = n;
	MaxHealth = maxH;
	HealthPoints = health;
	AttackDamage = attack;
	level = lev;
	currency = curr;
}


void enemy::initBasic()
{
	Name = "Slime";
	MaxHealth = 10;
	HealthPoints = 10;
	AttackDamage = 5;
	level = 1;
	currency = 5;
}


string enemy::getName()
{
	return Name;
}
int enemy::getMaxHP()
{
	return MaxHealth;
}
int enemy::getHP()
{
	return HealthPoints;
}
int enemy::getDMG()
{
	return AttackDamage;
}
int enemy::getLVL()
{
	return level;
}
int enemy::getCurr()
{
	return currency;
}
void enemy::setName(string n)
{
	Name = n;
}
void enemy::setMaxHP(int h)
{
	MaxHealth = h;
	HealthPoints = MaxHealth;
}
void enemy::setHP(int h)
{
	HealthPoints = h;
}
void enemy::setDMG(int d)
{
	AttackDamage = d;
}
void enemy::setLVL(int l)
{
	level = l;
}
void enemy::ModifyHealth(int h)
{
	HealthPoints = HealthPoints + h;
}

void enemy::ModifyMaxHP(int h)
{
	MaxHealth = MaxHealth + h;
	HealthPoints = MaxHealth;
}

void enemy::ModifyDamage(int d)
{
	AttackDamage = AttackDamage + d;
}
void enemy::setCurr(int c)
{
	currency = c;
}
ostream& operator <<(ostream& os, enemy& e)
{
	os << "Level " << e.level << " Enemy: " << e.Name << ", with HP : " << e.MaxHealth << "/" << e.HealthPoints << ", DMG : " << e.AttackDamage << ", and Value : $" << e.currency << endl;
	return os;
}