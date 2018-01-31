//Task.cpp
#include "Task.h"
namespace ARAIG
{
    Task::Task(std::list<Stimulation*> S, std::string N)
    {
        Stim = S;
        name = N;
    }

    Task::Task(const Task& T)
    {
        Stim = T.Stim;
    }
    Task& Task::operator=(const Task& T)
    {
        Stim = T.Stim;
        return *this;
    }
    Task::Task(Task&& T)
    {
        Stim = T.Stim;
        while(!T.Stim.empty())
        {
            delete T.Stim.front();
            T.Stim.pop_front();
        }
    }
    Task& Task::operator=(Task&& T)
    {
        Stim = T.Stim;
        while(!T.Stim.empty())
        {
            delete T.Stim.front();
            T.Stim.pop_front();
        }
        return *this;
    }
    Task::~Task()
    {
        while(!Stim.empty())
        {
            delete Stim.front();
            Stim.pop_front();
        }
    }

    Task& Task::operator+=(Task& T)
    {
        Stim.insert(Stim.end(), T.Stim.begin(), T.Stim.begin());
        return *this;
    }
    Stimulation& Task::operator[](unsigned int i)
    {
        if (Stim.size() > i)
        {
            std::list<Stimulation*>::iterator it = Stim.begin();
            std::advance(it, i);
            return **it;
        }
        else
        {
            throw "Stim not in array Size";
        }
    }
    std::string Task::getName() const
    {
        return name;
    }
    void Task::removeStim(std::string S)
    {
        for (std::list<Stimulation*>::iterator it = Stim.begin(), end = Stim.end(); it != end;)
        {
            if ((*it)->getName() == S)//removes all Stimulations with name S from list
            {
                (*it)->~Stimulation();
                it = Stim.erase(it);
            }
            else
                ++it;

        }
    }
    void Task::dump(std::ostream& os)
    {
        os << "TASK " << name << std::endl;
        for (std::list<Stimulation*>::const_iterator it = Stim.begin(), end = Stim.end(); it != end; ++it)
        {
            os << (*it)->getName() << std::endl;
        }
    }
    void Task::execute(std::ostream& os)
    {
        os << name << std::endl;
        for (std::list<Stimulation*>::const_iterator it = Stim.begin(), end = Stim.end(); it != end; ++it)
        {
            (*it)->display(os);
        }
    }
}
