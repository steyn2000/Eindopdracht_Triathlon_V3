#include "pch.h"
#include "Licentie.h"
#include "Atleet.h"
#include "Deelnemer.h"
#include "Wedstrijd.h"
#include <vector>
#include "valide_datum.h"
#include "leeftijd_op_datum.h"

using namespace std;

// Forward declaration zodat de GoogleTests de functie uit het hoofdproject kunnen aanroepen.


// Zorg voor een eenvoudige lijst met atleten zodat Deelnemer zijn index kan gebruiken.
vector<Atleet> atleten = { Atleet{} };

namespace test_helpers
{
    Licentie maak_licentie(const string& licentie_type, const string& geldig_tot, bool is_dopingvrij)
    {
        static int nummer_teller = 1;
        Licentie licentie(nummer_teller++, geldig_tot, licentie_type);
        if (!is_dopingvrij)
        {
            licentie.voeg_dopingcontrole_toe({ "01-01-2024", true });
        }
        return licentie;
    }

    void zet_enige_atleet_met_licentie(const Licentie& licentie)
    {
        Atleet atleet;
        atleet.set_licentie(licentie);
        atleten = { atleet };
    }

    Deelnemer maak_standaard_deelnemer()
    {
        return Deelnemer(0, 100, 200, 300);
    }
}

// Basistests voor Licentie::is_geldig_op volgens de opgegeven tabel.

TEST(licentie_is_geldig_op_test, daglicentie_op_zelfde_dag_geldig)
{
    Licentie licentie(1, "15-03-2025", "Daglicentie");
    EXPECT_TRUE(licentie.is_geldig_op("15-03-2025"));
}

TEST(licentie_is_geldig_op_test, daglicentie_voor_dag_ongeldig)
{
    Licentie licentie(1, "15-03-2025", "Daglicentie");
    EXPECT_FALSE(licentie.is_geldig_op("14-03-2025"));
}

TEST(licentie_is_geldig_op_test, daglicentie_na_dag_ongeldig)
{
    Licentie licentie(1, "15-03-2025", "Daglicentie");
    EXPECT_FALSE(licentie.is_geldig_op("16-03-2025"));
}

TEST(licentie_is_geldig_op_test, wedstrijdlicentie_begin_dag_geldig)
{
    Licentie licentie(2, "31-12-2025", "Wedstrijdlicentie");
    EXPECT_TRUE(licentie.is_geldig_op("01-01-2025"));
}

TEST(licentie_is_geldig_op_test, wedstrijdlicentie_eind_dag_geldig)
{
    Licentie licentie(2, "31-12-2025", "Wedstrijdlicentie");
    EXPECT_TRUE(licentie.is_geldig_op("31-12-2025"));
}

TEST(licentie_is_geldig_op_test, wedstrijdlicentie_na_eind_datum_ongeldig)
{
    Licentie licentie(2, "31-12-2025", "Wedstrijdlicentie");
    EXPECT_FALSE(licentie.is_geldig_op("01-01-2026"));
}

TEST(licentie_is_geldig_op_test, ongeldige_datum)
{
    Licentie licentie(3, "31-12-2025", "Wedstrijdlicentie");
    EXPECT_FALSE(licentie.is_geldig_op("29-02-2023"));
}

// Coverage tests voor valide_datum (statement en decision coverage).

// Statement coverage scenario's (T1 t/m T7 uit de tabel).

TEST(valide_datum_statement_coverage, T1_basispad_geldige_datum)
{
    EXPECT_TRUE(valide_datum("15-07-2023"));
}

TEST(valide_datum_statement_coverage, T2_ongeldige_lengte)
{
    EXPECT_FALSE(valide_datum("1-7-2023"));
}

TEST(valide_datum_statement_coverage, T3_teken_geen_cijfer)
{
    EXPECT_FALSE(valide_datum("a5-07-2023"));
}

TEST(valide_datum_statement_coverage, T4_jaar_buiten_bereik)
{
    EXPECT_FALSE(valide_datum("10-10-2201"));
}

TEST(valide_datum_statement_coverage, T5_maand_buiten_bereik)
{
    EXPECT_FALSE(valide_datum("10-13-2020"));
}

TEST(valide_datum_statement_coverage, T6_februari_schrikkeljaar)
{
    EXPECT_TRUE(valide_datum("29-02-2020"));
}

TEST(valide_datum_statement_coverage, T7_februari_geen_schrikkeljaar)
{
    EXPECT_FALSE(valide_datum("29-02-2021"));
}

// Decision (branch) coverage scenario's (T1 t/m T11 uit de tabel).

TEST(valide_datum_branch_coverage, T1_geldige_pad)
{
    EXPECT_TRUE(valide_datum("15-07-2023"));
}

TEST(valide_datum_branch_coverage, T2_teken_kleiner_dan_nul)
{
    EXPECT_FALSE(valide_datum("/5-07-2023"));
}

TEST(valide_datum_branch_coverage, T3_teken_groter_dan_negen)
{
    EXPECT_FALSE(valide_datum("a5-07-2023"));
}

