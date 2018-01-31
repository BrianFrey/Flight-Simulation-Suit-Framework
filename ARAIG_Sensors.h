//ARAIG_Sensors.h
#ifndef ARAIG_H_INCLUDED
#define ARAIG_H_INCLUDED
#include "Task.h"
#include "Stimulations.h"


namespace ARAIG
{
    class ARAIG_Sensors
    {
    private:
        std::list<Task*> TaskList;
    public:
        ARAIG_Sensors(std::string, std::string);
        void dump(std::ostream&);
        Task* search_for_task(std::string);
        ~ARAIG_Sensors();
    };
}
#endif
