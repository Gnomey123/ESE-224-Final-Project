#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <fstream>
#include <ctype.h>
#include <iomanip>
#include <algorithm>
#include <time.h>
#include <stdlib.h>

#include "player.h"
#include "enemy.h"
#include "scoreNode.h"
#include "weapon.h"
#include "fileoperations.h"

///*

using namespace std;

//rand num gen func
int genRandNum(int a, int b);

bool Resp();

player myPlayer;

enemy myEnemy;

queue<enemy> enemy_rand_encounter_Queue;

fileoperations myFileOp;


//generate password for player save/load functionality 
string genSavePassword();


//Global scoreboard list
list<scoreNode> sbList;



//Function Saves Scoreboard values to the "scoreboard.txt" once user wins or dies
void saveScoreListToFile(scoreNode head);

//Function to print scores from sbList
void printScoreList();

void printScoreList(list<scoreNode> sblist);


//	does all combat UI, returns result of victory or not
int combate();

stack<string> combateLogStack;

//Function to load init ScoreList from "scoreboard.txt"
void loadScoreList();

void sbSearchForName(string);


list<scoreNode> genAvgScoreList();

void sbSortByScore();

void sbSortByName();

void sbAddNewScore(string name, int score);

void initEnemyQueue();//	add 5 random encounter enemies to the Queue

stack<string> enemiesDefeated;

void clearQueue(queue<enemy> & toClear);	// according to user guides, the only way to clear a queue is to swap it with an empty one


/*********************************************************************************************************************************/
//	Main Function w/ funcSeg's (funcSeg's = callable functions that organize and segregate game operations)
//	Each Seg is defined by a number, used to call one-another when returning

#define valQuitGame 0;		// when called, game will properly clear data values and close

#define valMenuSeg 1;		// menuSeg is called via alias
int menuSeg();

#define	valNewPlayerSeg 2;	// newPlayerSeg is called via alias
int newPlayerSeg();

#define	valLoadPlayerSeg 3;	// newPlayerSeg is called via alias
int loadPlayerSeg();

#define valMasterSeg 4;		// masterSeg is called via alias
int masterSeg();


int main()
{

	/*********************/
	//	GLOBAL INIT ZONE
	srand((unsigned int)time(NULL));

	int segVal = 1;
	/*********************/

	while (segVal != 0)
	{


		switch (segVal)
		{
		case 0:						// valQuitGame		[0]
			
			break;

		case 1:						// valMenuSeg		[1]
			segVal = menuSeg();
			sbList.clear();		//clear list after to clear memory values
			break;
		
		case 2:						// valNewPlayerSeg	[2]
			segVal = newPlayerSeg();
			break;
		
		case 3:						// valLoadPlayerSeg	[3]
			segVal = loadPlayerSeg();
			break;
		
		case 4:						// valMasterSeg		[4]
			segVal = masterSeg();

			if (!enemiesDefeated.empty())
			{
				cout << "Enemies defeated in your playthrough:\n" << endl;
				while (!enemiesDefeated.empty())
				{
					cout << enemiesDefeated.top() << endl;
					enemiesDefeated.pop();
				}
			}


			break;

		default:
			cout << "[CRIT ERROR]: Global int [SegVal =" << segVal << "] caused unexpected switch case.\nAborting Program..." << endl;
			exit(1);
				
			break;


		}
	}

	exit(0);

}



