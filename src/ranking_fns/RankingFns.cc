#include "vector"
#include "string"
#include "math.h"
#include "RankingFns.h"

std::vector<double> RankingFns::GetTfIdf(std::vector<std::string> &documents, std::vector<std::string> &terms) {
    double df = RankingFns::GetDocumentFrequency(documents, terms);
    std::vector<double> scores;
    for (auto i = 0; i < documents.size(); i++) {
        auto doc = documents[i];
        auto words = RankingFns::SplitString(doc);
        double tf = RankingFns::GetTermFrequency(words, terms);
        double idf = log10((double)documents.size() / df);
        scores.push_back(abs(tf * idf));
    }

    return scores;
}

double RankingFns::GetDocumentFrequency(std::vector<std::string> &docs, std::vector<std::string> &terms) {
    double df = 0;
    for (auto & doc : docs) {
        auto words = RankingFns::SplitString(doc);
        bool termExists = false;
        for (auto & term : terms) {
            for (auto & word : words) {
                if (term == word) {
                    termExists = true;
                    break;
                }
            }
            if (termExists) break;
        }
        if (termExists) {
            df++;
        }
    }

    return df;
}

std::vector<std::string> RankingFns::SplitString(const std::string& str) {
    std::vector<std::string> res;
    std::string tmp;
    for (char i : str) {
        if (i == ' ') {
            res.push_back(tmp);
            tmp = "";
            continue;
        }

        tmp.push_back(i);
    }
    res.push_back(tmp);

    return res;
}

double RankingFns::GetTermFrequency(std::vector<std::string> &document, std::vector<std::string> &terms) {
    double tfSum = 0;
    for (auto & term : terms) {
        double tf = 0;
        for (auto & word : document) {
            if (term == word) {
                tf++;
            }
        }
        tfSum += tf / document.size();
    }

    return tfSum;
}

std::vector<double> RankingFns::GetBM25(std::vector<std::string> &documents, std::vector<std::string> &terms) {
    double df = this->GetDocumentFrequency(documents, terms);
    std::vector<double> scores;
    int documentLengthSum = 0;
    int n = documents.size();
    for (auto & document : documents) {
        documentLengthSum += document.size();
    }
    double averageDocumentLength = (double)documentLengthSum / n;
    double k = 1;
    double b = 0.5;
    for (const auto& doc : documents) {
        double documentLength = doc.size();
        auto words = this->SplitString(doc);
        double tf = this->GetTermFrequency(words, terms);
        // Fancy tf accounts for term saturation and document length.
        double fancyTf = tf / (tf + k * (1 - b + b * documentLength / averageDocumentLength));
        // Fancy (not so fancy) idf considers less a term if it's in most of the documents.
        double fancyIdf = log10(1 + (n - df + .5) / (df + .5));
        scores.push_back(abs(fancyTf * fancyIdf));
    }

    return scores;
}