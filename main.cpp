#include "sudoko.hpp"

int main()
{
    std::cout<<"why";
    sudukogame::suduko s1;
    std::ifstream sudukofilee("suduko.suduko");
    if (!sudukofilee.is_open())
    {
        std::cout<<"cant open";
    }
    else
    {
        s1.setboardfromfile(sudukofilee);
    }
    
    return 0;
}