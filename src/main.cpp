#include "include/sudoko.hpp"
#include <filesystem> // C++17


int main()
{
    sudukogame::board s1(9,1);
    std::ifstream sudukofilee("lvls/lvl1.suduko");
    //std::ifstream *sudukofilee = new std::ifstream("lvls/lvl1.suduko");
    if (!sudukofilee.is_open())
    {
        //throw error
        #if DEBUG
        std::cout<<"cant open file\n";
        #endif
    }
    else s1.setboard_from_originalfile(sudukofilee);

    s1.print_board();

    bool file_exists = std::filesystem::exists("lvls/lvl1_progress.suduko");
    if (file_exists) std::cout<<"file exist\n";
    else std::cout<<"file doesnot exist\n";
    // std::ofstream progress("lvls/lvl1_progress.suduko");
    // if (!progress.is_open()) {
    //     std::cerr << "Error\n";
    // }
    // else s1.save_progress_to_file(progress);
    int row;
    int col;
    int val;
    std::cin>>row;
    std::cin>>col;
    std::cin>>val;
    s1.modify_board(col,row,val);
    s1.print_board();
    s1.is_solved();


    
    return 0;
}