//*******************************
// Main Menu SEG	[1]
//*******************************
int menuSeg()
{


	loadScoreList();
	char cMenu;
	bool menuLoop = true;


	string newPlayerName;



	cout << "Welcome to the game!" << endl;

	while (menuLoop)
	{
		cout << "----------------\nMain Menu:" << endl;

		cout << "(a) View Scoreboard by score" << endl;
		cout << "(b) View Scoreboard by name" << endl;
		cout << "(c) View Global average score" << endl;
		cout << "(d) Search Scoreboard by name" << endl;
		cout << "(e) New Game" << endl;
		cout << "(f) Load Game" << endl;
		cout << "(g) Quit" << endl;


		cout << "\n: ";
		cin >> cMenu;
		cout << "---\n" << endl;
		cMenu = tolower(cMenu);
		string name;
		switch (cMenu)
		{
		case 'a':


			cout << "Top Scores:  " << genSavePassword() << endl;
			sbSortByScore();
			printScoreList();
			break;

		case 'b':
			cout << "Scores By Name:" << endl;
			sbSortByName();
			printScoreList();
			break;

		case 'c':
			cout << "All Player Cumulative Ranking:" << endl;
			printScoreList(genAvgScoreList());
			break;

		case 'd':
			cout << "Please enter name you'd like to search for (no spaces)" << endl;
			cout << ": ";
			cin >> name;
			cout << endl;

			cout << "searching for \"" << name << "\"..." << endl;

			sbSearchForName(name);

			break;

		case 'e':
			menuLoop = false;
			cout << "Making new player:" << endl;
			
			// call new player SEG
			return valNewPlayerSeg;
			break;


		case 'f':
			menuLoop = false;

			cout << "Loading existing player:" << endl;

			// call load player SEG
			return valLoadPlayerSeg;
			break;

		case 'g':

			sbList.clear();

			// call quit SEG
			return valQuitGame;
			break;

		default:
			cout << "Please enter a valid selection..." << endl;
			break;
		}
	}


}

//*******************************
// Generate new player SEG
//*******************************

int newPlayerSeg()
{
	string newPlayerName;
	bool isLooping = true;
	
	while (isLooping)
	{
		char c;
		int i;

		cout << "\nPlease enter a new player name (or enter g for Main Menu)\n[no spaces]:  ";
		cin >> newPlayerName;
		cout << endl;


		//Check for 'g' response and prompt before exiting
		if (newPlayerName == "g")
		{
				return valMenuSeg;
		}




		cout << "\"" << newPlayerName << "\", Is this name correct?" << endl;
		if (Resp())
		{
			while (1)
			{
				cout << "\nPlease enter a difficulty\n[1=Easy, 2=Medium, 3=Hard]: ";
				cin >> i;
				if ((i == 1) || (i == 2) || (i == 3))
				{
					cout << endl;
					break;
				}
				else
				{
					cout << "Please enter a valid number" << endl;
				}
			}
			string pass = genSavePassword();
			
			cout << "IMPORTANT:" << endl;
			cout << "In order to retrieve your saved player, you must write down your unique save password." << endl;

			cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
			cout << "@   YOUR PASSWORD: " << pass << "     @" << endl;
			cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
			
			cout << "\*such an original 80s idea, ik...\*" << endl;

			cout << "\nEnter any char to confirm you've written down your password to a piece of paper" << endl;

			char c;
			cin >> c;

			cout << "\nStarting New Game..." << endl;

			

			myPlayer.setName(newPlayerName);
			myPlayer.setDiffMod(i);
			myPlayer.upgradeWeaponList();//			Always called first thing

			myFileOp.setFilename(pass);
			myPlayer.setPassword(pass);
			

			isLooping = false;

			return valMasterSeg;
		}
		else
		{
			cout << "Okay. Starting again..." << endl;
		}



	}





}
	
// Load new player using password
int loadPlayerSeg() // all todo
{

	bool isLooping = true;
	string password;

	while (isLooping)
	{
		char c;
		int i;

		cout << "\nPlease enter your save password (or enter g for Main Menu)\n[xxx-xxx-xxxx]:  ";
		cin >> password;
		cout << endl;


		//Check for 'g' response and prompt before exiting
		if (password == "g")
		{
			return valMenuSeg;
		}

		if (myFileOp.saveFileExists(password))
		{

			myFileOp.LoadPlayer(myPlayer);

			isLooping = false;
			cout << "Loading saved player \"" << myPlayer.getName() << "\"\n..." << endl;
			return valMasterSeg;
			break;
		}
		else
		{
			cout << "\nNo save found. Please try again" << endl;
		}
			
		

	}

}






	///
	//
	//GAME_RUNNING
	//
	///


