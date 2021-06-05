#include <gtest/gtest.h>
#include "vector"
#include "../src/ranking_fns/RankingFns.h"

TEST(RankingFnsTest, GetsTfIdfScores) {
    std::vector<std::string> documents = { "this is a a sample", "this is another another example example example" };
    std::vector<std::string> terms = { "example" };
    auto *rankingFns = new RankingFns();

    auto result = rankingFns->GetTfIdf(documents, terms);

    std::vector<double> expectedScores{0, 0.12901285528456335};
    for (auto i = 0; i < result.size(); i++) {
        EXPECT_EQ(result[i], expectedScores[i]);
    }
}

TEST(RankingFnsTest, GetBM25Scores) {
    std::vector<std::string> documents = { "this is a a sample", "this is another another example example example" };
    std::vector<std::string> terms = { "example" };
    auto *rankingFns = new RankingFns();

    auto result = rankingFns->GetBM25(documents, terms);

    std::vector<double> expectedScores{0, 0.07811157572119272};
    for (auto i = 0; i < result.size(); i++) {
        EXPECT_EQ(result[i], expectedScores[i]);
    }
}