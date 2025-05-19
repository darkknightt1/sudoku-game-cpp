#pragma once

#include <vector>
#include <fstream>
#include <sstream>


namespace game
{
    //solve auto if needed (give original file not progress)
    //choose lvl , open lvl from progress , saved lvls inside 
    //
    class boardgame
{
    public:
        //boardgame();
        virtual ~boardgame() = default;

        //io file
        virtual void setboard_from_originalfile(std::ifstream &originalboard) = 0;
        virtual void setboard_from_progressfile(std::ifstream &original ,std::ifstream &progress)= 0;
        virtual void save_progress_to_file(std::ofstream& progressfile) = 0;
        
        //board
        virtual bool modify_board(int col , int row , int val) =0 ;
        virtual void reset_board(std::ifstream &original , std::ofstream &progress) = 0 ;
        virtual void print_board()= 0;
        virtual std::vector<std::vector<int>>& get_board()=0;

        //game
        virtual void start()=0;

    protected:
        int lvl;
        int boardsize;
        std::vector<std::vector<int>> grid; 

    private:


};
}

//correct architecture 
//class game (time , hints)
//    |
//class boardgame pub game (lvls )
//    |
//class sudukoboard pub boardgame

//boardgame board1 = new board(sudukoboard)
