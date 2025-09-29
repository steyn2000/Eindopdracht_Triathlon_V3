#include "categorie_van_leeftijd.h"

std::string categorie_van_leeftijd(int leeftijd)
{
    if (leeftijd < 13)
        return "<13";
    else if (leeftijd < 18)
        return "13-17";
    else if (leeftijd <= 35)
        return "18-35";
    else if (leeftijd <= 45)
        return "36-45";
    else if (leeftijd <= 55)
        return "46-55";
    else if (leeftijd <= 65)
        return "56-65";
    else
        return "66+";
}
