#include "sudoko.hpp"
#include <cmath>


namespace sudukogame
{

    void suduko::setboardfromfile(std::ifstream &sudukoboardfile)
    {
        #if DEBUG
            std::cout<<"DEBUG , setboardfromfile"<<std::endl;
        #endif

        std::string line;
        int row = 0;
        while ( getline(sudukoboardfile,line) )//loop through lines in the text file
        {
                // Skip separator lines
            if (line.find('-') != std::string::npos || line.empty())
                continue;

            std::istringstream iss(line);
            std::string token;
            int col = 0;

            while (iss >> token) {//loop through each letter in the line
                if (token == "|")
                    continue;

                if (token == ".") {
                    board[row][col] = 0;
                } else {
                    board[row][col] = std::stoi(token);
                }
                ++col;
                if (col >= boardsize) break; 
            }
            ++row;
            if (row >= boardsize) break; 
        }
    }

    suduko::suduko(int size)
    {
        /*
           default constructor 
           create sizexsize 2d vector and intialize by zero
        */
        #if DEBUG
        std::cout<<"suduko ctor"<<std::endl;
        #endif
        
        //check if size is applicable
        int root = static_cast<int>(std::sqrt(size));
        if ( std::sqrt(size) - static_cast<int>(root)  == 0.0 && size > 4)
        {
            this->boardsize = size; 
            #if DEBUG
            std::cout<<"valid board size\n";
            #endif
        }
        else
        {
            //throw error
            #if DEBUG
            std::cout<<"invalid board size\n";
            #endif
        }
        
       /*board.resize(9);
        for (auto &row : board) //more effecient method using iterators
        {row.resize(9,0);}*/
        
       board.resize(boardsize);
       for (int i=0 ; i<boardsize ; i++)
       {
            board[i].resize(boardsize,0);
       }
    }


}