int masterSeg()
{

	bool gameRunning = true;
	bool isShopping = false;

	int i;
	int multiplier;
	int weaponSel;
	char c;
	string name;
	stack<string> boughtWeapons;


	while (gameRunning)
	{


		int fightRes;

		cout << "\n----------------\nPlease choose from one of the following:\n" << endl;
		
		// Change choice 1 if FistOnlyChal is true
		if (myPlayer.isUsingFistChal())
		{
			cout << "(x) Buy Weapons from the shop [Close due to covid, reopening on the date of TBA]" << endl;
		}
		else
		{
			cout << "(1) Buy Weapons from the shop" << endl;
		}
		
		cout << "(2) Get current player stats" << endl;
		cout << "(3) Fight a random encountered enemy (" << enemy_rand_encounter_Queue.size() << "/5)" << endl;
		
		// Change choice 1 if FistOnlyChal is true
		if (myPlayer.isMoneySaveChal())
		{
			cout << "(x) Fight the next floor boss enemy [No money? sorry bud: no ticket, no ride]" << endl;
		}
		else if((myPlayer.getCurr() < 25))
		{
			cout << "(4) Fight the next floor boss enemy [Godspeed, you magnificent bastard]" << endl;
		}
		else
		{
			cout << "(4) Fight the next floor boss enemy" << endl;
		}
		
		cout << "(5) Display Global Scoreboard" << endl;
		cout << "(6) Save and quit to Main Menu" << endl;

		cout << "\nYour choice: ";

		cin >> i;
		cout << "----------------" << endl;

			
				
				
			switch (i)
			{
					
			case 1:
				if (myPlayer.isUsingFistChal())
				{
					cout << "\n[Huell]: We're closed....\n?\nClosed..." << endl;
					break;
				}

				cout << "You currently have $" << myPlayer.getCurr() << " available" << endl;
				cout << "[Catalog]\n" << endl;
				myPlayer.printWeaponList();

				cout << "----" << endl;
				cout << "Enter a number as shown to add it to your cart. When finished, enter any other number to checkout" << endl;
				
					

				isShopping = true;
				while (isShopping)
				{
					cin >> weaponSel;
					switch (myPlayer.buyWeapon(weaponSel))
					{
					case -1:
						isShopping = false;
						cout << "\nExiting shop" << endl;
						break;
					case 0:
						cout << "...not enough money to buy ( $" << myPlayer.getCurr() << " )." << endl;
						break;
					case 1:
						boughtWeapons.push(myPlayer.getWeaponIndexName(weaponSel));
						cout << "item bought." << endl;
						break;
					default:
						cout << "[ERROR] shop default statement reached" << endl;
						break;
					}
				}
				cout << "\nShop Tracker" << endl;
				cout << "[Weapon types bought]:\n" << endl;

				while (!boughtWeapons.empty())
				{
					cout << boughtWeapons.top() << endl;
					boughtWeapons.pop();
				}

				break;

				

			case 2:

				
				myPlayer.print();
				cout << "[Weapon Catalog]\n" << endl;
				myPlayer.printWeaponList();
				break;

				
			case 3:
				if (enemy_rand_encounter_Queue.empty())
				{
					cout << "[INFO]: User used up all available rand enemies in queue. In order to maintain original game flow, reloading queue..." << endl;
					initEnemyQueue();
				}

				myEnemy = enemy_rand_encounter_Queue.front();
				enemy_rand_encounter_Queue.pop();


				//if user is doing x2 enemy double trouble chal, x2 health
				if (myPlayer.isDoubleTroubleChal())
				{
					myEnemy.ModifyMaxHP(myEnemy.getMaxHP());
				}


				cout << "\nSeeking for a fight, you approach an enemy with the following stats:\n" << endl;


				fightRes = combate();


				cout << "[Combat Log]:\n" << endl;

				while (!combateLogStack.empty())
				{
					cout << combateLogStack.top() << endl;
					combateLogStack.pop();
				}

				if (fightRes == 0)
				{
					cout << "\n\nOOOFFF, you seam to be dead at the moment." << endl;

					cout << "Your final score: " << myPlayer.getScore() << " points" << endl;
					

					sbAddNewScore(myPlayer.getName(), myPlayer.getScore());


					cout << "Global Top Scores: \n" << endl;

					printScoreList();

					cout << "Better luck next time!" << endl;

					return menuSeg();

				}

				else if (fightRes == 1)
				{
					cout << "\n\nYou won the battle! And you got additional money from the enemy!" << endl;

					myPlayer.ModifyCurrency(myEnemy.getCurr());

					myPlayer.addScore(myPlayer.getFloor());


				}
				else
				{
					cout << "[ERROR] combat returned unexpected val" << endl;
				}
				
				break;
			case 4:
				if (myPlayer.isMoneySaveChal() && (myPlayer.getCurr() < 25))
				{
					cout << "[Infomaniac]: Whoops! You Have To Put The CD In Your Computer! (get more money pal [" << myPlayer.getCurr() << "/25] )" << endl;
					break;
				}
				


				myEnemy.initBasic();
				if (myPlayer.getFloor() == 1)
				{
					myEnemy.setName("Dirty Bubble");
				}
				else if (myPlayer.getFloor() == 2)
				{
					myEnemy.setName("Man Ray");
				}
				else if(myPlayer.getFloor() == 2)
				{
					myEnemy.setName("The Flying Dutchman");
				}
				else
				{
					myEnemy.setName("Robo Spongebob");
				}



				
				
				myEnemy.setMaxHP((myPlayer.getDiffMod() * 10));

				myEnemy.ModifyMaxHP((myPlayer.getFloor() * 35));
				

				myEnemy.setLVL(myPlayer.getFloor());
				myEnemy.setCurr((myPlayer.getFloor()) * (genRandNum(1, 3))+ 5);
				
				myEnemy.setDMG((myPlayer.getFloor()* 2) + 2);


				//if user is doing x2 enemy double trouble chal, x2 health
				if (myPlayer.isDoubleTroubleChal())
				{
					myEnemy.ModifyMaxHP(myEnemy.getMaxHP());
				}

				cout << "\nMaking your way to the top, you are ambushed by the dreaded \"" << myEnemy.getName() << "\" with the stats of:\n" << endl;


				fightRes = combate();

				cout << "[Combat Log]:\n" << endl;

				while (!combateLogStack.empty())
				{
					cout << combateLogStack.top() << endl;
					combateLogStack.pop();
				}

				if (fightRes == 0)
				{
					cout << "\n\nOOOFFF, you seam to be dead at the moment." << endl;

					cout << "Your final score: " << myPlayer.getScore() << " points" << endl;


					sbAddNewScore(myPlayer.getName(), myPlayer.getScore());


					cout << "Global Top Scores: \n" << endl;

					printScoreList();

					cout << "Better luck next time!" << endl;

					return menuSeg();

				}

				else if (fightRes == 1)
				{
					clearQueue(enemy_rand_encounter_Queue);

					if (myPlayer.getFloor() == 4)
					{
						cout << "CONGRATULATIONS! YOU\'VE FINALLY BEATEN Spongebob Battle for Bikini Bottom" << endl;

						cout << "Your final score: " << myPlayer.getScore() << " points" << endl;

						sbAddNewScore(myPlayer.getName(), myPlayer.getScore());
						
						cout << "Global Top Scores: \n" << endl;

						printScoreList();

						cout << "\nYour Global Scores (by name): \n" << endl;
						sbSearchForName(myPlayer.getName());
						
						return menuSeg();
					}

					myPlayer.setFloor(myPlayer.getFloor() + 1);

					myPlayer.ModifyCurrency(myEnemy.getCurr());
					
					myPlayer.setHP(myPlayer.getMaxHP());

					cout << "\n\nYou won the battle! You gain back your HP, get brand new weapons available for sale, and advance to the next Level..." << myPlayer.getFloor() << endl;

					myPlayer.upgradeWeaponList();

					myPlayer.addScore(myPlayer.getFloor()*10);

					initEnemyQueue();


					multiplier = 0;

					if (myPlayer.isMoneySaveChal())
					{
						myPlayer.setMoneySaveChal(false);
						multiplier += 2;
					}

					if (myPlayer.isUsingFistChal())
					{
						myPlayer.setUsingFistChal(false);
						multiplier += 2;
					}


					if (myPlayer.isHalfHealthChal())
					{
						myPlayer.setHalfHealthChal(false);
						myPlayer.setMaxHP(26);
						myPlayer.setHP(26);
						multiplier += 2;
					}


					if (myPlayer.isDoubleTroubleChal())
					{
						myPlayer.setDoubleTroubleChal(false);
						multiplier += 2;
					}

					if (multiplier != 0)
					{
						cout << "Nice work on those challenges! you've got a x" << multiplier << " point multiplier!" << endl;
						cout << "You can now live in harmony....\n" << endl;

						myPlayer.setScore(myPlayer.getScore()* multiplier);
					}



					cout << endl;
					cout << "_____________________" << endl;
					cout << "|OpTiNal cHaLlEnGes! |" << endl;
					cout << "|____________________|" << endl;

					cout << "WannA sEE thEM? [ALl x2 pOINTS]" << endl;
					if (Resp())
					{
						cout << "\nMoney Save Challenge (aka: gotta have 25 dollars to fight big-boss)" << endl;

						if (Resp())
						{
							myPlayer.setMoneySaveChal(true);
						}

						cout << "\nUsing Fist Only Challenge (aka: Chuck Norris simulation, no weapons [shopping or using], only kicks that can cure cancer)" << endl;

						if (Resp())
						{
							myPlayer.setUsingFistChal(true);
						}

						cout << "\nHalf Health Challenge (aka: Become Prince Philip, but get your youth back after big-boss)" << endl;

						if (Resp())
						{
							myPlayer.setMaxHP(13);
							myPlayer.setHP(13);
							myPlayer.setHalfHealthChal(true);
						}

						cout << "\nDouble Trouble Challenge (aka: Give your next enemies plot armor. Random + boss enemies lose it after big-boss)" << endl;

						if (Resp())
						{
							myPlayer.setDoubleTroubleChal(true);
						}

					}




				}
				else
				{
					cout << "[ERROR] combat returned unexpected val" << endl;
				}




				break;
			case 5:
				cout << "\nPlease select an option (or enter any char to exit):" << endl;
				cout << "View Scoreboard by score" << endl;
				cout << "(b) View Scoreboard by name" << endl;
				cout << "(c) View Global average score" << endl;
				cout << "(d) Search Scoreboard by name" << endl;
				cout << ":";
				
				
				cin >> c;
				cout << endl;


				loadScoreList();//get scoreList ready

				switch (c)
				{
				case 'a':

					cout << "Top Scores:  " << genSavePassword() << endl;
					sbSortByScore();
					printScoreList();
					break;

				case 'b':
					cout << "Scores By Name:" << endl;
					sbSortByName();
					printScoreList();
					break;

				case 'c':
					cout << "All Player Cumulative Ranking:" << endl;
					printScoreList(genAvgScoreList());
					break;

				case 'd':
					cout << "Please enter name you'd like to search for (no spaces)" << endl;
					cout << ": ";
					cin >> name;
					cout << endl;

					cout << "searching for \"" << name << "\"..." << endl;

					sbSearchForName(name);
					break;
				default:
					break;
				}
				sbList.clear();

				break;
			case 6:
				



				myFileOp.SavePlayer(myPlayer);
				
				cout << "Bye Bye..." << endl;
				return valMenuSeg;
				break;
			default:
				cout << "Please enter a valid choice." << endl;
				break;
			}
			

	}

	



	

}


