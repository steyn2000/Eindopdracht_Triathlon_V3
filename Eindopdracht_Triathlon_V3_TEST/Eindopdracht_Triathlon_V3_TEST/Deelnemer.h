#pragma once
#include <string>
#include "Atleet.h"

using namespace std;

/**
 * @file Deelnemer.h
 * @brief Houdt de wedstrijdtijden van één atleet bij.
 */

/**
 * @brief Een deelnemer met tijden voor alle onderdelen.
 */
class Deelnemer
{
private:
    int index_atleet{ 0 }; ///< Verwijzing naar atleet in globale lijst.
    int tijd_zwem{ 0 };     ///< Zwemtijd in seconden.
    int tijd_fiets{ 0 };    ///< Fietstijd in seconden.
    int tijd_loop{ 0 };     ///< Looptijd in seconden.
    bool heeft_wissel1{ false }; ///< Heeft wissel 1? 
    bool heeft_wissel2{ false }; ///< Heeft wissel 2?
    int tijd_wissel1{ 0 };  ///< Tijd voor eerste wissel (indien aanwezig).
    int tijd_wissel2{ 0 };  ///< Tijd voor tweede wissel (indien aanwezig).

public:
    // constructors

    /** @brief Standaardconstructor. */
    Deelnemer() = default;

    /**
     * @brief Maak een deelnemer zonder wisseltijden.
     * @param index_atleet Index naar atleet in de globale lijst.
     * @param tijd_zwem Zwemtijd in seconden.
     * @param tijd_fiets Fietstijd in seconden.
     * @param tijd_loop Looptijd in seconden.
     */
    Deelnemer(int index_atleet, int tijd_zwem, int tijd_fiets, int tijd_loop);

    /**
     * @brief Maak een deelnemer met wisseltijden.
     * @param index_atleet Index naar atleet in de globale lijst.
     * @param tijd_zwem Zwemtijd in seconden.
     * @param tijd_fiets Fietstijd in seconden.
     * @param tijd_loop Looptijd in seconden.
     * @param tijd_wissel1 Tijd voor eerste wissel.
     * @param tijd_wissel2 Tijd voor tweede wissel.
     */
    Deelnemer(int index_atleet, int tijd_zwem, int tijd_fiets, int tijd_loop, int tijd_wissel1, int tijd_wissel2);

    // setters

    /** @brief Zet de zwemtijd. */
    void set_tijd_zwem(int nieuwe_tijd_zwem);

    /** @brief Zet de fietstijd. */
    void set_tijd_fiets(int nieuwe_tijd_fiets);

    /** @brief Zet de looptijd. */
    void set_tijd_loop(int nieuwe_tijd_loop);

    /** @brief Zet de eerste wisseltijd en markeer deze als aanwezig. */
    void set_wisseltijd1(int tijd_wissel1);

    /** @brief Zet de tweede wisseltijd en markeer deze als aanwezig. */
    void set_wisseltijd2(int tijd_wissel2);

    // getters

    /** @brief Geeft de gekoppelde atleet terug. */
    const Atleet& get_atleet() const;

    /** @brief Geeft de index van de atleet terug. */
    int get_index_atleet() const;

    /** @brief Geeft de zwemtijd terug. */
    int get_tijd_zwem() const;

    /** @brief Geeft de fietstijd terug. */
    int get_tijd_fiets() const;

    /** @brief Geeft de looptijd terug. */
    int get_tijd_loop() const;

    /** @brief Is de eerste wissel aanwezig? */
    bool get_heeft_wissel1() const;

    /** @brief Is de tweede wissel aanwezig? */
    bool get_heeft_wissel2() const;

    /** @brief Geeft de tijd van de eerste wissel terug. */
    int get_wisseltijd1() const;

    /** @brief Geeft de tijd van de tweede wissel terug. */
    int get_wisseltijd2() const;

    // berekening

    /** @brief Totale tijd inclusief wissels. */
    int totale_tijd() const;
};

