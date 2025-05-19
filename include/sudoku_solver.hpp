#pragma once

#include <vector>
#include <iostream>
#include<cmath>

namespace game
{

class suduko_solver
{
    public:
        suduko_solver(std::vector<std::vector<int>> grid , int boardsize);
        bool solve_backtracking();
        bool is_solved(); //check if the 
        void print_board();
        std::vector<std::vector<int>>& get_board();

    private:
        int boardsize;
        std::vector<std::vector<int>> grid;
        bool isValid(int row, int col, int num) const;
        bool findEmptyCell(int& row, int& col) const;

};





}
