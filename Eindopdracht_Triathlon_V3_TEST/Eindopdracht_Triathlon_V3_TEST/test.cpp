#include "pch.h"
#include "Licentie.h"
#include "Atleet.h"
#include "Deelnemer.h"
#include "Wedstrijd.h"

#include <vector>

using namespace std;

// Zorg voor een eenvoudige lijst met atleten zodat Deelnemer zijn index kan gebruiken.
vector<Atleet> atleten = { Atleet{} };

namespace
{
    Licentie MaakLicentie(const string& type, const string& geldig_tot, bool dopingvrij)
    {
        static int nummer_teller = 1;
        Licentie licentie(nummer_teller++, geldig_tot, type);
        if (!dopingvrij)
        {
            licentie.voeg_dopingcontrole_toe({ "01-01-2024", true });
        }
        return licentie;
    }

    void ZetEnigeAtleetMetLicentie(const Licentie& licentie)
    {
        Atleet atleet;
        atleet.set_licentie(licentie);
        atleten = { atleet };
    }

    Deelnemer MaakStandaardDeelnemer()
    {
        return Deelnemer(0, 100, 200, 300);
    }
}

// Basistests voor Licentie::is_geldig_op volgens de opgegeven tabel.

TEST(LicentieIsGeldigOpTest, DaglicentieOpZelfdeDagGeldig)
{
    Licentie licentie(1, "15-03-2025", "Daglicentie");
    EXPECT_TRUE(licentie.is_geldig_op("15-03-2025"));
}

TEST(LicentieIsGeldigOpTest, DaglicentieVoorDagOngeldig)
{
    Licentie licentie(1, "15-03-2025", "Daglicentie");
    EXPECT_FALSE(licentie.is_geldig_op("14-03-2025"));
}

TEST(LicentieIsGeldigOpTest, DaglicentieNaDagOngeldig)
{
    Licentie licentie(1, "15-03-2025", "Daglicentie");
    EXPECT_FALSE(licentie.is_geldig_op("16-03-2025"));
}

TEST(LicentieIsGeldigOpTest, WedstrijdlicentieBeginDagGeldig)
{
    Licentie licentie(2, "31-12-2025", "Wedstrijdlicentie");
    EXPECT_TRUE(licentie.is_geldig_op("01-01-2025"));
}

TEST(LicentieIsGeldigOpTest, WedstrijdlicentieEindDagGeldig)
{
    Licentie licentie(2, "31-12-2025", "Wedstrijdlicentie");
    EXPECT_TRUE(licentie.is_geldig_op("31-12-2025"));
}

TEST(LicentieIsGeldigOpTest, WedstrijdlicentieNaEindDatumOngeldig)
{
    Licentie licentie(2, "31-12-2025", "Wedstrijdlicentie");
    EXPECT_FALSE(licentie.is_geldig_op("01-01-2026"));
}

TEST(LicentieIsGeldigOpTest, OngeldigeDatum)
{
    Licentie licentie(3, "31-12-2025", "Wedstrijdlicentie");
    EXPECT_FALSE(licentie.is_geldig_op("29-02-2023"));
}

// Basistests voor Licentie::is_dopingvrij volgens de opgegeven tabel.

TEST(LicentieIsDopingvrijTest, GeenDopingcontroles)
{
    Licentie licentie;
    EXPECT_TRUE(licentie.is_dopingvrij());
}

TEST(LicentieIsDopingvrijTest, AlleenNegatieveControles)
{
    Licentie licentie;
    licentie.voeg_dopingcontrole_toe({"01-01-2024", false});
    licentie.voeg_dopingcontrole_toe({"01-06-2024", false});

    EXPECT_TRUE(licentie.is_dopingvrij());
}

TEST(LicentieIsDopingvrijTest, PositieveControleTussenNegatieve)
{
    Licentie licentie;
    licentie.voeg_dopingcontrole_toe({"01-01-2024", false});
    licentie.voeg_dopingcontrole_toe({"15-03-2024", true});
    licentie.voeg_dopingcontrole_toe({"01-06-2024", false});

    EXPECT_FALSE(licentie.is_dopingvrij());
}

TEST(LicentieIsDopingvrijTest, PositieveControleOpWedstrijddag)
{
    Licentie licentie;
    licentie.voeg_dopingcontrole_toe({"20-07-2024", true});

    EXPECT_FALSE(licentie.is_dopingvrij());
}

// Basistests voor Deelnemer::totale_tijd volgens de opgegeven tabel.

TEST(DeelnemerTotaleTijdTest, OptellingZonderWissels)
{
    Deelnemer deelnemer(0, 900, 3600, 1800);

    EXPECT_EQ(deelnemer.totale_tijd(), 6300);
}

TEST(DeelnemerTotaleTijdTest, OptellingMetWissels)
{
    Deelnemer deelnemer(0, 900, 3600, 1800, 90, 40);

    EXPECT_EQ(deelnemer.totale_tijd(), 6430);
}

TEST(DeelnemerTotaleTijdTest, SegmentMetNulTijd)
{
    Deelnemer deelnemer(0, 900, 3600, 0);

    EXPECT_EQ(deelnemer.totale_tijd(), 4500);
}

