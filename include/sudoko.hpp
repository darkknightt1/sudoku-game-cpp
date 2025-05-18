#pragma once

#define GUI 0
#define DEBUG 1
#define MAX_LVL 5


#include <fstream>
#include <sstream>
#include <string>

#include <vector>

#if GUI == 0
#include <iostream>
#endif

namespace sudukogame
{



class board{
    public:
        board(int board , int lvl);
        //virtual ~board();
    
    public:
        void setboard_from_originalfile(std::ifstream &sudukooriginalboard  );
        void setboard_from_progressfile(std::ifstream &sudukooriginal ,std::ifstream &sudukoprogress);
        void save_progress_to_file(std::ofstream& progressfile);
        void modify_board(int col , int row , int val);
        void print_board();
        bool is_solved();
        
        
        
    private:
        std::vector<std::vector<int>> grid; 
        std::vector<std::vector<bool>> okaytowrite; 
        int boardsize;
        int lvl;


};

class SudukoGame:public board
{
    public:
    protected:
    private:

};





}

