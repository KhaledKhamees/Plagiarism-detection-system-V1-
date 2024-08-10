#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>
#include <unordered_set>

using namespace std;

// Tokenize
vector<string> tokenize(const string& text) {
    vector<string> tokens;
    stringstream ss(text);
    string word;
    while (ss >> word) {
        word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());
        tokens.push_back(word);
    }
    return tokens;
}

// Normalization
string normalize(const string& token) {
    string normalized = token;
    transform(normalized.begin(), normalized.end(), normalized.begin(), ::tolower);
    return normalized;
}

// Shingling
unordered_set<string> createShingles(const vector<string>& tokens, int k) {
    unordered_set<string> shingles;
    if (tokens.size() < k) return shingles; // Ensure enough tokens for shingling

    for (size_t i = 0; i <= tokens.size() - k; ++i) {
        string shingle = "";
        for (int j = 0; j < k; ++j) {
            shingle += tokens[i + j] + " ";
        }
        shingles.insert(shingle);
    }
    return shingles;
}

// Jaccard Similarity Calculation
double Jaccardcalculator(const unordered_set<string>& shingles1, const unordered_set<string>& shingles2) {
    int intersectionSize = 0;
    for (const auto& shingle : shingles1) {
        if (shingles2.find(shingle) != shingles2.end()) {
            intersectionSize++;
        }
    }
    int unionSize = shingles1.size() + shingles2.size() - intersectionSize;
    return static_cast<double>(intersectionSize) / unionSize;
}

int main() {
    string text1, text2;
    cout << "Enter TEXT 1 \n";
    getline(cin, text1);
    cout << "Enter TEXT 2 \n";
    getline(cin, text2);

    // Tokenize
    auto tokens1 = tokenize(text1);
    auto tokens2 = tokenize(text2);

    // Normalize
    for (auto& token : tokens1) {
        token = normalize(token);
    }
    for (auto& token : tokens2) {
        token = normalize(token);
    }

    // Create shingles
    auto shingles1 = createShingles(tokens1, 2);
    auto shingles2 = createShingles(tokens2, 2);

    // Calculate Jaccard Similarity
    double jaccardSimilarity = Jaccardcalculator(shingles1, shingles2);

    cout << "Jaccard Similarity = " << jaccardSimilarity << endl;
    cout << " (1 = identical, 0 = completely different)" << endl;

    return 0;
}
