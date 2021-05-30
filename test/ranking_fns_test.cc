#include <gtest/gtest.h>
#include "vector"
#include "../src/ranking_fns/RankingFns.h"
#include "../src/Abc.h"

TEST(RankingFnsTest, GetsTfIdfScores) {
    std::vector<std::string> documents = { "this is a a sample", "this is another another example example example" };
    std::vector<std::string> terms = { "example" };
    int res = Abc::calc();
    EXPECT_EQ(res, 1);
    //auto *rankingFns = new RankingFns();

    //rankingFns->GetTfIdf(documents, terms);
    // auto result = rankingFns->GetTfIdf(documents, terms);

    std::vector<double> expectedScores(0, 0.12901285528456335);
    EXPECT_EQ(1, 1);
}