int combate()
{
	cout << myEnemy;
	char charI;
	int i, response = 1;
	cout << "\n_______________________" << endl;
	cout << "\nYour current stats:\n" << endl;
	
	myPlayer.print();
	cout << "_______________________" << endl;
	cout << "\nWhich weapon will you use?\n" << endl;

	if (!myPlayer.isUsingFistChal())
	{
		myPlayer.printWeaponList();
	}
	
	cout << "(f)  ";
	cout << left << setw(20) << setfill(' ') << "Fists";
	cout << left << setw(20) << setfill(' ') << "5";
	cout << left << setw(20) << setfill(' ') << "Nothing";
	cout << left << setw(20) << setfill(' ') << "N/A";
	cout << endl;
	
	while (1)
	{
			cout << "Choice: ";
			cin >> charI;

			cout << endl;

			response = myPlayer.actAttack(charI);
			if (response == -1)
			{
				cout << "Please enter a valid choice again" << endl;
			}
			else if (response == 0)
			{
				cout << "Please chose a different weapon; you don't have any of that type" << endl;
			}
			else
			{
				cout << "\nYou do " << response << " DMG to the enemy" << endl;
				myEnemy.ModifyHealth((-1)*response);
				break;
			}
	}

	combateLogStack.push("\"" + myEnemy.getName() + "\"  Health: [" + to_string(myEnemy.getHP()) + "/" + to_string(myEnemy.getMaxHP()) + "]"); //really ugly string, but it's the most efficient for the cpu (I'm told...)

	if (myEnemy.getHP() <= 0)
	{
		enemiesDefeated.push(myEnemy.getName());
		return 1;
	}

	cout << "_______________________________________________________" << endl;
	cout << "[Enemy " << myEnemy.getName() << " Does " << myEnemy.getDMG() << " DMP to you]" << endl;
	cout << "_______________________________________________________" << endl;
	myPlayer.ModifyHealth((-1) * myEnemy.getDMG());

	combateLogStack.push("\"" + myPlayer.getName() + "\"  Health: [" + to_string(myPlayer.getHP()) + "/" + to_string(myPlayer.getMaxHP()) + "]");

	if (myPlayer.getHP() <= 0)
	{
		return 0;
	}

	return combate();

}



