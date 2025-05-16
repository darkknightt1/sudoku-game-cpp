#ifndef SUDOKO_HPP
#define SUDOKO_HPP

#define GUI 0
#define DEBUG 1

#include <fstream>
#include <sstream>
#include <string>

#include <vector>

#if GUI == 0
#include <iostream>
#endif

namespace sudukogame
{



class suduko{
    public:
        void setboardfromfile(std::ifstream &sudukoboardfile);
        suduko(int board);
        
        
    private:
        std::vector<std::vector<int>> board; 
        int boardsize;

        

};





}

#endif