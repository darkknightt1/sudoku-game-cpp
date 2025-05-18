#include "../include/sudoko.hpp"
#include <cmath>
#include <unordered_set>


namespace sudukogame
{

    void board::setboard_from_originalfile(std::ifstream &sudukooriginalboard )
    {
        #if DEBUG
            std::cout<<"DEBUG , setboardfromfile\n";
        #endif

        std::string line;
        int row = 0;
        while ( getline(sudukooriginalboard,line) )//loop through lines in the text file
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
                    grid[row][col] = 0;
                    okaytowrite[row][col] = true;
                } else {
                    grid[row][col] = std::stoi(token);
                    okaytowrite[row][col] = false;
                }
                ++col;
                if (col >= boardsize) break; 
            }
            ++row;
            if (row >= boardsize) break; 
        }
        
    }


    void board::setboard_from_progressfile(std::ifstream &sudukooriginal , std::ifstream &sudukoprogress )
    {

        /*
        will set the grid 2D vector from the progress file 
        will set the okaytomove vector from the original file
        */
        #if DEBUG
            std::cout<<"DEBUG , setboard_from_progressfile\n";
        #endif

        std::string line;
        int row = 0;

        while ( getline(sudukooriginal,line) )//loop through lines in the original suduko file
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

                if (token == ".") 
                okaytowrite[row][col] = true;
                
                else 
                okaytowrite[row][col] = false;
                
                ++col;
                if (col >= boardsize) break; 
            }
            ++row;
            if (row >= boardsize) break; 
        }

        row = 0;

        while ( getline(sudukoprogress, line) )//loop through lines in the progress suduko file
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

                if (token == ".") 
                grid[row][col] = 0;
                    
                 else 
                grid[row][col] = std::stoi(token);
        
                
                ++col;
                if (col >= boardsize) break; 
            }
            ++row;
            if (row >= boardsize) break; 
        }
        
    }

    void board::save_progress_to_file(std::ofstream& progressfile) 
    {
    int root =static_cast<int> (std::sqrt(boardsize));
    for (int row = 0; row < boardsize; ++row) {
        if (row % root == 0) {
            progressfile << "-------------------------------------\n";
        }

        for (int col = 0; col < boardsize; ++col) {
            if (col % root == 0 && col != 0)
                progressfile << "| ";

            if (this->grid[row][col] == 0)
                progressfile << ". ";
            else
                progressfile << grid[row][col] << " ";
        }
        progressfile << "\n";
    }
    progressfile << "-------------------------------------\n";

    progressfile.close();
}

    void board::modify_board(int col , int row , int val)
    {
        if (( col<boardsize && col>=0 ) && ( row<boardsize && row>=0 )&& (val<=boardsize && val>0) )
        {
            if ( okaytowrite[row][col] ) this->grid[row][col]=val;
            else 
            {
                //throw error
                #if DEBUG
                std::cerr<<"writing in an un-writable square\n";
                #endif
            }
        }
        else
        {
            //throw error
            #if DEBUG
            std::cerr<<"intput out of board range\n";
            #endif
                
        }
    }
    
    void board::print_board()
    {
        int root =static_cast<int> (std::sqrt(boardsize));
        for (int row = 0; row < boardsize; ++row) {
            if (row % root == 0) {
                std::cout << "-------------------------------------\n";
            }

            for (int col = 0; col < boardsize; ++col) {
                if (col % root == 0 && col != 0)
                    std::cout << "| ";

                if (this->grid[row][col] == 0)
                    std::cout << ". ";
                else
                    std::cout << grid[row][col] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "-------------------------------------\n";

    }

    bool board::is_solved()
    {
        
        // for (auto& row : grid)
        // {
        //     std::unordered_set<int> seen;
        //     for (int val : row)
        //     {
        //         if (seen.count(val) > 0 || val == 0 )
        //             return false;

        //         seen.insert(val);
        //     }
        // }


        for (int i = 0; i<boardsize; i++)
        {
            std::unordered_set<int> seen;
            for (int j=0 ; j<boardsize ; j++)
            {
                if (seen.count(grid[i][j]) > 0 || grid[i][j] == 0 )
                    return false;

                seen.insert(grid[i][j]);
            }   
        }
        return true;
    }
    board::board(int size , int lvl)
    {
        /*
           parameterized constructor 
           create sizexsize 2d vector and intialize by zero
        */
        #if DEBUG
        std::cout<<"suduko ctor"<<std::endl;
        #endif
        
        //check if size is okay
        int root = static_cast<int>(std::sqrt(size));
        if ( std::sqrt(size) - static_cast<double>(root)  == 0.0 && size > 4)
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
        //input lvl
        if (lvl > 0 && lvl < MAX_LVL)
        {
            this->lvl = lvl;
        }
        else
        {
            //throw error
            #if DEBUG
            std::cout<<"invalid lvl\n";
            #endif
        }
        
       /*grid.resize(9);
        for (auto &row : grid) //more effecient method using iterators
        {row.resize(9,0);}*/
        
       grid.resize(boardsize);
       okaytowrite.resize(boardsize);
       for (int i=0 ; i<boardsize ; i++)
       {
            grid[i].resize(boardsize,0);
            okaytowrite[i].resize(boardsize,false);
       }
    }


}



