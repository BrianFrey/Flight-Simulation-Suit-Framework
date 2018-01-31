//Stimulations.cpp
#include "Stimulations.h"
namespace ARAIG
{
    Stim::Stim(std::string n, int l, float i, float f, float d) :
         name(n), location(l), intensity(i), frequency(f), duration(d) {};

    void Stim::display(std::ostream& os)
    {
        os << name << std::endl;
        os << "     Type = stim" << std::endl;
        if (location == ABS)
            os << "     Location = abs" << std::endl;
        else if (location == FRONT)
            os << "     Location = front" << std::endl;
        else if (location == BACK)
            os << "     Location = back" << std::endl;
        else if (location == TRAPS)
            os << "     Location = traps" << std::endl;
        os << "     Intensity = " << intensity << std::endl;
        os << "     Frequency = " << frequency << std::endl;
        os << "     Duration = " << duration << std::endl;
    }

    std::string Stim::getName()const
    {
        return name;
    }

    Stim* Stim::clone()
    {
        Stim* S = new Stim(name, location, intensity, frequency, duration);
        return S;
    }


    Exoskeleton::Exoskeleton(std::string n, float i, float d) :
         name(n), intensity(i), duration(d){};

    void Exoskeleton::display(std::ostream& os)
    {
        os << name << std::endl;
        os << "     Type = exoskeleton" << std::endl;
        os << "     Intensity = " << intensity << std::endl;
        os << "     Duration = " << duration << std::endl;
    }

    std::string Exoskeleton::getName()const
    {
        return name;
    }

    Exoskeleton* Exoskeleton::clone()
    {
        Exoskeleton* E = new Exoskeleton(name, intensity, duration);
        return E;
    }

}