int genRandNum(int a, int b)
{
	return (rand() % (b - a + 1) + a);
}



bool Resp()
{
	bool isTrue;
	char c;
	cout << "[y / (N or any char) ]: ";
	cin >> c;
	isTrue = (tolower(c) == 'y');
	cout << endl;
	return isTrue;

}


void sbSortByScore()
{

	sbList.sort();
	
}


//Init sbList
void loadScoreList()
{
	fstream sbFile;

	sbFile.open("scoreboard.txt", fstream::in);

	if (sbFile.fail())
	{
		cout << "[CRITCAL ERROR]: attempt to loadScoreList caused instream to fail" << endl;
		exit(1);
	}


	
	string tempName;
	int tempScore;

	while (!sbFile.eof())
	{
	
		sbFile >> tempName >> tempScore;

		sbList.push_back(scoreNode(tempName, tempScore));
	}

}

void sbSortByName()
{
	sbList.sort([](scoreNode &lhs, scoreNode &rhs) 
		{
			// comps with > to sort from highest to lowest (A to Z)
			return lhs.getName() < rhs.getName();
		});
	
}



void sbSortByName(list<scoreNode> &listToSort)
{
	listToSort.sort([](scoreNode& lhs, scoreNode& rhs)
		{
			// comps with > to sort from highest to lowest (A to Z)
			return lhs.getName() < rhs.getName();
		});
	
}


