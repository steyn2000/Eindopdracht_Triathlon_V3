#include "leeftijd_op_datum.h"

static int get_dag(const std::string& datum)
{
    return (datum[0] - '0') * 10 + (datum[1] - '0');
}

static int get_maand(const std::string& datum)
{
    return (datum[3] - '0') * 10 + (datum[4] - '0');
}

static int get_jaar(const std::string& datum)
{
    return (datum[6] - '0') * 1000 + (datum[7] - '0') * 100 + (datum[8] - '0') * 10 + (datum[9] - '0');
}

int leeftijd_op_datum(const std::string& geboortedatum, const std::string& datum)
{
    int geboortedatum_dag = get_dag(geboortedatum), geboortedatum_maand = get_maand(geboortedatum), geboortedatum_jaar = get_jaar(geboortedatum);
    int datum_dag = get_dag(datum), datum_maand = get_maand(datum), datum_jaar = get_jaar(datum);
    int leeftijd = datum_jaar - geboortedatum_jaar;
    if (datum_maand < geboortedatum_maand || (datum_maand == geboortedatum_maand && datum_dag < geboortedatum_dag)) leeftijd -= 1; // verjaardag nog niet geweest
    return leeftijd;
}