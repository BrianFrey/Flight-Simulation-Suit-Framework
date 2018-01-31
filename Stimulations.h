//Stimulations.h
#ifndef STIMULATIONS_H_INCLUDED
#define STIMULATIONS_H_INCLUDED
#include <string>
#include <sstream>
#include <list>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <typeinfo>

namespace ARAIG
{
    class Stimulation
    {
        std::string name;
    public:
        virtual void display(std::ostream&) = 0;
        virtual std::string getName()const = 0;
        virtual Stimulation* clone() = 0;
    };

    enum loc {ABS = 0, FRONT = 1, BACK = 2, TRAPS = 3};

    class Stim : public Stimulation
    {
        std::string name;
        int location;
        float intensity;
        float frequency;
        float duration;
    public:
        Stim();
        Stim(std::string n, int l, float i, float f, float d);
        Stim* clone();
        std::string getName()const;
        void display(std::ostream&);
    };

    class Exoskeleton : public Stimulation
    {
        std::string name;
        float intensity;
        float duration;
    public:
        Exoskeleton();
        Exoskeleton(std::string n, float i, float d);
        Exoskeleton* clone();
        std::string getName()const;
        void display(std::ostream&);
    };
}
#endif
