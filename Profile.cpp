//Profile.cpp
#include "Profile.h"
namespace ARAIG
{
    Profile::Profile(std::string fileName, std::ostream& os, ARAIG_Sensors& A)
    {
        std::string line;
        std::ifstream SFile(fileName);
        if (!SFile)
            throw std::string("*** Failed to open file ") +
            std::string(fileName) + std::string(" ***");

        SFile >> line;
        Stud_F_Name = line.substr(0, line.find_first_of(','));
        line = line.substr(line.find_first_of(',')+1);
        Stud_L_Name = line.substr(0, line.find_first_of(','));
        stud_Num = atoi(line.substr(line.find_first_of(',')+1).c_str());

        SFile >> line;
        Inst_F_Name = line.substr(0, line.find_first_of(','));
        line = line.substr(line.find_first_of(',')+1);
        Inst_L_Name = line.substr(0, line.find_first_of(','));
        Inst_Num = atoi(line.substr(line.find_first_of(',')+1).c_str());

        SFile >> line;
        MM.Max = atof(line.substr(0, line.find_first_of(',')).c_str());
        MM.Min = atof(line.substr(line.find_first_of(',')+1).c_str());

        while (SFile.good())//reads each task
        {
            SFile >> line;
            if (A.search_for_task(line) != nullptr)
                ToRun.push_back(A.search_for_task(line));//finds the stim in the stim list and adds it to ToRun
        }
    }
    void Profile::displayToRun(std::ostream& os)
    {
        for (std::vector<Task*>::const_iterator it = ToRun.begin(), end = ToRun.end(); it != end; ++it)
        {
            os << (*it)->getName() << std::endl;
        }
    }
    void Profile::displayCompleted(std::ostream& os)
    {
        for (std::vector<Task*>::const_iterator it = Completed.begin(), end = Completed.end(); it != end; ++it)
        {
            os << (*it)->getName() << std::endl;
        }
    }
    void Profile::displayNext(std::ostream& os)
    {
        os << ToRun.front()->getName() << std::endl;
    }
    void Profile::displayLast(std::ostream& os)
    {
        os << Completed.back()->getName() << std::endl;
    }
    void Profile::run(std::ostream& os)
    {
        os << "Student:     " << Stud_F_Name << " " << Stud_L_Name << " - " << stud_Num << std::endl;
        os << "Instructor:  " << Inst_F_Name << " " << Inst_L_Name << " - " << Inst_Num << std::endl;
        os << "Student Calibration:" << std::endl;
        os << "MAX = " << MM.Max << std::endl;
        os << "MIN = " << MM.Min << std::endl;
        while(!ToRun.empty())
        {
            ToRun.front()->execute(os);
            Completed.push_back(ToRun.front());
            ToRun.erase(ToRun.begin());
        }
    }
}
