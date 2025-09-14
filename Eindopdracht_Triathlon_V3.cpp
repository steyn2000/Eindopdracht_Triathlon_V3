/**
 * @file Eindopdracht_Triathlon_V3.cpp
 * @brief Hoofdbestand met de main-functie van het programma.
 */

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include <map>
#include <fstream>
#include "Atleet.h"
#include "Deelnemer.h"
#include "Wedstrijd.h"
#include "Licentie.h"

using namespace std;

vector<Atleet> atleten;
vector<Wedstrijd> wedstrijden;

const string DATA_BESTAND = "triathlon_data.txt";

void save_data()
{
    ofstream bestand(DATA_BESTAND);
    if (!bestand) return;

    bestand << atleten.size() << '\n';
    for (const auto& atleet : atleten)
    {
        const Licentie& licentie = atleet.get_licentie();
        bestand << atleet.get_voornaam() << '\n'
            << atleet.get_achternaam() << '\n'
            << atleet.get_geboortedatum() << '\n'
            << atleet.get_geslacht() << '\n'
            << licentie.get_nummer() << '\n'
            << licentie.get_geldig_tot() << '\n'
            << licentie.get_type() << '\n'
            << licentie.get_vereniging() << '\n';

        const auto& doping_controles = licentie.get_doping_controles();
        bestand << doping_controles.size() << '\n';
        for (const auto& controle : doping_controles)
        {
            bestand << controle.datum << '\n' << controle.doping_geconstateerd << '\n';
        }
    }

    bestand << wedstrijden.size() << '\n';
    for (const auto& wedstrijd : wedstrijden)
    {
        bestand << wedstrijd.get_naam() << '\n'
            << wedstrijd.get_datum() << '\n'
            << wedstrijd.get_is_nederlands_kampioenschap() << '\n'
            << wedstrijd.get_met_wissels() << '\n';

        const auto& deelnemers = wedstrijd.get_deelnemers();
        bestand << deelnemers.size() << '\n';
        for (const auto& deelnemer : deelnemers)
        {
            bestand << deelnemer.get_index_atleet() << ' '
                << deelnemer.get_tijd_zwem() << ' '
                << deelnemer.get_tijd_fiets() << ' '
                << deelnemer.get_tijd_loop() << ' '
                << deelnemer.get_heeft_wissel1() << ' '
                << deelnemer.get_wisseltijd1() << ' '
                << deelnemer.get_heeft_wissel2() << ' '
                << deelnemer.get_wisseltijd2() << '\n';
        }
    }
}

