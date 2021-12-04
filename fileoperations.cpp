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

 

void fileoperations::setFilename(string filename)
{
    pFilename = filename + ".txt";
}

//Function that retrieves player data. If file found, player object ptr loads all values and returns true, else return false
bool fileoperations::LoadPlayer(player& p)
{

    
    pFile.open(pFilename, fstream::in);
    
    if (pFile.fail())
    {
        pFile.close();
        return false;
    }


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
         cout << "[ERROR]: attempt to save player caused outstream to fail" << endl;
        return;
    }

    pFile << p;


    pFile.close();


}


bool fileoperations::saveFileExists(string password)
{
    password = password + ".txt";
    bool ret = false;
    ifstream ifile;

    ifile.open(password);

    if (ifile)
    {
        pFilename = password;
        ret = true;
    }
    else
    {
        ret = false;
    }
    ifile.close();
    return ret;
}






