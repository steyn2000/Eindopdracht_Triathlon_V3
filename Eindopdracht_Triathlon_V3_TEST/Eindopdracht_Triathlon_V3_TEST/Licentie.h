#pragma once
#include <string>
#include <vector>

using namespace std;

/**
 * @file Licentie.h
 * @brief Bevat de licentiegegevens van een atleet.
 */

/**
 * @brief Resultaat van een dopingcontrole.
 */
struct DopingControle
{
    string datum;              ///< Datum van de controle.
    bool doping_geconstateerd; ///< true als er doping is geconstateerd.
};

/**
 * @brief Klasse die een licentie voor een atleet voorstelt.
 */
class Licentie
{
private:
    int licentie_nummer;              ///< Nummer van de licentie.
    string geldig_tot;                ///< Datum waarop de licentie verloopt.
    string type;                      ///< Dag-, trainings- of wedstrijdlicentie.
    string vereniging;                ///< Vereniging (alleen voor trainingslicentie).
    vector<DopingControle> doping_controles; ///< Alleen voor wedstrijdlicentie.

public:
    // Constructoren

    /** @brief Standaardconstructor. */
    Licentie();

    /**
     * @brief Maak een nieuwe licentie.
     * @param nummer Licentienummer.
     * @param geldig_tot Datum tot wanneer de licentie geldig is.
     * @param type Type licentie.
     * @param vereniging Optioneel: vereniging voor trainingslicentie.
     */
    Licentie(int nummer, const string& geldig_tot, const string& type, const string& vereniging = "");

    // Getters

    /** @brief Geeft het licentienummer terug. */
    int get_nummer() const;

    /** @brief Geeft de geldigheidsdatum terug. */
    string get_geldig_tot() const;

    /** @brief Geeft het type licentie terug. */
    string get_type() const;

    /** @brief Geeft de vereniging terug. */
    string get_vereniging() const;

    /** @brief Geeft de lijst met dopingcontroles terug. */
    const vector<DopingControle>& get_doping_controles() const;

    // Dopingstatus

    /** @brief Controleert of er nooit doping is gevonden. */
    bool is_dopingvrij() const;

    // Geldigheid

    /** @brief Controleert of de licentie geldig is op een datum. */
    bool is_geldig_op(const string& datum) const;

    // Setters

    /** @brief Zet het licentienummer. */
    void set_nummer(int nummer);

    /** @brief Zet de geldigheidsdatum. */
    void set_geldig_tot(const string& geldig_tot);

    /** @brief Zet het type licentie. */
    void set_type(const string& nieuw_type);

    /** @brief Zet de vereniging. */
    void set_vereniging(const string& vereniging);

    /** @brief Voeg een dopingcontrole toe. */
    void voeg_dopingcontrole_toe(const DopingControle& controle);
};



