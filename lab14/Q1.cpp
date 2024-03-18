#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

class Mapper {
public:
    std::vector<std::pair<std::string, int>> map(const std::string& line) {
        std::vector<std::pair<std::string, int>> pairs;
        std::string word;
        for (char c : line) {
            if (std::isalpha(c)) {
                word += std::tolower(c);
            } else if (!word.empty()) {
                pairs.push_back({word, 1});
                word.clear();
            }
        }
        if (!word.empty()) {
            pairs.push_back({word, 1});
        }
        return pairs;
    }
};

class Reducer {
public:
    std::vector<std::pair<std::string, int>> reduce(const std::vector<std::pair<std::string, int>>& pairs) {
        std::vector<std::pair<std::string, int>> counts;
        for (const auto& pair : pairs) {
            auto it = std::find_if(counts.begin(), counts.end(), [&](const auto& count) {
                return count.first == pair.first;
            });
            if (it != counts.end()) {
                it->second += pair.second;
            } else {
                counts.push_back(pair);
            }
        }
        return counts;
    }
};

int main() {
    std::string filename;
    std::cout << "Enter the name of the text file: ";
    std::cin >> filename;

    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file." << std::endl;
        return 0;
    }

    std::vector<std::pair<std::string, int>> pairs;
    std::string line;
    Mapper mapper;
    while (std::getline(file, line)) {
        auto mappedPairs = mapper.map(line);
        pairs.insert(pairs.end(), mappedPairs.begin(), mappedPairs.end());
    }

    std::sort(pairs.begin(), pairs.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;
    });

    Reducer reducer;
    auto counts = reducer.reduce(pairs);

    std::string outputFilename = filename + "_mr.txt";
    std::ofstream outputFile(outputFilename);
    if (!outputFile) {
        std::cerr << "Error creating output file." << std::endl;
        return 0;
    }

    for (const auto& count : counts) {
        std::cout << count.first << " " << count.second << std::endl;
        outputFile << count.first << " " << count.second << std::endl;
    }

    std::cout << "Word count results saved to " << outputFilename << std::endl;

    return 0;
}

