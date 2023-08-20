#include "MarkovManager.h"
#include <iostream>

int levenshteinDistance(const state_sequence str1, const state_sequence str2);
double similarityPercentage(const state_sequence sequence1, const state_sequence sequence2);


int main()
{
    MarkovManager mm{};
    state_sequence sequence1 = {
            "F", "E", "A", "D", "D", "A#", "C",
            "F", "C", "D", "G", "A#", "F", "F",
            "E", "A", "D", "D", "A#", "C", "F",
            "C", "D", "G", "A#", "F", "A", "A",
            "D", "C", "A#", "D", "G", "C", "F",
            "A", "A", "D", "C", "A#", "D", "G",
            "C", "F", "F", "F", "E", "A", "D",
            "D", "A#", "C", "F", "C", "D", "G",
            "A#", "F", "A", "A", "D", "C", "A#",
            "D", "G", "C", "F", "A", "A", "D",
            "C", "A#", "D", "G", "C", "F", "F",
            "F", "E", "A", "D", "D", "A#", "C",
            "F", "C", "D", "G", "A#", "F", "A",
            "A", "D", "C", "A#", "D", "G", "C",
            "F", "A", "A", "D", "C", "A#", "D",
            "G", "C", "F", "F", "F", "E", "A",
            "D", "D", "A#", "C", "F", "C", "D",
            "G", "A#", "F", "G", "A#", "F"
    };

    // Iterate through the sequence and call mm.putEvent() for each note
    for (const auto& note : sequence1) {
        mm.putEvent(note);
    }



    // std::cout << mm.getModelAsString();
    mm.setMaxOrder(20);
    state_sequence sequence;
    sequence.emplace_back("C");
    // std::cout << mm.getModelAsString();

    for (auto i=0;i<6;++i){
        sequence.push_back(mm.getEvent(sequence));
        std::cout << "Next state " << sequence[i] << std::endl;
    }


    double similarity1_2 = similarityPercentage(sequence1, sequence);

    std::cout << "Similarity between sequence1 and sequence2: " << similarity1_2 << "%" << std::endl;

}

std::vector<std::string> longestCommonSubsequence(const state_sequence sequence1, const state_sequence sequence2) {
    const int len1 = sequence1.size();
    const int len2 = sequence2.size();

    std::vector<std::vector<int>> dp(len1 + 1, std::vector<int>(len2 + 1, 0));

    for (int i = 1; i <= len1; ++i) {
        for (int j = 1; j <= len2; ++j) {
            if (sequence1[i - 1] == sequence2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    std::vector<std::string> lcs;
    int i = len1, j = len2;
    while (i > 0 && j > 0) {
        if (sequence1[i - 1] == sequence2[j - 1]) {
            lcs.push_back(sequence1[i - 1]);
            --i;
            --j;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            --i;
        } else {
            --j;
        }
    }

    std::reverse(lcs.begin(), lcs.end());
    return lcs;
}

// Function to calculate the similarity percentage
double similarityPercentage(const state_sequence sequence1, const state_sequence sequence2) {
    const int len1 = sequence1.size();
    const int len2 = sequence2.size();

    // Calculate the longest common subsequence
    std::vector<std::string> lcs = longestCommonSubsequence(sequence1, sequence2);

    // Calculate the percentage similarity
    double similarity = static_cast<double>(lcs.size()) / std::max(len1, len2);

    return similarity * 100.0;
}