void load_data()
{
    ifstream in(DATA_BESTAND);
    if (!in) return;

    size_t aantal_atleten;
    if (!(in >> aantal_atleten)) return;
    in.ignore(numeric_limits<streamsize>::max(), '\n');
    for (size_t atleet_index = 0; atleet_index < aantal_atleten; ++atleet_index)
    {
        string voornaam, achternaam, geboortedatum;
        getline(in, voornaam);
        getline(in, achternaam);
        getline(in, geboortedatum);
        char geslacht;
        in >> geslacht;
        in.ignore(numeric_limits<streamsize>::max(), '\n');

        int licentienummer;
        string licentie_geldig_tot, licentie_type, vereniging;
        in >> licentienummer;
        in.ignore();
        getline(in, licentie_geldig_tot);
        getline(in, licentie_type);
        getline(in, vereniging);

        size_t aantal_dopingcontroles;
        in >> aantal_dopingcontroles;
        in.ignore(numeric_limits<streamsize>::max(), '\n');
        Licentie licentie(licentienummer, licentie_geldig_tot, licentie_type, vereniging);
        for (size_t controle_index = 0; controle_index < aantal_dopingcontroles; ++controle_index)
        {
            string controle_datum;
            getline(in, controle_datum);
            int doping_geconstateerd_int;
            in >> doping_geconstateerd_int;
            in.ignore(numeric_limits<streamsize>::max(), '\n');
            licentie.voeg_dopingcontrole_toe({ controle_datum, doping_geconstateerd_int != 0 });
        }

        Atleet nieuwe_atleet(voornaam, achternaam, geboortedatum, geslacht);
        nieuwe_atleet.set_licentie(licentie);
        atleten.push_back(nieuwe_atleet);
    }

    size_t aantal_wedstrijden;
    in >> aantal_wedstrijden;
    in.ignore(numeric_limits<streamsize>::max(), '\n');
    for (size_t wedstrijd_index = 0; wedstrijd_index < aantal_wedstrijden; ++wedstrijd_index)
    {
        string naam, datum;
        getline(in, naam);
        getline(in, datum);
        int is_nederlands_kampioenschap_int, met_wissels_int;
        in >> is_nederlands_kampioenschap_int >> met_wissels_int;
        in.ignore(numeric_limits<streamsize>::max(), '\n');

        Wedstrijd wedstrijd(naam, datum, is_nederlands_kampioenschap_int != 0, met_wissels_int != 0);

        size_t aantal_deelnemers;
        in >> aantal_deelnemers;
        in.ignore(numeric_limits<streamsize>::max(), '\n');
        for (size_t deelnemer_index = 0; deelnemer_index < aantal_deelnemers; ++deelnemer_index)
        {
            int index_atleet;
            int tijd_zwem, tijd_fiets, tijd_loop, heeft_wissel1, tijd_wissel1, heeft_wissel2, tijd_wissel2;
            in >> index_atleet >> tijd_zwem >> tijd_fiets >> tijd_loop >> heeft_wissel1 >> tijd_wissel1 >> heeft_wissel2 >> tijd_wissel2;
            in.ignore(numeric_limits<streamsize>::max(), '\n');

            Deelnemer deelnemer(index_atleet, tijd_zwem, tijd_fiets, tijd_loop);
            if (heeft_wissel1) deelnemer.set_wisseltijd1(tijd_wissel1);
            if (heeft_wissel2) deelnemer.set_wisseltijd2(tijd_wissel2);
            wedstrijd.voeg_deelnemer_toe(deelnemer);
        }

        wedstrijden.push_back(wedstrijd);
    }
}

void print_welkom()
{
    cout << "~~ Welkom bij het Triathlon organisatiesysteem! ~~\n";
}

void print_keuzemenu()
{
    cout << "\nMaak een keuze:\n";
    cout << "1. Wedstrijd aanmaken\n";
    cout << "2. Toon alle wedstrijden\n";
    cout << "3. Atleet aanmaken\n";
    cout << "4. Toon alle atleten\n";
    cout << "5. Deelnemer (atleet) inschrijven bij wedstrijd\n";
    cout << "6. Aantal deelnemers tonen\n";
    cout << "7. Licentie aan atleet koppelen\n";
    cout << "8. Dopingcontrole toevoegen\n";
    cout << "9. Uitslagen tonen\n";
    cout << "10. Stoppen\n"; // De terminal bleef zwart, menu niet zichtbaar terwijl de code wel leek te werken
}

bool valide_datum(const string& datum)
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

// datum helpers voor "dd-mm-jjjj"
static int get_dag(const string& datum)
{
    return (datum[0] - '0') * 10 + (datum[1] - '0');
}
static int get_maand(const string& datum)
{
    return (datum[3] - '0') * 10 + (datum[4] - '0');
}
static int get_jaar(const string& datum)
{
    return (datum[6] - '0') * 1000 + (datum[7] - '0') * 100 + (datum[8] - '0') * 10 + (datum[9] - '0');
}

int leeftijd_op_datum(const string& geboortedatum, const string& datum)
{
    int geboortedatum_dag = get_dag(geboortedatum), geboortedatum_maand = get_maand(geboortedatum), geboortedatum_jaar = get_jaar(geboortedatum);
    int datum_dag = get_dag(datum), datum_maand = get_maand(datum), datum_jaar = get_jaar(datum);
    int leeftijd = datum_jaar - geboortedatum_jaar;
    if (datum_maand < geboortedatum_maand || (datum_maand == geboortedatum_maand && datum_dag < geboortedatum_dag)) leeftijd -= 1; // verjaardag nog niet geweest
    return leeftijd;
}

