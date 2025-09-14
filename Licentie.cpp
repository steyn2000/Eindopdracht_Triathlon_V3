#include "Licentie.h"

using namespace std;

Licentie::Licentie() : licentie_nummer(0), geldig_tot(""), type(""), vereniging(""), doping_controles({}) {}

Licentie::Licentie(int nummer, const string& geldig_tot, const string& type, const string& vereniging)
    : licentie_nummer(nummer), geldig_tot(geldig_tot), type(type), vereniging(vereniging), doping_controles({}) {}

int Licentie::get_nummer() const
{
    return licentie_nummer;
}

string Licentie::get_geldig_tot() const
{
    return geldig_tot;
}

string Licentie::get_type() const
{
    return type;
}

string Licentie::get_vereniging() const
{
    return vereniging;
}

const vector<DopingControle>& Licentie::get_doping_controles() const
{
    return doping_controles;
}

bool Licentie::is_dopingvrij() const
{
    for (const auto& controle : doping_controles)
    {
        if (controle.doping_geconstateerd)
        {
            return false;
        }
    }
    return true;
}

// Controleer of licentie geldig is op gegeven datum ("dd-mm-jjjj")
bool Licentie::is_geldig_op(const string& datum) const
{
    if (geldig_tot.size() != 10 || datum.size() != 10)
        return false; // ongeldige datumformaten

    auto datum_naar_int = [](const string& d) {
        int jaar = (d[6]-'0') * 1000 + (d[7]-'0') * 100 +
                   (d[8]-'0') * 10 + (d[9]-'0');
        int maand = (d[3]-'0') * 10 + (d[4]-'0');
        int dag = (d[0]-'0') * 10 + (d[1]-'0');
        return jaar * 10000 + maand * 100 + dag;
    };

    int datum_als_int = datum_naar_int(datum);
    int geldig_tot_als_int = datum_naar_int(geldig_tot);
    return datum_als_int <= geldig_tot_als_int;
}

void Licentie::set_nummer(int nummer)
{
    licentie_nummer = nummer;
}

void Licentie::set_geldig_tot(const string& geldig_tot)
{
    this->geldig_tot = geldig_tot;
}

void Licentie::set_type(const string& nieuw_type)
{
    type = nieuw_type;
}

void Licentie::set_vereniging(const string& vereniging)
{
    this->vereniging = vereniging;
}

void Licentie::voeg_dopingcontrole_toe(const DopingControle& controle)
{
    doping_controles.push_back(controle);
}
