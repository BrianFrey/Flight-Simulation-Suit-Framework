//Profile.h
#ifndef PROFILE_H_INCLUDED
#define PROFILE_H_INCLUDED
#include "Task.h"
#include "Stimulations.h"
#include "ARAIG_Sensors.h"


namespace ARAIG
{
    class Profile
    {
        std::string Stud_F_Name;
        std::string Stud_L_Name;
        int stud_Num;
        std::string Inst_F_Name;
        std::string Inst_L_Name;
        int Inst_Num;
        std::vector<Task*> ToRun;
        std::vector<Task*> Completed;
        struct MinMax
        {
            int Min;
            int Max;
        };
        MinMax MM;
    public:
        Profile(std::string, std::ostream&, ARAIG_Sensors&);
        void displayToRun(std::ostream&);
        void displayCompleted(std::ostream&);
        void displayNext(std::ostream&);
        void displayLast(std::ostream&);
        void run(std::ostream&);
    };
}
#endif
