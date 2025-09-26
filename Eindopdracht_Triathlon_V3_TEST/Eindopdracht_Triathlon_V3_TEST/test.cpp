#include "pch.h"
#include "../Licentie.h"

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
