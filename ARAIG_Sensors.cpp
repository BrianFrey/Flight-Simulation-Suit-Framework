//ARAIG_Sensors.cpp
#include "ARAIG_Sensors.h"

namespace ARAIG
{
    ARAIG_Sensors::ARAIG_Sensors(std::string s, std::string t)
    {
        std::list<Stimulation*> stims;//all stims
        std::list<Stimulation*> TaskStims;//stims to be added to the current task
        std::string line;
        std::string task;
        std::string tempName;
        std::string tempStimName;
        float tempI;
        float tempD;
        int tempL;
        float tempF;

        //read file
        std::ifstream SFile(s);
        if (!SFile)
            throw std::string("*** Failed to open file ") +
            std::string(s) + std::string(" ***");
        while (!SFile.eof())//reads the stimulations text file
        {
            getline(SFile, line);
            if (line[0] == 'e' || line[0] == 'E')
            {//exo
                line = line.substr(12);
                tempName = line.substr(0, line.find_first_of(','));
                line = line.substr(line.find_first_of(',')+1);
                tempI = atof(line.substr(0, line.find_first_of(',')).c_str());
                line = line.substr(line.find_first_of(',')+1);
                tempD = atof(line.c_str());
                Exoskeleton* E = new Exoskeleton(tempName, tempI, tempD);
                stims.push_back(E);
            }
            else if (line[0] == 's' || line[0] == 'S')
            {//stim
                line = line.substr(5);
                tempName = line.substr(0, line.find_first_of(','));
                line = line.substr(line.find_first_of(',')+1);

                if(line.substr(0, line.find_first_of(',')) == "abs")
                   tempL = ABS;
                else if(line.substr(0, line.find_first_of(',')) == "front")
                    tempL = FRONT;
                else if(line.substr(0, line.find_first_of(',')) == "back")
                    tempL = BACK;
                else
                    tempL = TRAPS;
                line = line.substr(line.find_first_of(',')+1);

                tempI = atof(line.substr(0, line.find_first_of(',')).c_str());
                line = line.substr(line.find_first_of(',')+1);

                tempF = atof(line.substr(0, line.find_first_of(',')).c_str());
                line = line.substr(line.find_first_of(',')+1);

                tempD = atof(line.c_str());
                Stim* S = new Stim(tempName, tempL, tempI, tempF, tempD);
                stims.push_back(S);
            }
        }
        //construct tasks
        std::ifstream TFile(t);
        if (!TFile)
            throw std::string("*** Failed to open file ") +
            std::string(t) + std::string(" ***");
        std::stringstream strStream;
        strStream << TFile.rdbuf();
        std::string fileStr = strStream.str();//moves the entire file into a string

        while (fileStr.find_first_of("TASK") != std::string::npos)//do while there are tasks left in the file string
        {
            if (fileStr.find("TASK", 5) != std::string::npos)//if there are tasks left
            {
                task = fileStr.substr(0, fileStr.find("TASK", 5));
                fileStr = fileStr.substr(fileStr.find("TASK", 5));//cuts the current task off of fileString
            }
            else
            {//if the last task
                task = fileStr;
                fileStr = "";
            }

            tempName = task.substr(5, task.find_first_of('\n')-5);
            task = task.substr(task.find_first_of('\n')+1);//cuts name line off task

            while (task.find_first_of('\n') != std::string::npos)//this loop reads in a single task
            {
                tempStimName = task.substr(0, task.find_first_of('\n'));
                task = task.substr(task.find_first_of('\n')+1);//cuts the name line off task

                for (std::list<Stimulation*>::const_iterator it = stims.begin(), end = stims.end(); it != end; ++it)
                {
                    if ((*it)->getName() == tempStimName){
                        TaskStims.push_back((*it)->clone());//finds the stim in the stim list, makes a clone, and adds it to the task list;
                    }
                }
            }
            //construct task
            Task* T = new Task(TaskStims, tempName);
            TaskList.push_back(T);
            //clear taskStims so the next task can use it
            TaskStims.clear();
        }
        std::cout << "ARAIG_Sensors Created" << std::endl;
        while(!stims.empty())//the list of stims is no longer needed
        {
            delete stims.front();
            stims.pop_front();
        }
    }
    void ARAIG_Sensors::dump(std::ostream& os)
    {
        for (std::list<Task*>::const_iterator it = TaskList.begin(), end = TaskList.end(); it != end; ++it)
        {
            (*it)->dump(os);
        }
    }
    Task* ARAIG_Sensors::search_for_task(std::string S)
    {
        for (std::list<Task*>::const_iterator it = TaskList.begin(), end = TaskList.end(); it != end; ++it)
        {
            if ((*it)->getName() == S)
                return *it;

        }
        return nullptr;
    }
    ARAIG_Sensors::~ARAIG_Sensors()
    {
        while(!TaskList.empty())
        {
            delete TaskList.front();
            TaskList.pop_front();
        }
    }
}
