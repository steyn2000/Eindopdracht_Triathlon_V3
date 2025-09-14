#include "Wedstrijd.h"
#include <algorithm>

/**
 * @file Wedstrijd.cpp
 * @brief Implementatie van de Wedstrijd klasse.
 */

using namespace std;

Wedstrijd::Wedstrijd(string wedstrijd_naam, string wedstrijd_datum, bool is_nederlands_kampioenschap, bool heeft_wissels)
    : naam(wedstrijd_naam),
      datum(wedstrijd_datum),
      is_nederlands_kampioenschap(is_nederlands_kampioenschap),
      met_wissels(heeft_wissels) {}

void Wedstrijd::voeg_deelnemer_toe(const Deelnemer& nieuwe_deelnemer)
{
    auto bestaat = find_if(deelnemers.begin(), deelnemers.end(),
        [&](const Deelnemer& bestaande) { return bestaande.get_index_atleet() == nieuwe_deelnemer.get_index_atleet(); });
    if (bestaat == deelnemers.end())
    {
        deelnemers.push_back(nieuwe_deelnemer);
    }
}

int Wedstrijd::aantal_deelnemers() const
{
    return static_cast<int>(deelnemers.size());
}

const vector<Deelnemer>& Wedstrijd::get_deelnemers() const
{
    return deelnemers;
}

vector<Deelnemer> Wedstrijd::deelnemer_lijst_gesorteerd() const
{
    vector<Deelnemer> gesorteerde_deelnemers = deelnemers; // kopie om het origineel niet te wijzigen
    sort(gesorteerde_deelnemers.begin(), gesorteerde_deelnemers.end(),
        [](const Deelnemer& eerste, const Deelnemer& tweede)
        {
            return eerste.totale_tijd() < tweede.totale_tijd();
        });
    return gesorteerde_deelnemers;
}

//getters
string Wedstrijd::get_naam() const
{
    return naam;
}

string Wedstrijd::get_datum() const
{
    return datum;
}

bool Wedstrijd::get_met_wissels() const
{
    return met_wissels;
}

bool Wedstrijd::get_is_nederlands_kampioenschap() const
{
    return is_nederlands_kampioenschap;
}
