#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "scoreNode.h"
#include "player.h"
using namespace std;

class fileoperations{
    private:

       
        //holds the name of the player file
        string pFilename;
        
        //opens the player file
        fstream pFile;
        

    public:

        void setPlayername(string playername);
  
        //Function that retrieves player data. If file found, player object ptr loads all values and returns true, else return false
        bool LoadPlayer(string filename, player  & p);

        
        
        //Function Saves players progress into a file
        void SavePlayer(player & p);
        
    
};