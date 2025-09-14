#pragma once
#include <string>
#include <vector>
#include "Deelnemer.h"

using namespace std;

/**
 * @file Wedstrijd.h
 * @brief Bevat informatie en deelnemers van een wedstrijd.
 */

/**
 * @brief Een wedstrijd met een lijst van deelnemers.
 */
class Wedstrijd
{
private:
    string naam;   ///< Naam van de wedstrijd.
    string datum;  ///< Datum van de wedstrijd (dd-mm-jjjj).

    bool is_nederlands_kampioenschap{ false }; ///< Is dit een NK?
    bool met_wissels{ false };                 ///< Zijn wisseltijden van toepassing?

    vector<Deelnemer> deelnemers; ///< Lijst met alle deelnemers.

public:
    /** @brief Standaardconstructor. */
    Wedstrijd() = default;

    /**
     * @brief Maak een nieuwe wedstrijd.
     * @param wedstrijd_naam Naam van de wedstrijd.
     * @param wedstrijd_datum Datum van de wedstrijd.
     * @param is_nederlands_kampioenschap Is het een Nederlands kampioenschap?
     * @param heeft_wissels Zijn er wisseltijden?
     */
    Wedstrijd(string wedstrijd_naam, string wedstrijd_datum, bool is_nederlands_kampioenschap, bool heeft_wissels);

    // basisacties

    /** @brief Voeg een deelnemer toe als deze nog niet bestaat. */
    void voeg_deelnemer_toe(const Deelnemer& nieuwe_deelnemer);

    // simpele output (kan later klassement worden)

    /** @brief Geeft het aantal deelnemers terug. */
    int aantal_deelnemers() const;

    /** @brief Geeft de lijst met deelnemers terug. */
    const vector<Deelnemer>& get_deelnemers() const;

    /** @brief Geeft een gesorteerde kopie van de deelnemerslijst. */
    vector<Deelnemer> deelnemer_lijst_gesorteerd() const;

    // getters

    /** @brief Geeft de naam van de wedstrijd terug. */
    string get_naam() const;

    /** @brief Geeft de datum van de wedstrijd terug. */
    string get_datum() const;

    /** @brief Geeft aan of wisseltijden aanwezig zijn. */
    bool get_met_wissels() const;

    /** @brief Geeft aan of het een Nederlands kampioenschap is. */
    bool get_is_nederlands_kampioenschap() const;
};