TEST(valide_datum_branch_coverage, T4_schrikkeljaar_true)
{
    EXPECT_TRUE(valide_datum("29-02-2020"));
}

TEST(valide_datum_branch_coverage, T5_schrikkeljaar_false)
{
    EXPECT_FALSE(valide_datum("29-02-2021"));
}

TEST(valide_datum_branch_coverage, T6_maand_ongeldig_hoog)
{
    EXPECT_FALSE(valide_datum("22-19-2020"));
}

TEST(valide_datum_branch_coverage, T7_maand_ongeldig_laag)
{
    EXPECT_FALSE(valide_datum("10-00-2019"));
}

TEST(valide_datum_branch_coverage, T8_dag_boven_maximum)
{
    EXPECT_FALSE(valide_datum("32-12-2020"));
}

TEST(valide_datum_branch_coverage, T9_dag_boven_maximum_in_april)
{
    EXPECT_FALSE(valide_datum("31-04-2020"));
}

TEST(valide_datum_branch_coverage, T10_jaar_te_klein)
{
    EXPECT_FALSE(valide_datum("12-12-1899"));
}

TEST(valide_datum_branch_coverage, T11_jaar_te_groot)
{
    EXPECT_FALSE(valide_datum("12-12-2101"));
}

// Statement coverage voor leeftijd_op_datum (L1 en L2 uit de tabel).

TEST(leeftijd_op_datum_statement_coverage, L1_verjaardag_geweest)
{
    EXPECT_EQ(leeftijd_op_datum("01-01-2000", "01-07-2020"), 20);
}

TEST(leeftijd_op_datum_statement_coverage, L2_verjaardag_niet_geweest)
{
    EXPECT_EQ(leeftijd_op_datum("01-10-2000", "01-07-2020"), 19);
}

// Decision (branch) coverage voor leeftijd_op_datum (L1 en L2 dekken beide paden).

TEST(leeftijd_op_datum_branch_coverage, L1_pad_verjaardag_geweest)
{
    EXPECT_EQ(leeftijd_op_datum("01-01-2000", "01-07-2020"), 20);
}

TEST(leeftijd_op_datum_branch_coverage, L2_pad_verjaardag_niet_geweest)
{
    EXPECT_EQ(leeftijd_op_datum("01-10-2000", "01-07-2020"), 19);
}

// Basistests voor Licentie::is_dopingvrij volgens de opgegeven tabel.

TEST(licentie_is_dopingvrij_test, geen_dopingcontroles)
{
    Licentie licentie;
    EXPECT_TRUE(licentie.is_dopingvrij());
}

TEST(licentie_is_dopingvrij_test, alleen_negatieve_controles)
{
    Licentie licentie;
    licentie.voeg_dopingcontrole_toe({"01-01-2024", false});
    licentie.voeg_dopingcontrole_toe({"01-06-2024", false});

    EXPECT_TRUE(licentie.is_dopingvrij());
}

TEST(licentie_is_dopingvrij_test, positieve_controle_tussen_negatieve)
{
    Licentie licentie;
    licentie.voeg_dopingcontrole_toe({"01-01-2024", false});
    licentie.voeg_dopingcontrole_toe({"15-03-2024", true});
    licentie.voeg_dopingcontrole_toe({"01-06-2024", false});

    EXPECT_FALSE(licentie.is_dopingvrij());
}

TEST(licentie_is_dopingvrij_test, positieve_controle_op_wedstrijddag)
{
    Licentie licentie;
    licentie.voeg_dopingcontrole_toe({"20-07-2024", true});

    EXPECT_FALSE(licentie.is_dopingvrij());
}

// Basistests voor Deelnemer::totale_tijd volgens de opgegeven tabel.

TEST(deelnemer_totale_tijd_test, optelling_zonder_wissels)
{
    Deelnemer deelnemer(0, 900, 3600, 1800);

    EXPECT_EQ(deelnemer.totale_tijd(), 6300);
}

TEST(deelnemer_totale_tijd_test, optelling_met_wissels)
{
    Deelnemer deelnemer(0, 900, 3600, 1800, 90, 40);

    EXPECT_EQ(deelnemer.totale_tijd(), 6430);
}

TEST(deelnemer_totale_tijd_test, segment_met_nul_tijd)
{
    Deelnemer deelnemer(0, 900, 3600, 0);

    EXPECT_EQ(deelnemer.totale_tijd(), 4500);
}

TEST(deelnemer_totale_tijd_test, grote_waarden_zonder_overflow)
{
    Deelnemer deelnemer(0, 900000, 3600000, 1800000);

    EXPECT_EQ(deelnemer.totale_tijd(), 6300000);
}

TEST(deelnemer_totale_tijd_test, wisseltijden_van_nul)
{
    Deelnemer deelnemer(0, 900, 3600, 1800, 0, 0);

    EXPECT_EQ(deelnemer.totale_tijd(), 6300);
}

// Basistests voor Wedstrijd::voeg_deelnemer_toe volgens de opgegeven tabel.

