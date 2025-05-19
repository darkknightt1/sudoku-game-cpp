#include <filesystem>      // C++17
#include "sudoko.hpp"
#include "sudoku_solver.hpp"
#include <unordered_map>
#include <string>

// std::unordered_map <std::string,int> suduko_original_lvls_size ={{"lvls/lvl1",9},
//                                                                  {"lvls/lvl2",9},
//                                                                  {"lvls/lvl3",9},
//                                                                  {"lvls/lvl4",9},
//                                                                  {"lvls/lvl5",16},
//                                                                 };



int main()
{
    // game::sudokuboard s1(9);
    // std::ifstream sudukofilee("lvls/lvl1.suduko");
    //  //std::ifstream *sudukofilee = new std::ifstream("lvls/lvl1.suduko");
    // if (!sudukofilee.is_open())
    // {
    //     //throw error
    //     #if DEBUG
    //     std::cout<<"cant open file\n";
    //     #endif
    // }
    //else s1.setboard_from_originalfile(sudukofilee);

    //s1.print_board();

    // bool file_exists = std::filesystem::exists("lvls/lvl1_progress.suduko");
    // if (file_exists) std::cout<<"file exist\n";
    // else std::cout<<"file doesnot exist\n";
    // std::ofstream progress("lvls/lvl1_progress.suduko");
    // if (!progress.is_open()) {
    //     std::cerr << "Error\n";
    // }
    // else s1.save_progress_to_file(progress);
    // int row;
    // int col;
    // int val;
    // std::cin>>row;
    // std::cin>>col;
    // std::cin>>val;
    // s1.modify_board(col,row,val);
    //s1.print_board();

    //sudukogame::suduko_solver solver(s1.get_grid(),9);
    //solver.solve_backtracking();
    //solver.print_board();




    // game::boardgame* boardd = new game::sudokuboard(9);
    // std::ifstream sudukofilee("lvls/lvl1.suduko");
    // boardd->setboard_from_originalfile(sudukofilee);
    // boardd->print_board();
    // game::suduko_solver solved(boardd->get_board(),9);
    // solved.solve_backtracking();
    // solved.print_board();

    // delete boardd;






    game::boardgame* boardd = new game::sudokuboard(9);
    boardd->start();
    delete boardd;

    return 0;
}

//to do
// 1. add hints
// 2. add errors throw ,try and catch
// 3. add time
// 4. solve gridsize passing issue , 

