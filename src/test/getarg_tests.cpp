#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>

#include "util.h"

BOOST_AUTO_TEST_SUITE(getarg_tests)

static void
ResetArgs(const std::string& strArg)
{
    std::vector<std::string> vecArg;
    boost::split(vecArg, strArg, boost::is_space(), boost::token_compress_on);

    // Insert dummy executable name:
    vecArg.insert(vecArg.begin(), "testbitcoin");

    // Convert to char*:
    std::vector<const char*> vecChar;
    BOOST_FOREACH(std::string& s, vecArg)
        vecChar.push_back(s.c_str());

    ParseParameters(vecChar.size(), &vecChar[0]);
}

BOOST_AUTO_TEST_CASE(boolarg)
{
    ResetArgs("-LUC");
    BOOST_CHECK(GetBoolArg("-LUC"));
    BOOST_CHECK(GetBoolArg("-LUC", false));
    BOOST_CHECK(GetBoolArg("-LUC", true));

    BOOST_CHECK(!GetBoolArg("-fo"));
    BOOST_CHECK(!GetBoolArg("-fo", false));
    BOOST_CHECK(GetBoolArg("-fo", true));

    BOOST_CHECK(!GetBoolArg("-LUCo"));
    BOOST_CHECK(!GetBoolArg("-LUCo", false));
    BOOST_CHECK(GetBoolArg("-LUCo", true));

    ResetArgs("-LUC=0");
    BOOST_CHECK(!GetBoolArg("-LUC"));
    BOOST_CHECK(!GetBoolArg("-LUC", false));
    BOOST_CHECK(!GetBoolArg("-LUC", true));

    ResetArgs("-LUC=1");
    BOOST_CHECK(GetBoolArg("-LUC"));
    BOOST_CHECK(GetBoolArg("-LUC", false));
    BOOST_CHECK(GetBoolArg("-LUC", true));

    // New 0.6 feature: auto-map -nosomething to !-something:
    ResetArgs("-noLUC");
    BOOST_CHECK(!GetBoolArg("-LUC"));
    BOOST_CHECK(!GetBoolArg("-LUC", false));
    BOOST_CHECK(!GetBoolArg("-LUC", true));

    ResetArgs("-noLUC=1");
    BOOST_CHECK(!GetBoolArg("-LUC"));
    BOOST_CHECK(!GetBoolArg("-LUC", false));
    BOOST_CHECK(!GetBoolArg("-LUC", true));

    ResetArgs("-LUC -noLUC");  // -LUC should win
    BOOST_CHECK(GetBoolArg("-LUC"));
    BOOST_CHECK(GetBoolArg("-LUC", false));
    BOOST_CHECK(GetBoolArg("-LUC", true));

    ResetArgs("-LUC=1 -noLUC=1");  // -LUC should win
    BOOST_CHECK(GetBoolArg("-LUC"));
    BOOST_CHECK(GetBoolArg("-LUC", false));
    BOOST_CHECK(GetBoolArg("-LUC", true));

    ResetArgs("-LUC=0 -noLUC=0");  // -LUC should win
    BOOST_CHECK(!GetBoolArg("-LUC"));
    BOOST_CHECK(!GetBoolArg("-LUC", false));
    BOOST_CHECK(!GetBoolArg("-LUC", true));

    // New 0.6 feature: treat -- same as -:
    ResetArgs("--LUC=1");
    BOOST_CHECK(GetBoolArg("-LUC"));
    BOOST_CHECK(GetBoolArg("-LUC", false));
    BOOST_CHECK(GetBoolArg("-LUC", true));

    ResetArgs("--noLUC=1");
    BOOST_CHECK(!GetBoolArg("-LUC"));
    BOOST_CHECK(!GetBoolArg("-LUC", false));
    BOOST_CHECK(!GetBoolArg("-LUC", true));

}

BOOST_AUTO_TEST_CASE(stringarg)
{
    ResetArgs("");
    BOOST_CHECK_EQUAL(GetArg("-LUC", ""), "");
    BOOST_CHECK_EQUAL(GetArg("-LUC", "eleven"), "eleven");

    ResetArgs("-LUC -bar");
    BOOST_CHECK_EQUAL(GetArg("-LUC", ""), "");
    BOOST_CHECK_EQUAL(GetArg("-LUC", "eleven"), "");

    ResetArgs("-LUC=");
    BOOST_CHECK_EQUAL(GetArg("-LUC", ""), "");
    BOOST_CHECK_EQUAL(GetArg("-LUC", "eleven"), "");

    ResetArgs("-LUC=11");
    BOOST_CHECK_EQUAL(GetArg("-LUC", ""), "11");
    BOOST_CHECK_EQUAL(GetArg("-LUC", "eleven"), "11");

    ResetArgs("-LUC=eleven");
    BOOST_CHECK_EQUAL(GetArg("-LUC", ""), "eleven");
    BOOST_CHECK_EQUAL(GetArg("-LUC", "eleven"), "eleven");

}

BOOST_AUTO_TEST_CASE(intarg)
{
    ResetArgs("");
    BOOST_CHECK_EQUAL(GetArg("-LUC", 11), 11);
    BOOST_CHECK_EQUAL(GetArg("-LUC", 0), 0);

    ResetArgs("-LUC -bar");
    BOOST_CHECK_EQUAL(GetArg("-LUC", 11), 0);
    BOOST_CHECK_EQUAL(GetArg("-bar", 11), 0);

    ResetArgs("-LUC=11 -bar=12");
    BOOST_CHECK_EQUAL(GetArg("-LUC", 0), 11);
    BOOST_CHECK_EQUAL(GetArg("-bar", 11), 12);

    ResetArgs("-LUC=NaN -bar=NotANumber");
    BOOST_CHECK_EQUAL(GetArg("-LUC", 1), 0);
    BOOST_CHECK_EQUAL(GetArg("-bar", 11), 0);
}

BOOST_AUTO_TEST_CASE(doubledash)
{
    ResetArgs("--LUC");
    BOOST_CHECK_EQUAL(GetBoolArg("-LUC"), true);

    ResetArgs("--LUC=verbose --bar=1");
    BOOST_CHECK_EQUAL(GetArg("-LUC", ""), "verbose");
    BOOST_CHECK_EQUAL(GetArg("-bar", 0), 1);
}

BOOST_AUTO_TEST_CASE(boolargno)
{
    ResetArgs("-noLUC");
    BOOST_CHECK(!GetBoolArg("-LUC"));
    BOOST_CHECK(!GetBoolArg("-LUC", true));
    BOOST_CHECK(!GetBoolArg("-LUC", false));

    ResetArgs("-noLUC=1");
    BOOST_CHECK(!GetBoolArg("-LUC"));
    BOOST_CHECK(!GetBoolArg("-LUC", true));
    BOOST_CHECK(!GetBoolArg("-LUC", false));

    ResetArgs("-noLUC=0");
    BOOST_CHECK(GetBoolArg("-LUC"));
    BOOST_CHECK(GetBoolArg("-LUC", true));
    BOOST_CHECK(GetBoolArg("-LUC", false));

    ResetArgs("-LUC --noLUC");
    BOOST_CHECK(GetBoolArg("-LUC"));

    ResetArgs("-noLUC -LUC"); // LUC always wins:
    BOOST_CHECK(GetBoolArg("-LUC"));
}

BOOST_AUTO_TEST_SUITE_END()