TEST(wedstrijd_voeg_deelnemer_toe_test, nk_wedstrijdlicentie_geldig_en_dopingvrij)
{
    test_helpers::zet_enige_atleet_met_licentie(test_helpers::maak_licentie("Wedstrijdlicentie", "20-07-2025", true));

    Wedstrijd wedstrijd("NK Triathlon", "20-07-2025", true, false);
    Deelnemer deelnemer = test_helpers::maak_standaard_deelnemer();

    wedstrijd.voeg_deelnemer_toe(deelnemer);

    EXPECT_EQ(wedstrijd.aantal_deelnemers(), 1);
}

TEST(wedstrijd_voeg_deelnemer_toe_test, niet_nk_daglicentie_geldig_en_dopingvrij)
{
    test_helpers::zet_enige_atleet_met_licentie(test_helpers::maak_licentie("Daglicentie", "20-07-2025", true));

    Wedstrijd wedstrijd("Zomertriathlon", "20-07-2025", false, false);
    Deelnemer deelnemer = test_helpers::maak_standaard_deelnemer();

    wedstrijd.voeg_deelnemer_toe(deelnemer);

    EXPECT_EQ(wedstrijd.aantal_deelnemers(), 1);
}

TEST(wedstrijd_voeg_deelnemer_toe_test, nk_wedstrijdlicentie_met_doping_wordt_geweigerd)
{
    test_helpers::zet_enige_atleet_met_licentie(test_helpers::maak_licentie("Wedstrijdlicentie", "20-07-2025", false));

    Wedstrijd wedstrijd("NK Triathlon", "20-07-2025", true, false);
    Deelnemer deelnemer = test_helpers::maak_standaard_deelnemer();

    wedstrijd.voeg_deelnemer_toe(deelnemer);

    EXPECT_EQ(wedstrijd.aantal_deelnemers(), 0);
}

TEST(wedstrijd_voeg_deelnemer_toe_test, nk_wedstrijdlicentie_niet_geldig_wordt_geweigerd)
{
    test_helpers::zet_enige_atleet_met_licentie(test_helpers::maak_licentie("Wedstrijdlicentie", "19-07-2025", true));

    Wedstrijd wedstrijd("NK Triathlon", "20-07-2025", true, false);
    Deelnemer deelnemer = test_helpers::maak_standaard_deelnemer();

    wedstrijd.voeg_deelnemer_toe(deelnemer);

    EXPECT_EQ(wedstrijd.aantal_deelnemers(), 0);
}

TEST(wedstrijd_voeg_deelnemer_toe_test, niet_nk_wedstrijdlicentie_niet_geldig_wordt_geweigerd)
{
    test_helpers::zet_enige_atleet_met_licentie(test_helpers::maak_licentie("Wedstrijdlicentie", "19-07-2025", true));

    Wedstrijd wedstrijd("Regionale triathlon", "20-07-2025", false, false);
    Deelnemer deelnemer = test_helpers::maak_standaard_deelnemer();

    wedstrijd.voeg_deelnemer_toe(deelnemer);

    EXPECT_EQ(wedstrijd.aantal_deelnemers(), 0);
}

TEST(wedstrijd_voeg_deelnemer_toe_test, niet_nk_wedstrijdlicentie_met_doping_wordt_geweigerd)
{
    test_helpers::zet_enige_atleet_met_licentie(test_helpers::maak_licentie("Wedstrijdlicentie", "20-07-2025", false));

    Wedstrijd wedstrijd("Regionale triathlon", "20-07-2025", false, false);
    Deelnemer deelnemer = test_helpers::maak_standaard_deelnemer();

    wedstrijd.voeg_deelnemer_toe(deelnemer);

    EXPECT_EQ(wedstrijd.aantal_deelnemers(), 0);
}

TEST(wedstrijd_voeg_deelnemer_toe_test, nk_dag_of_trainingslicentie_wordt_geweigerd)
{
    test_helpers::zet_enige_atleet_met_licentie(test_helpers::maak_licentie("Daglicentie", "20-07-2025", true));

    Wedstrijd wedstrijd("NK Triathlon", "20-07-2025", true, false);
    Deelnemer deelnemer = test_helpers::maak_standaard_deelnemer();

    wedstrijd.voeg_deelnemer_toe(deelnemer);

    EXPECT_EQ(wedstrijd.aantal_deelnemers(), 0);
}

TEST(wedstrijd_voeg_deelnemer_toe_test, dubbele_inschrijving_wordt_genegeerd)
{
    test_helpers::zet_enige_atleet_met_licentie(test_helpers::maak_licentie("Wedstrijdlicentie", "20-07-2025", true));

    Wedstrijd wedstrijd("NK Triathlon", "20-07-2025", true, false);
    Deelnemer deelnemer = test_helpers::maak_standaard_deelnemer();

    wedstrijd.voeg_deelnemer_toe(deelnemer);
    wedstrijd.voeg_deelnemer_toe(deelnemer);

    EXPECT_EQ(wedstrijd.aantal_deelnemers(), 1);
}
