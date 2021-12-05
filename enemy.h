#pragma once
#include <iostream>
#include <string>
using namespace std;

class enemy 
{
    private:
        
        //This should hold the enemy's name
        string Name;

        string nameList[10] = { "Slime", "Goblin", "Squirrel", "Local Heretic", "Anti-Seawolve", "College Debt Collector", "Python User", "[some who call him]... Tim", "Jellyfish", "Jungle Bat" };
        
        
        //This should hold the maximum health of the enemy
        int MaxHealth;
        
        
        //This should hold the current health of the enemy
        int HealthPoints;
      
        
        //This should hold the attack damage of the enemy
        int AttackDamage;
        
        
        //floor level
        int level = 0;
        
 

        // Currency value
        int currency;
        
        
    public:
        
        void initBasic();
        
        enemy();
        enemy(string n, int maxH, int health, int attack, int lev ,int curr);
        string getName();
       
        //returns the maximum health
        int getMaxHP();
        
        //returns the current health
        int getHP();



        //returns the current damage
        int getDMG();
        
        //returns the level
        int getLVL();
        
        // Returns currency
        int getCurr();
       
        // Sets Name
        void setName(string n);
        
        void ModifyMaxHP(int h);

        // Sets Max HP
        void setMaxHP(int h);
        
        //sets the current health
        void setHP(int h);
       
        //sets the current damage
        void setDMG(int d);
        
        //sets the level of enemy
        void setLVL(int l);
        
        //Increments or decrements the enemy’s health by the input value
        void ModifyHealth(int h);
        
        //Increments or decrements the enemy’s attack damage by the input value
        void ModifyDamage(int d);
        
        //Sets Enemy Value
        void setCurr(int c);

        //prints all info on the enemy
        friend ostream& operator <<(ostream& os, enemy& e);
        
};
