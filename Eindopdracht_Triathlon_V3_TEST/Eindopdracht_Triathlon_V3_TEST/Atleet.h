/**
 * @file Atleet.h
 * @brief Klasse die alle gegevens van één atleet bijhoudt.
 */

#pragma once
#include <string>
#include "Licentie.h"

using namespace std;

/**
 * @brief Houdt basisinformatie van een atleet bij.
 */
class Atleet {
private:
    string voornaam;             ///< Voornaam van de atleet.
    string achternaam;           ///< Achternaam van de atleet.
    string geboortedatum;        ///< Geboortedatum (dd-mm-jjjj).
    char geslacht;               ///< Geslacht van de atleet (M/V).
    Licentie licentie{ 0, "", "", "" }; ///< Atleet start zonder ingevulde licentie.

public:
    /**
     * @brief Standaardconstructor.
     */
    Atleet();

    /**
     * @brief Maak een atleet met naam, geboortedatum en geslacht.
     * @param voornaam Voornaam van de atleet.
     * @param achternaam Achternaam van de atleet.
     * @param geboortedatum Geboortedatum (dd-mm-jjjj).
     * @param geslacht Geslacht van de atleet.
     */
    Atleet(string voornaam, string achternaam, string geboortedatum, char geslacht);

    // setters

    /** @brief Zet een nieuwe voornaam. */
    void set_voornaam(string nieuwe_voornaam);

    /** @brief Zet een nieuwe achternaam. */
    void set_achternaam(string nieuwe_achternaam);

    /** @brief Zet een nieuwe geboortedatum. */
    void set_geboortedatum(string nieuwe_geboortedatum);

    /** @brief Zet het geslacht. */
    void set_geslacht(char nieuw_geslacht);

    /** @brief Koppel een licentie aan de atleet. */
    void set_licentie(const Licentie& nieuwe_licentie);

    // getters

    /** @brief Geeft de voornaam terug. */
    string get_voornaam() const;

    /** @brief Geeft de achternaam terug. */
    string get_achternaam() const;

    /** @brief Geeft de geboortedatum terug. */
    string get_geboortedatum() const;

    /** @brief Geeft het geslacht terug. */
    char get_geslacht() const;

    /** @brief Geeft een kopie van de licentie terug. */
    Licentie get_licentie() const;

    /** @brief Geeft een verwijzing naar de licentie terug. */
    Licentie& get_licentie_ref();
};

