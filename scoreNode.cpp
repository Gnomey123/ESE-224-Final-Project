#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "scoreNode.h"
using namespace std;


//default constructor
scoreNode::scoreNode()
{
    name = "null_name";
    score = 0;
}

scoreNode::scoreNode(string myName, int myScore) {
    name = myName;
    score = myScore;
}


scoreNode::~scoreNode()
{
}


void scoreNode::setName(string n){
    name = n;
}

void scoreNode::setScore(int s){
    score = s;
}

string scoreNode::getName(){
    return name;
}

int scoreNode::getScore(){
    return score;
}



//outputs score
void scoreNode::print()
{
    const char separator = ' ';
    const int nameWidth = 20;


    cout << left << setw(nameWidth) << setfill(separator) <<  "[" + getName() + "]:" << getScore() << endl;
 

}

bool scoreNode::operator <(const scoreNode& nodeToComp)
{
    // comps with > to sort from highest to lowest
    return (this->getScore() > nodeToComp.score);
}

ostream& operator <<(ostream& os, scoreNode& s)
{
    os << s.name << " " << s.score;
    return os;
}

istream& operator >>(istream& is, scoreNode& s)
{

    is >> s.name >> s.score;
    return is;
    
}





