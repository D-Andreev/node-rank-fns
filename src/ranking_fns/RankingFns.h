#ifndef NODE_RANK_FNS_RANKINGFNS_H
#define NODE_RANK_FNS_RANKINGFNS_H


class RankingFns {
public:
    std::vector<double> GetTfIdf(std::vector<std::string> &documents, std::vector<std::string> &terms);
    std::vector<double> GetBM25(std::vector<std::string> &documents, std::vector<std::string> &terms);
private:
    static std::vector<std::string> SplitString(const std::string &str);
    static double GetTermFrequency(std::vector<std::string> &document, std::vector<std::string> &terms);
    static double GetDocumentFrequency(std::vector<std::string> &docs, std::vector<std::string> &terms);
};


#endif //NODE_RANK_FNS_RANKINGFNS_H