TEST(DeelnemerTotaleTijdTest, GroteWaardenZonderOverflow)
{
    Deelnemer deelnemer(0, 900000, 3600000, 1800000);

    EXPECT_EQ(deelnemer.totale_tijd(), 6300000);
}

TEST(DeelnemerTotaleTijdTest, WisseltijdenVanNul)
{
    Deelnemer deelnemer(0, 900, 3600, 1800, 0, 0);

    EXPECT_EQ(deelnemer.totale_tijd(), 6300);
}

// Basistests voor Wedstrijd::voeg_deelnemer_toe volgens de opgegeven tabel.

TEST(WedstrijdVoegDeelnemerToeTest, NkWedstrijdlicentieGeldigEnDopingvrij)
{
    ZetEnigeAtleetMetLicentie(MaakLicentie("Wedstrijdlicentie", "20-07-2025", true));

    Wedstrijd wedstrijd("NK Triathlon", "20-07-2025", true, false);
    Deelnemer deelnemer = MaakStandaardDeelnemer();

    wedstrijd.voeg_deelnemer_toe(deelnemer);

    EXPECT_EQ(wedstrijd.aantal_deelnemers(), 1);
}

TEST(WedstrijdVoegDeelnemerToeTest, NietNkDaglicentieGeldigEnDopingvrij)
{
    ZetEnigeAtleetMetLicentie(MaakLicentie("Daglicentie", "20-07-2025", true));

    Wedstrijd wedstrijd("Zomertriathlon", "20-07-2025", false, false);
    Deelnemer deelnemer = MaakStandaardDeelnemer();

    wedstrijd.voeg_deelnemer_toe(deelnemer);

    EXPECT_EQ(wedstrijd.aantal_deelnemers(), 1);
}

TEST(WedstrijdVoegDeelnemerToeTest, NkWedstrijdlicentieMetDopingWordtGeweigerd)
{
    ZetEnigeAtleetMetLicentie(MaakLicentie("Wedstrijdlicentie", "20-07-2025", false));

    Wedstrijd wedstrijd("NK Triathlon", "20-07-2025", true, false);
    Deelnemer deelnemer = MaakStandaardDeelnemer();

    wedstrijd.voeg_deelnemer_toe(deelnemer);

    EXPECT_EQ(wedstrijd.aantal_deelnemers(), 0);
}

TEST(WedstrijdVoegDeelnemerToeTest, NkWedstrijdlicentieNietGeldigWordtGeweigerd)
{
    ZetEnigeAtleetMetLicentie(MaakLicentie("Wedstrijdlicentie", "19-07-2025", true));

    Wedstrijd wedstrijd("NK Triathlon", "20-07-2025", true, false);
    Deelnemer deelnemer = MaakStandaardDeelnemer();

    wedstrijd.voeg_deelnemer_toe(deelnemer);

    EXPECT_EQ(wedstrijd.aantal_deelnemers(), 0);
}

TEST(WedstrijdVoegDeelnemerToeTest, NietNkWedstrijdlicentieNietGeldigWordtGeweigerd)
{
    ZetEnigeAtleetMetLicentie(MaakLicentie("Wedstrijdlicentie", "19-07-2025", true));

    Wedstrijd wedstrijd("Regionale triathlon", "20-07-2025", false, false);
    Deelnemer deelnemer = MaakStandaardDeelnemer();

    wedstrijd.voeg_deelnemer_toe(deelnemer);

    EXPECT_EQ(wedstrijd.aantal_deelnemers(), 0);
}

TEST(WedstrijdVoegDeelnemerToeTest, NietNkWedstrijdlicentieMetDopingWordtGeweigerd)
{
    ZetEnigeAtleetMetLicentie(MaakLicentie("Wedstrijdlicentie", "20-07-2025", false));

    Wedstrijd wedstrijd("Regionale triathlon", "20-07-2025", false, false);
    Deelnemer deelnemer = MaakStandaardDeelnemer();

    wedstrijd.voeg_deelnemer_toe(deelnemer);

    EXPECT_EQ(wedstrijd.aantal_deelnemers(), 0);
}

TEST(WedstrijdVoegDeelnemerToeTest, NkDagOfTrainingslicentieWordtGeweigerd)
{
    ZetEnigeAtleetMetLicentie(MaakLicentie("Daglicentie", "20-07-2025", true));

    Wedstrijd wedstrijd("NK Triathlon", "20-07-2025", true, false);
    Deelnemer deelnemer = MaakStandaardDeelnemer();

    wedstrijd.voeg_deelnemer_toe(deelnemer);

    EXPECT_EQ(wedstrijd.aantal_deelnemers(), 0);
}

TEST(WedstrijdVoegDeelnemerToeTest, DubbeleInschrijvingWordtGenegeerd)
{
    ZetEnigeAtleetMetLicentie(MaakLicentie("Wedstrijdlicentie", "20-07-2025", true));

    Wedstrijd wedstrijd("NK Triathlon", "20-07-2025", true, false);
    Deelnemer deelnemer = MaakStandaardDeelnemer();

    wedstrijd.voeg_deelnemer_toe(deelnemer);
    wedstrijd.voeg_deelnemer_toe(deelnemer);

    EXPECT_EQ(wedstrijd.aantal_deelnemers(), 1);
}
