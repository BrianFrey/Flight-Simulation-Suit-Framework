//tm.cpp
#include "Stimulations.h"
#include "Task.h"
#include "ARAIG_Sensors.h"
#include "Profile.h"


int main(int argc, char* argv[])
{
    if (argc != 5)
    {
        std::cerr << "Wrong number of arguments";
        return 1;
    }
    try{
        ARAIG::ARAIG_Sensors sensors(argv[2], argv[3]);
        std::ofstream O(argv[4]);
        ARAIG::Profile P(argv[1], std::cout, sensors);
        P.run(O);
        O.close();
        std::cout << "Press any key to continue ... ";
        std::cin.get();
    }catch (std::string S)
    {
        std::cout << S;
    }
}
