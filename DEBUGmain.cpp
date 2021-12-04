#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctype.h>
#include <iomanip>
#include <list>
#include <time.h>
#include <stdlib.h>


#include "player.h"
#include "enemy.h"
#include "scoreNode.h"
#include "weapon.h"
#include "fileoperations.h"

using namespace std;



int main()
{
	scoreNode* scorePtr;

	
	scorePtr = new scoreNode("player1", 25);


	scoreNode scorei("Scorei", 100);

	//cout << scorePtr << endl;
	
	list<scoreNode> scoreList;


	//scoreList.push_back(*scorePtr);

	scoreList.push_back(scorei);
	
	
	scoreList.push_back(*scorePtr);


	list<scoreNode>::iterator it;

	it = scoreList.begin();

	//it->print();

	cout << *(it++) << endl;
	cout << *(it++) << endl;

	//scoreList.getCurrent()->print();
	


	
}