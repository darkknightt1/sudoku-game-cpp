#include "sudoko.hpp"

int main()
{
    sudukogame::suduko s1(9);
    std::ifstream sudukofilee("suduko.suduko");
    if (!sudukofilee.is_open())
    {
        //throw error
        #if DEBUG
        std::cout<<"cant open file\n";
        #endif
    }
    else s1.setboardfromfile(sudukofilee);
    
    return 0;
}

