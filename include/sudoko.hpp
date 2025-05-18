#pragma once

#define GUI 0
#define DEBUG 1
#define MAX_LVL 5


#include <fstream>
#include <sstream>
#include <string>

#include <vector>
#include <iostream>



namespace sudukogame
{



class board{
    public:
        board(int board , int lvl);
        //virtual ~board();
    
    public:
        //io file
        void setboard_from_originalfile(std::ifstream &sudukooriginalboard  );
        void setboard_from_progressfile(std::ifstream &sudukooriginal ,std::ifstream &sudukoprogress);
        void save_progress_to_file(std::ofstream& progressfile);
        
        //board
        void modify_board(int col , int row , int val);
        void reset_board(std::ifstream &sudukooriginal , std::ofstream &sudukoprogress);
        void print_board();
        std::vector<std::vector<int>>& get_grid();
        
        

    private:
        std::vector<std::vector<int>> grid; 
        std::vector<std::vector<bool>> okaytowrite; 
        int boardsize;
        int lvl;
        int movesallowed;//record no. of empty cells in the board

    
};

class SudukoGame:public board
{
    public:
    protected:
    private:

};





}

