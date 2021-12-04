#include <iostream>
#include <string>
#include <fstream>
#include "scoreNode.h"
#include "player.h"
#include "fileoperations.h"
using namespace std;

       
 //holds the name of the player file

                  string pFilename;
        
 //opens the player file

                   fstream pFile;   

 

void fileoperations::setPlayername(string playername)
{
    pFilename = playername + ".txtfcffff";
}

//Function that retrieves player data. If file found, player object ptr loads all values and returns true, else return false
bool fileoperations::LoadPlayer(string filename, player& p)
{

    filename = filename + ".txt";
    pFile.open(filename, fstream::in);
    
    if (pFile.fail())
    {
        return false;
    }
    pFilename = filename;


    pFile >> p; // TODO

    pFile.close();

    return true;

}

//Function Saves players progress into a file
void fileoperations::SavePlayer(player& p)
{
    pFile.open(pFilename, fstream::out | fstream::trunc);
    
    if (pFile.fail())
    {
         cout << "[CRITCAL ERROR]: attempt to save player caused outstream to fail" << endl;
        return;
    }

    pFile << p;


    pFile.close();


}