//Function Saves Scoreboard values to the "scoreboard.txt" once user wins or dies
void saveScoreListToFile(scoreNode head)
{

	fstream sbFile;

	sbFile.open("scoreboard.txt", fstream::out | fstream::trunc);

	if (sbFile.fail())
	{
		cout << "[CRITCAL ERROR]: attempt to saveScoreListToFile caused outstream to fail" << endl;
		exit(1);
	}

	sbFile.close();



}


//Function to print scores from sbList
void printScoreList()
{

	

	auto sbListPtr = sbList.begin();

	while (sbListPtr != (sbList).end())
	{
		(sbListPtr++)->print();

	}

	cout << "\n" << endl;

}


void printScoreList(list<scoreNode> sblist)
{



	auto sbListPtr = sblist.begin();

	while (sbListPtr != (sblist).end())
	{
		(sbListPtr++)->print();

	}

	cout << "\n" << endl;
	

}


void sbSearchForName(string nameToFind)
{
	int scoresFound = 0;
	for (scoreNode scoreN : sbList)
	{
		if (scoreN.getName() == nameToFind)
		{
			scoreN.print();
			scoresFound++;
		}
	}

	if (scoresFound > 1)
	{
		cout << "[" << scoresFound << " names found" << "]" << endl;
		return;
	}

	if (scoresFound == 1)
	{
		cout << "[" << scoresFound << " name found" << "]" << endl;
		return;
	}


	cout << "[no names found]" << endl;

}

