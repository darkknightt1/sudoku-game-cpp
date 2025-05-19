#include "sudoko.hpp"
#include "sudoku_solver.hpp"
#include <cmath>
#include <filesystem>
#include <unordered_set>

namespace game
{

    void sudokuboard::setboard_from_originalfile(std::ifstream &sudukooriginalboard )
    {
        #if DEBUG
            std::cout<<"DEBUG , setboardfromfile\n";
        #endif

        std::string line;
        int row = 0;
        this->movesallowed=0;
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
                    movesallowed++;
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

    void sudokuboard::setboard_from_progressfile(std::ifstream &sudukooriginal , std::ifstream &sudukoprogress )
    {

        /*
        will set the grid 2D vector from the progress file 
        will set the okaytomove vector from the original file
        */
        #if DEBUG
            std::cout<<"DEBUG , setboard_from_progressfile\n";
        #endif

        std::string line;
        this->movesallowed = 0;
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
                {
                    grid[row][col] = 0;
                    movesallowed++;
                } 

                 else 
                grid[row][col] = std::stoi(token);
        
                
                ++col;
                if (col >= boardsize) break; 
            }
            ++row;
            if (row >= boardsize) break; 
        }
        
    }

    void sudokuboard::save_progress_to_file(std::ofstream& progressfile) 
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

    bool sudokuboard::modify_board(int col , int row , int val)
    {
        if (( col<boardsize && col>=0 ) && ( row<boardsize && row>=0 )&& (val<=boardsize && val>0) )
        {
            if ( okaytowrite[row][col] ) { 
                this->grid[row][col]=val;
                movesallowed--;
                return true;
            }

            else 
            {
                //throw error
                #if DEBUG
                std::cerr<<"writing in an un-writable square\n";
                #endif
                return false;
            }
        }
        else
        {
            //throw error
            #if DEBUG
            std::cerr<<"intput out of board range\n";
            #endif
            return false;      
        }
    }
    
    void sudokuboard::reset_board(std::ifstream &sudukooriginal , std::ofstream &sudukoprogress)
    {
        setboard_from_originalfile(sudukooriginal);
        save_progress_to_file(sudukoprogress);    
    } 

    void sudokuboard::print_board()
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
    
    std::vector<std::vector<int>>& sudokuboard::get_board()
    {
        return grid;
    }
    
    sudokuboard::sudokuboard(int size )
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
    
    int sudokuboard::showstartMenu()
    {
        int choice = 0;
        while (choice!=1 && choice!=2 )
        {
            std::cout<<"1. start new game\n";
            std::cout<<"2. exit\n"; 
            std::cin>>choice;
        }
        if ( choice == 1 )
        {
            this->lvl = 0;
            while (this->lvl < 1 || this->lvl > MAX_LVL)
            {
                std::cout<<"choose level: ";
                std::cin>>this->lvl;
            } 
        }
        return choice;
    }

    bool sudokuboard::is_solved()
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

    void sudokuboard::initialize_files()
    {
            std::string original = "lvls/lvl"+std::to_string(this->lvl)+".suduko";
            std::string progress = "lvls/lvl"+std::to_string(this->lvl)+"_progress.suduko";
            bool file_exists = std::filesystem::exists(progress);
            if (file_exists)
            {
                std::ifstream progressfile(progress);
                std::ifstream originalfile(original);
                if (originalfile.is_open() && progressfile.is_open()) 
                    setboard_from_progressfile(originalfile,progressfile);
            }
            else
            {
                std::ifstream originalfile(original);
                if (originalfile.is_open())
                    setboard_from_originalfile(originalfile);
            }
    }
    
    void sudokuboard::make_amove()
    {
        print_board();
        std::cout<<"enter row , col , value\n";
        int row ,col, val;
        std::cin>>row>>col>>val;
        while(!modify_board(col,row,val))
        {
            std::cout<<"invalid! enter row , col , value\n";
            std::cin>>row>>col>>val;
        }

    }   
    
    int sudokuboard::showloopMenu()
    {
        
        int choice = 0;
        std::cout<<"1. make a move\n";
        std::cout<<"2. solve completely\n"; 
        //std::cout<<"3. get a hint \n";
        std::cout<<"4. reset board\n"; 
        std::cout<<"5. save & exit\n"; 
        std::cin>>choice;

        while (choice >5 || choice < 1)
        {
            std::cout<<"invalid choice! enter again\n";
            std::cout<<"1. make a move\n";
            std::cout<<"2. solve completely\n"; 
            //std::cout<<"3. get a hint \n"; 
            std::cout<<"4. reset board\n"; 
            std::cout<<"5. save & exit\n";
            std::cin>>choice;
        }
        return choice;
    }
    
    void sudokuboard::game_loop(int choice)
    {
        if (choice == 1)
        {
            if (movesallowed < 0)
            {
                if (is_solved())
                {
                    std::cout<<"Hurray! you have solved the board\n";
                    solved = true;
                    return;
                }
                
            }
            else
            {
                std::cout<<"board is full and not solved , reset or keep trying\n";
            }
            make_amove();
        }

        else if (choice == 2)
        {
            //solve the board
            suduko_solver solver(this->grid,boardsize);
            solver.solve_backtracking();
            this->grid = solver.get_board();
            print_board();
        }
        else if (choice == 3)
        {
            //get a hint
        }
        else if (choice == 4)
        {
            std::ifstream originalfile("lvls/lvl"+std::to_string(this->lvl)+".suduko");
            std::ofstream progressfile("lvls/lvl"+std::to_string(this->lvl)+"_progress.suduko");
            reset_board(originalfile,progressfile);
        }
        
        
    }
    void sudokuboard::start()
    {
        int start_choice = showstartMenu();
        while (start_choice != EXIT)
        { 
            initialize_files();

            int loop_choice = showloopMenu();
            while (loop_choice != EXIT_LOOP && !solved)
            {
                game_loop(loop_choice);
                loop_choice = showloopMenu();
            } 
            //save progress to file before exiting
            std::ofstream progressfile("lvls/lvl"+std::to_string(this->lvl)+"_progress.suduko");
            save_progress_to_file(progressfile);
            start_choice = showstartMenu();
        }
        
        
    }
        
}       
        
 



