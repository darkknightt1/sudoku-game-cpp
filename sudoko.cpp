#include "sudoko.hpp"



namespace sudukogame
{

    void suduko::setboardfromfile(std::ifstream &sudukoboardfile)
    {
        #if DEBUG
            std::cout<<"DEBUG , setboardfromfile";
        #endif
        
        std::string line;
        int row = 0;
        while ( getline(sudukoboardfile,line) )
        {
            
            
        }
    }


}