void sbAddNewScore(string name, int score)
{
	fstream sbFile;

	sbFile.open("scoreboard.txt", std::fstream::out | std::fstream::app);

	sbFile << endl;
	sbFile << name << " " << score;

	sbFile.close();

	sbSortByScore();
}

list<scoreNode> genAvgScoreList()
{
	//preserve OG sbList
	list<scoreNode> sbListCPY;
	sbListCPY = sbList;


	list<scoreNode> sbAVGList;

	sbSortByName(sbListCPY);

	

	int occurs = 0, totscore = 0;

	


	stack<scoreNode> scoreNameStack;

	string s;
	string priorName;
	string currName = sbListCPY.begin()->getName();

	for(scoreNode score : sbListCPY)
	{
		priorName = currName;

		currName = score.getName();
		

		if (currName == priorName)
		{
			scoreNameStack.push(score);
			
		}
		else
		{
			while (!scoreNameStack.empty())
			{
				totscore += scoreNameStack.top().getScore();
				occurs++;
				s = scoreNameStack.top().getName();
				scoreNameStack.pop();
			}
			sbAVGList.push_back(scoreNode(s, totscore / occurs));



			occurs = 0;
			totscore = 0;

			scoreNameStack.push(score);
		}




	}

	
	while (!scoreNameStack.empty())
	{
		totscore += scoreNameStack.top().getScore();
		occurs++;
		s = scoreNameStack.top().getName();
		scoreNameStack.pop();
	}
	sbAVGList.push_back(scoreNode(s, totscore / occurs));

	
	sbAVGList.sort();
	sbAVGList.reverse();
	return sbAVGList;
}


void initEnemyQueue()
{
	for (int x = 0; x < 5; x++)
	{
		myEnemy.initBasic();
		myEnemy.ModifyMaxHP(genRandNum(0, 5));

		myEnemy.setLVL(myPlayer.getFloor());
		myEnemy.setCurr((myPlayer.getFloor()) * (genRandNum(1, 3)));
		myEnemy.setDMG(myPlayer.getFloor());

		myEnemy.ModifyMaxHP((myPlayer.getDiffMod() - 1) * 2);

		enemy_rand_encounter_Queue.push(myEnemy);
	}

}


//Password Gen
string genSavePassword()
{
	string strToReturn;

	//Gen first 3 digits
	strToReturn += to_string(genRandNum(0, 9));
	strToReturn += to_string(genRandNum(0, 9));
	strToReturn += to_string(genRandNum(0, 9));

	//Gen second 3 digits w/ dash
	strToReturn += "-";
	strToReturn += to_string(genRandNum(0, 9));
	strToReturn += to_string(genRandNum(0, 9));
	strToReturn += to_string(genRandNum(0, 9));

	//Gen final 4 digits w/ dash	
	strToReturn += "-";
	strToReturn += to_string(genRandNum(0, 9));
	strToReturn += to_string(genRandNum(0, 9));
	strToReturn += to_string(genRandNum(0, 9));
	strToReturn += to_string(genRandNum(0, 9));

	return strToReturn;

}

void clearQueue(queue<enemy>& toClear)
{
	queue<enemy> empty;
	swap(toClear, empty);
}




//*/