// categorieën volgens jouw eisen
string categorie_van_leeftijd(int leeftijd)
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

string categorie_van(const Atleet& atleet, const string& wedstrijddatum)
{
    return categorie_van_leeftijd(leeftijd_op_datum(atleet.get_geboortedatum(), wedstrijddatum));
}

int lees_int(const string& prompt)
{
    while (true)
    {
        string input;
        cout << prompt;
        if (!(cin >> input))
        {
            cout << "Ongeldige invoer. Voer een niet-negatief getal in.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        bool ok = !input.empty();
        int value = 0;
        for (char c : input)
        {
            if (c < '0' || c > '9')
            {
                ok = false;
                break;
            }

            int digit = c - '0';
            if (value > (numeric_limits<int>::max() - digit) / 10)
            {
                ok = false;
                break;
            }
            value = value * 10 + digit;
        }

        if (ok)
        {
            return value;
        }

        cout << "Ongeldige invoer. Voer een niet-negatief getal in.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int kies_index(int max_index, const string& prompt)
{
    int index = lees_int(prompt);

    if (index < 0 || index >= max_index)
    {
        return -1;
    }
    return index;
}

string lees_tekst(const string& prompt)
{
    string input;
    while (true)
    {
        cout << prompt;
        cin.clear();
        if (getline(cin >> ws, input))
            return input;
        cout << "Ongeldige invoer. Probeer opnieuw.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void lijst_atleten(const vector<Atleet>& lijst_atleten)
{
    if (lijst_atleten.empty())
    {
        cout << "Geen atleten.\n";
        return;
    }

    for (size_t atleet_index = 0; atleet_index < lijst_atleten.size(); ++atleet_index)
    {
        const Licentie& licentie = lijst_atleten[atleet_index].get_licentie();
        cout << "[" << atleet_index << "] "
            << lijst_atleten[atleet_index].get_voornaam() << " " << lijst_atleten[atleet_index].get_achternaam() << " | Geb.datum: " << lijst_atleten[atleet_index].get_geboortedatum() << " | Geslacht: "
            << lijst_atleten[atleet_index].get_geslacht() << " | Licentie: " << licentie.get_type() << " (" << licentie.get_nummer() << ")\n";
    }
}

void lijst_wedstrijden(const vector<Wedstrijd>& lijst_wedstrijden)
{
    if (lijst_wedstrijden.empty())
    {
        cout << "Geen wedstrijden.\n";
        return;
    }

    for (size_t wedstrijd_index = 0; wedstrijd_index < lijst_wedstrijden.size(); ++wedstrijd_index)
    {
        cout << "[" << wedstrijd_index << "] " << lijst_wedstrijden[wedstrijd_index].get_naam() << " (" << lijst_wedstrijden[wedstrijd_index].get_datum() << ")\n";
    }
}

Atleet invoer_atleet()
{
    string voornaam = lees_tekst("Voornaam: ");
    string achternaam = lees_tekst("Achternaam: ");
    string geboortedatum;
    do {
        geboortedatum = lees_tekst("Geboortedatum (dd-mm-jjjj): ");
        if (!valide_datum(geboortedatum))
            cout << "Ongeldige datum. Probeer opnieuw.\n";
    } while (!valide_datum(geboortedatum));
    char geslacht = lees_tekst("Geslacht (M/V): ")[0];

    return Atleet(voornaam, achternaam, geboortedatum, geslacht);
}
// functie voor het formatteren van de tijd
string format_tijd(int seconden)
{
    int uren = seconden / 3600;
    int minuten = (seconden % 3600) / 60;
    int resterende_seconden = seconden % 60;
    return to_string(uren) + "u " + to_string(minuten) + "m " + to_string(resterende_seconden) + "s";
}

// Functie voor het tonen van de uitslagen
void toon_uitslag_van_wedstrijd(const vector<Wedstrijd>& wedstrijden)
{
    if (wedstrijden.empty())
    {
        cout << "Geen wedstrijden.\n";
        return;
    }

    lijst_wedstrijden(wedstrijden);
    int wedstrijd_index = kies_index((int)wedstrijden.size(), "Kies wedstrijd-index: ");
    if (wedstrijd_index == -1)
    {
        cout << "Ongeldige keuze.\n";
        return;
    }

    const Wedstrijd& wedstrijd = wedstrijden[wedstrijd_index];
    auto uitslag = wedstrijd.deelnemer_lijst_gesorteerd(); // gesorteerd op totale tijd

    // deelnemers met een Trainingslicentie worden niet opgenomen in de uitslag
    uitslag.erase(remove_if(uitslag.begin(), uitslag.end(),
        [](const Deelnemer& d)
        {
            return d.get_atleet().get_licentie().get_type() == "Trainingslicentie";
        }), uitslag.end());

    // deelnemers met verlopen licentie worden niet opgenomen in de uitslag
    uitslag.erase(remove_if(uitslag.begin(), uitslag.end(),
        [&](const Deelnemer& d)
        {
            return !d.get_atleet().get_licentie().is_geldig_op(wedstrijd.get_datum());
        }), uitslag.end());

    // dopingpositieve atleten worden niet opgenomen in de uitslag
    uitslag.erase(remove_if(uitslag.begin(), uitslag.end(),
        [](const Deelnemer& d)
        {
            return !d.get_atleet().get_licentie().is_dopingvrij();
        }), uitslag.end());

    if (uitslag.empty())
    {
        cout << "Geen deelnemers voor deze wedstrijd.\n";
        return;
    }

    bool met_wissels = wedstrijd.get_met_wissels();

    // --------- TOTAAL ---------
    cout << "\nUitslag: " << wedstrijd.get_naam() << " (" << wedstrijd.get_datum() << ")\n";
    cout << "Pos  Naam                     Zwem       ";

    if (met_wissels)
        cout << "T1         ";
    cout << "Fiets      ";

    if (met_wissels)
        cout << "T2         ";
    cout << "Loop       Totaal\n";
    cout << "---- -----------------------  ----------  ";

    if (met_wissels)
        cout << "----------  ";
    cout << "----------  ";

    if (met_wissels)
        cout << "----------  ";
    cout << "----------  ----------\n";

    for (size_t deelnemer_index = 0; deelnemer_index < uitslag.size(); ++deelnemer_index)
    {
        const Deelnemer& deelnemer = uitslag[deelnemer_index];
        const Atleet& atleet = deelnemer.get_atleet();
        string naam = atleet.get_voornaam() + " " + atleet.get_achternaam();

        if (naam.size() > 23) naam = naam.substr(0, 23);
        cout << (deelnemer_index + 1);

        if (deelnemer_index + 1 < 10)
            cout << "   ";

        else
            cout << "  ";
        cout << naam;

        if (naam.size() < 23)
            cout << string(23 - naam.size(), ' ');
        cout << "    " << format_tijd(deelnemer.get_tijd_zwem());

        if (met_wissels)
            cout << "    " << format_tijd(deelnemer.get_wisseltijd1());
        cout << "    " << format_tijd(deelnemer.get_tijd_fiets());

        if (met_wissels)
            cout << "    " << format_tijd(deelnemer.get_wisseltijd2());
        cout << "    " << format_tijd(deelnemer.get_tijd_loop());
        cout << "    " << format_tijd(deelnemer.totale_tijd()) << "\n";
    }

    // --------- PER CATEGORIE ---------
    // groepeert deelnemers per categorie
    map<string, vector<Deelnemer>> groepen;
    for (const auto& deelnemer : uitslag)
    {
        const Atleet& atleet = deelnemer.get_atleet();
        string categorie = categorie_van(atleet, wedstrijd.get_datum());
        groepen[categorie].push_back(deelnemer);
    }

    vector<string> categorie_volgorde = { "<13","13-17","18-35","36-45","46-55","56-65","66+" };

    for (const auto& categorie : categorie_volgorde)
    {
        auto it = groepen.find(categorie);
        if (it == groepen.end() || it->second.empty()) continue;

        auto& categorie_deelnemers = it->second; // al gesorteerd door kopie uit 'uitslag', maar safe nog eens:
        sort(categorie_deelnemers.begin(), categorie_deelnemers.end(),
            [](const Deelnemer& e1, const Deelnemer& e2) { return e1.totale_tijd() < e2.totale_tijd(); });

        cout << "\n[" << categorie << "]\n";
        cout << "Pos  Naam                             Zwem       ";

        if (met_wissels)
            cout << "T1         ";
        cout << "Fiets      ";

        if (met_wissels)
            cout << "T2         ";
        cout << "Loop       Totaal\n";
        cout << "---- --------------------------------  ---------  ";

        if (met_wissels)
            cout << "---------  ";
        cout << "---------  ";

        if (met_wissels)
            cout << "---------  ";
        cout << "---------  ---------\n";

        for (size_t deelnemer_index = 0; deelnemer_index < categorie_deelnemers.size(); ++deelnemer_index) {
            const Deelnemer& deelnemer = categorie_deelnemers[deelnemer_index];
            const Atleet& atleet = deelnemer.get_atleet();
            string naam = atleet.get_voornaam() + " " + atleet.get_achternaam();
            if (naam.size() > 32) naam = naam.substr(0, 32);
            cout << (deelnemer_index + 1);

            if (deelnemer_index + 1 < 10)
                cout << "   ";
            else
                cout << "  ";
            cout << naam;

            if (naam.size() < 32) cout << string(32 - naam.size(), ' ');
            cout << "  " << format_tijd(deelnemer.get_tijd_zwem());

            if (met_wissels)
                cout << "   " << format_tijd(deelnemer.get_wisseltijd1());
            cout << "   " << format_tijd(deelnemer.get_tijd_fiets());
            if (met_wissels)
                cout << "   " << format_tijd(deelnemer.get_wisseltijd2());
            cout << "   " << format_tijd(deelnemer.get_tijd_loop());
            cout << "   " << format_tijd(deelnemer.totale_tijd()) << "\n";
        }
    }
    cout << endl;
}

int main() {
    load_data();
    print_welkom();

    bool doorgaan = true;
    while (doorgaan)
    {
        print_keuzemenu();
        int keuze = lees_int("Keuze: ");


        if (keuze == 1)
        {
            string naam, datum;
            string is_nederlands_kampioenschap_keuze, wissels_keuze;

            naam = lees_tekst("Naam wedstrijd: ");
            do {
                datum = lees_tekst("Datum (bv. 15-06-2024): ");
                if (!valide_datum(datum))
                    cout << "Ongeldige datum. Probeer opnieuw.\n";
            } while (!valide_datum(datum));

            is_nederlands_kampioenschap_keuze = lees_tekst("Is Nederlands Kampioenschap? (ja/nee): ");

            wissels_keuze = lees_tekst("Wisseltijden registreren? (ja/nee): ");

            bool is_nederlands_kampioenschap = (is_nederlands_kampioenschap_keuze == "ja");
            bool heeft_wissels = (wissels_keuze == "ja");

            // nieuw object maken en toevoegen aan de vector
            Wedstrijd nieuwe_wedstrijd(naam, datum, is_nederlands_kampioenschap, heeft_wissels);
            wedstrijden.push_back(nieuwe_wedstrijd);

            cout << "Wedstrijd aangemaakt met index ["
                << (int)wedstrijden.size() - 1 << "].\n";
        }

        else if (keuze == 2)
        {
            lijst_wedstrijden(wedstrijden);
        }

        else if (keuze == 3)
        {
            Atleet atleet = invoer_atleet();
            atleten.push_back(atleet);
            cout << "Atleet aangemaakt met index [" << (int)atleten.size() - 1 << "].\n";
        }

        else if (keuze == 4)
        {
            lijst_atleten(atleten);
        }

        else if (keuze == 5)
        {
            if (wedstrijden.empty())
            {
                cout << "Geen wedstrijden. Maak eerst een wedstrijd (optie 1).\n";
            }
            else if (atleten.empty())
            {
                cout << "Geen atleten. Maak eerst een atleet (optie 2).\n";
            }
            else
            {
                lijst_wedstrijden(wedstrijden);
                int wedstrijd_index = kies_index((int)wedstrijden.size(), "Kies wedstrijd-index: ");
                if (wedstrijd_index == -1)
                {
                    cout << "Ongeldige keuze.\n";
                }
                else {
                lijst_atleten(atleten);
                int index_atleet = kies_index((int)atleten.size(), "Kies atleet-index: ");
                if (index_atleet == -1)
                {
                    cout << "Ongeldige keuze.\n";
                }
                else
                {
                    // Bepaal licentietype van de atleet
                    string licentie_type = atleten[index_atleet].get_licentie().get_type();

                        // NK-licentiecontrole
                        if (wedstrijden[wedstrijd_index].get_is_nederlands_kampioenschap())
                        {
                            if (licentie_type != "Wedstrijdlicentie") {
                                cout << "Deze wedstrijd is een NK, atleet heeft geen Wedstrijdlicentie.\n";
                                cout << "Koppel eerst een Wedstrijdlicentie via optie 7 en probeer opnieuw.\n";
                                continue; // ga terug naar het hoofdmenu (while-loop)
                            }
                        }

        
                        // Daglicentie alleen geldig op de dag van de wedstrijd
                        if (licentie_type == "Daglicentie")
                        {
                            string licentie_datum = atleten[index_atleet].get_licentie().get_geldig_tot();
                            string wedstrijd_datum = wedstrijden[wedstrijd_index].get_datum();
                            if (licentie_datum != wedstrijd_datum)
                            {
                                cout << "Daglicentie is alleen geldig op de dag van de wedstrijd.\n";
                                cout << "Inschrijving geweigerd.\n";
                                continue; // ga terug naar het hoofdmenu (while-loop)
                            }
                        }

                        // Controleer of licentie nog geldig is ten opzichte van wedstrijddatum
                        if (!atleten[index_atleet].get_licentie().is_geldig_op(
                            wedstrijden[wedstrijd_index].get_datum()))
                        {
                            cout << "Licentie verlopen. Inschrijving geweigerd.\n";
                            continue;
                        }

                    // Controleer op positieve dopingcontroles
                    if (!atleten[index_atleet].get_licentie().is_dopingvrij())
                    {
                        cout << "Atleet heeft een positieve dopingcontrole. Inschrijving geweigerd.\n";
                        continue;
                    }

                    int tijd_zwem, tijd_fiets, tijd_loop;
                    cout << "Tijden in seconden.\n";
                        tijd_zwem = lees_int("Zwem: ");
                        tijd_fiets = lees_int("Fiets: ");
                        tijd_loop = lees_int("Loop: ");

                        if (wedstrijden[wedstrijd_index].get_met_wissels())
                        {
                            int tijd_wissel1, tijd_wissel2;
                            tijd_wissel1 = lees_int("T1 (wissel zwemmen->fietsen, sec): ");
                            tijd_wissel2 = lees_int("T2 (wissel fietsen->lopen, sec):   ");

                            Deelnemer deelnemer(index_atleet, tijd_zwem, tijd_fiets, tijd_loop, tijd_wissel1, tijd_wissel2);
                            wedstrijden[wedstrijd_index].voeg_deelnemer_toe(deelnemer);
                        }
                        else {
                            Deelnemer deelnemer(index_atleet, tijd_zwem, tijd_fiets, tijd_loop);
                            wedstrijden[wedstrijd_index].voeg_deelnemer_toe(deelnemer);
                        }

                        cout << "Deelnemer ingeschreven bij wedstrijd [" << wedstrijd_index << "].\n";
                    }
                }
            }
        }

        else if (keuze == 6)
        {
            if (wedstrijden.empty()) {
                cout << "Geen wedstrijden.\n";
            }
            else {
                lijst_wedstrijden(wedstrijden);
                int wedstrijd_index = kies_index((int)wedstrijden.size(), "Kies wedstrijd-index: ");
                if (wedstrijd_index == -1) {
                    cout << "Ongeldige keuze.\n";
                }
                else {
                    cout << "Aantal deelnemers: "
                        << wedstrijden[wedstrijd_index].aantal_deelnemers() << "\n";
                }
            }
        }

        else if (keuze == 7)
        {
            if (atleten.empty()) {
                cout << "Geen atleten.\n";
            }
            else {
                lijst_atleten(atleten);
                int index_atleet = kies_index((int)atleten.size(), "Kies atleet-index: ");
                if (index_atleet == -1)
                {
                    cout << "Ongeldige keuze.\n";
                }
                else {
                    int keuze_licentie = lees_int("Kies licentie (1 = Dag, 2 = Trainings, 3 = Wedstrijd): ");

                    int licentienummer;
                    string geldig_tot;
                    bool bestaat;
                    do {
                        bestaat = false;
                        licentienummer = lees_int("Licentienummer: ");
                          for (size_t atleet_index = 0; atleet_index < atleten.size(); ++atleet_index) {
                              if (atleet_index != (size_t)index_atleet && atleten[atleet_index].get_licentie().get_nummer() == licentienummer) {
                                bestaat = true;
                                cout << "Licentienummer bestaat al. Probeer opnieuw.\n";
                                break;
                            }
                        }
                    } while (bestaat);
                    do {
                        geldig_tot = lees_tekst("Geldig tot (bv. 31-12-2024): ");
                        if (!valide_datum(geldig_tot))
                            cout << "Ongeldige datum. Probeer opnieuw.\n";
                    } while (!valide_datum(geldig_tot));

                    string licentie_type = "Daglicentie";
                    string vereniging = "";
                    if (keuze_licentie == 2) {
                        licentie_type = "Trainingslicentie";
                        vereniging = lees_tekst("Vereniging: ");
                    }
                    else if (keuze_licentie == 3) {
                        licentie_type = "Wedstrijdlicentie";
                    }

                    Licentie licentie(licentienummer, geldig_tot, licentie_type, vereniging);
                    atleten[index_atleet].set_licentie(licentie);
                    cout << "Licentie gekoppeld aan atleet [" << index_atleet << "].\n";
                }
            }

        }

        else if (keuze == 8)
        {
            if (atleten.empty()) {
                cout << "Geen atleten.\n";
            }
            else {
                lijst_atleten(atleten);
                int index_atleet = kies_index((int)atleten.size(), "Kies atleet-index: ");
                if (index_atleet == -1) {
                    cout << "Ongeldige keuze.\n";
                }
                else {
                    Licentie& licentie = atleten[index_atleet].get_licentie_ref();
                    if (licentie.get_type() != "Wedstrijdlicentie") {
                        cout << "Atleet heeft geen Wedstrijdlicentie.\n";
                    }
                    else {
                        string controle_datum;
                        do {
                            controle_datum = lees_tekst("Datum (bv. 01-01-2024): ");
                            if (!valide_datum(controle_datum))
                                cout << "Ongeldige datum. Probeer opnieuw.\n";
                        } while (!valide_datum(controle_datum));
                        string antwoord = lees_tekst("Doping geconstateerd? (ja/nee): ");
                        bool doping_geconstateerd = (antwoord == "ja");
                        licentie.voeg_dopingcontrole_toe({ controle_datum, doping_geconstateerd });
                        cout << "Dopingcontrole toegevoegd.\n";
                    }
                }
            }
        }

        else if (keuze == 9)
        {
            toon_uitslag_van_wedstrijd(wedstrijden);
        }

        else if (keuze == 10)
        {
            doorgaan = false;
        }

        else
        {
            cout << "Ongeldige keuze\n";
        }
    }

    save_data();
    cout << "Tot ziens!\n";
    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
