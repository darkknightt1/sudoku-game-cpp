#pragma once

#define GUI 0
#define DEBUG 0
#define MAX_LVL 5

#define EXIT 2
#define EXIT_LOOP 5

#include <iostream>
#include "boardgame.hpp"


namespace game
{



class sudokuboard: public boardgame
{
    public:
        sudokuboard(int board);
    
    public:
        //io file
        void setboard_from_originalfile(std::ifstream &sudukooriginalboard)override;
        void setboard_from_progressfile(std::ifstream &sudukooriginal ,std::ifstream &sudukoprogress)override;
        void save_progress_to_file(std::ofstream& progressfile)override;
        
        //board
        bool modify_board(int col , int row , int val) override;
        void reset_board(std::ifstream &sudukooriginal , std::ofstream &sudukoprogress) override;
        void print_board() override;
        std::vector<std::vector<int>>& get_board() override;

        //game loop
        void start()override;

        
        

    private:
        std::vector<std::vector<bool>> okaytowrite; 
        int movesallowed;//record no. of empty cells in the board
        bool solved = false;
        
        //start game helping functions
        int showstartMenu();
        int showloopMenu();
        void initialize_files();
        void make_amove();
        void game_loop(int choice);
        bool is_solved();

};







}

