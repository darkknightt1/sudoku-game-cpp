#include "sudoku_solver.hpp"
#include <unordered_set>


namespace game
{

suduko_solver::suduko_solver(std::vector<std::vector<int>> grid , int boardsize)
{
    this->grid = grid;
    this->boardsize = boardsize;
}
bool suduko_solver::is_solved()
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

        //checking rows uniqueness
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

        //checking cols uniqueness
        for (int i = 0; i<boardsize; i++)
        {
            std::unordered_set<int> seen;
            for (int j=0 ; j<boardsize ; j++)
            {
                if (seen.count(grid[j][i]) > 0 || grid[j][i] == 0 )
                    return false;

                seen.insert(grid[j][i]);
            }   
        }


        return true;
}
bool suduko_solver::isValid(int row, int col, int num) const
     {

        /*
        check if a certain input for the board is valid or not by checking
        its uniqueness in row and cols and box
        */

        // Check row
        for (int x = 0; x < boardsize; ++x) {
            if (grid[row][x] == num) return false;
        }

        // Check column
        for (int x = 0; x < boardsize; ++x) {
            if (grid[x][col] == num) return false;
        }

        int root = static_cast<int>(std::sqrt(boardsize));
        // Check root X root box
        int startRow = row - row % root;
        int startCol = col - col % root;

        for (int i = 0; i < root; ++i)
            for (int j = 0; j < root; ++j)
                if (grid[startRow + i][startCol + j] == num)
                    return false;

        return true;
   }
bool suduko_solver::findEmptyCell(int& row, int& col) const {
        for (row = 0; row < 9; ++row)
            for (col = 0; col < 9; ++col)
                if (grid[row][col] == 0)
                    return true;
        return false;
    }
bool suduko_solver::solve_backtracking()
    {

        int row, col;
        if (!findEmptyCell(row, col))
            return true; // Puzzle solved

        for (int num = 1; num <= boardsize; ++num) {
            if (isValid(row, col, num)) {
                grid[row][col] = num;

                if (solve_backtracking())
                    return true;

                grid[row][col] = 0; // Backtrack
            }
        }

        return false; // Trigger backtracking
    }


void suduko_solver::print_board()
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
}

