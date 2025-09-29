#include "valide_datum.h"

bool valide_datum(const std::string& datum)
{
    if (datum.size() != 10 || datum[2] != '-' || datum[5] != '-')
        return false;
    for (size_t datum_index = 0; datum_index < datum.size(); ++datum_index)
    {
        if (datum_index == 2 || datum_index == 5)
            continue;
        char c = datum[datum_index];
        if (c < '0' || c > '9')
            return false;
    }
    int dag = (datum[0] - '0') * 10 + (datum[1] - '0');
    int maand = (datum[3] - '0') * 10 + (datum[4] - '0');
    int jaar = (datum[6] - '0') * 1000 + (datum[7] - '0') * 100 + (datum[8] - '0') * 10 + (datum[9] - '0');
    if (jaar < 1900 || jaar > 2100)
        return false;
    if (maand < 1 || maand > 12)
        return false;
    int dagen_per_maand[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    int dagen = dagen_per_maand[maand - 1];
    if (maand == 2)
    {
        bool leap = (jaar % 4 == 0 && (jaar % 100 != 0 || jaar % 400 == 0));
        if (leap)
            dagen = 29;
    }
    if (dag < 1 || dag > dagen)
        return false;
    return true;
}

