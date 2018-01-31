//Task.h
#ifndef TASK_H_INCLUDED
#define TASK_H_INCLUDED
#include "Stimulations.h"

namespace ARAIG
{
    class Task
    {
    private:
        std::string name;
        std::list<Stimulation*> Stim;
    public:
        Task();
        Task(std::list<Stimulation*>, std::string);

        Task(const Task&);
        Task& operator=(const Task&);
        Task(Task&&);
        Task& operator=(Task&&);
        ~Task();

        Task& operator+=(Task&);
        Stimulation& operator[](unsigned int);
        std::string getName() const;
        void removeStim(std::string);
        void dump(std::ostream&);
        void execute(std::ostream&);
    };
}
#endif
