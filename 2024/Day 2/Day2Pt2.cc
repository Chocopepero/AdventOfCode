#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>

bool isValidSequence(const std::vector<int>& vec) {
    if (vec.size() < 2) return false;

    bool increasing = vec[1] > vec[0];
    for (size_t i = 1; i < vec.size(); ++i) {
        int diff = std::abs(vec[i] - vec[i - 1]);
        if (diff < 1 || diff > 3) {
            return false;
        }
        if ((increasing && vec[i] < vec[i - 1]) || (!increasing && vec[i] > vec[i - 1])) {
            return false;
        }
    }
    return true;
}

bool testVector(const std::vector<int>& vec) {
    if (isValidSequence(vec)) {
        return true;
    }

    for (size_t i = 0; i < vec.size(); ++i) {
        std::vector<int> modifiedVec = vec;
        modifiedVec.erase(modifiedVec.begin() + i);
        if (isValidSequence(modifiedVec)) {
            return true;
        }
    }

    return false;
}

int main() {
    std::ifstream file("input.txt");
    int safe = 0;
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::vector<int> row;
            std::istringstream iss(line);
            int num;
            while (iss >> num) {
                row.push_back(num);
            }
            if (testVector(row)) {
                safe++;
            }
        }
        file.close();
    } else {
        std::cerr << "Unable to open file" << std::endl;
    }
    std::cout << safe << '\n';
    return 0;
}