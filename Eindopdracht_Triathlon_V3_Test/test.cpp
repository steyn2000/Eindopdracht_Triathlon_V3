#include "pch.h"
#include "../Licentie.h"

#include <iomanip>
#include <sstream>
#include <string>

namespace
{
std::string make_date(int day, int month, int year)
{
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << day << "-"
        << std::setw(2) << month << "-"
        << std::setw(4) << year;
    return oss.str();
}
}

TEST(LicentieIsGeldigOpTest, DaglicentieDagVoorafNietGeldig)
{
    Licentie daglicentie(1, make_date(1, 6, 2025), "Daglicentie");
    EXPECT_FALSE(daglicentie.is_geldig_op(make_date(31, 5, 2025)));
}

TEST(LicentieIsGeldigOpTest, DaglicentieOpDagGeldig)
{
    Licentie daglicentie(1, make_date(1, 6, 2025), "Daglicentie");
    EXPECT_TRUE(daglicentie.is_geldig_op(make_date(1, 6, 2025)));
}

TEST(LicentieIsGeldigOpTest, DaglicentieDagErnaNietGeldig)
{
    Licentie daglicentie(1, make_date(1, 6, 2025), "Daglicentie");
    EXPECT_FALSE(daglicentie.is_geldig_op(make_date(2, 6, 2025)));
}

TEST(LicentieIsGeldigOpTest, WedstrijdlicentieVoorBegindatumNietGeldig)
{
    Licentie wedstrijdlicentie(2, make_date(31, 12, 2025), "Wedstrijdlicentie");
    EXPECT_FALSE(wedstrijdlicentie.is_geldig_op(make_date(31, 12, 2024)));
}

TEST(LicentieIsGeldigOpTest, WedstrijdlicentieOpBegindatumGeldig)
{
    Licentie wedstrijdlicentie(2, make_date(31, 12, 2025), "Wedstrijdlicentie");
    EXPECT_TRUE(wedstrijdlicentie.is_geldig_op(make_date(1, 1, 2025)));
}

TEST(LicentieIsGeldigOpTest, WedstrijdlicentieOpEinddatumGeldig)
{
    Licentie wedstrijdlicentie(2, make_date(31, 12, 2025), "Wedstrijdlicentie");
    EXPECT_TRUE(wedstrijdlicentie.is_geldig_op(make_date(31, 12, 2025)));
}

TEST(LicentieIsGeldigOpTest, WedstrijdlicentieNaEinddatumNietGeldig)
{
    Licentie wedstrijdlicentie(2, make_date(31, 12, 2025), "Wedstrijdlicentie");
    EXPECT_FALSE(wedstrijdlicentie.is_geldig_op(make_date(1, 1, 2026)));
}

TEST(LicentieIsGeldigOpTest, OngeldigeDatumNietGeldig_Februari29InNietSchrikkeljaar)
{
    Licentie wedstrijdlicentie(2, make_date(31, 12, 2025), "Wedstrijdlicentie");
    EXPECT_FALSE(wedstrijdlicentie.is_geldig_op(make_date(29, 2, 2023)));
}

TEST(LicentieIsGeldigOpTest, OngeldigeDatumNietGeldig_April31)
{
    Licentie wedstrijdlicentie(2, make_date(31, 12, 2025), "Wedstrijdlicentie");
    EXPECT_FALSE(wedstrijdlicentie.is_geldig_op(make_date(31, 4, 2025)));
}

TEST(LicentieIsGeldigOpTest, GeldigeSchrikkeldatumGeldig)
{
    Licentie wedstrijdlicentie(2, make_date(31, 12, 2025), "Wedstrijdlicentie");
    EXPECT_TRUE(wedstrijdlicentie.is_geldig_op(make_date(29, 2, 2024)));
}
