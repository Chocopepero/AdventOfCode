#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <regex>
#include <iostream>

int main() {
    std::ifstream file("input.txt");
    std::vector<std::pair<int, int>> numbers;
    if (file.is_open()) {
        std::string line;
        std::regex pattern(R"(mul\((\d+),(\d+)\))");

        while (std::getline(file, line)) {
            auto matches_begin = std::sregex_iterator(line.begin(), line.end(), pattern);
            auto matches_end = std::sregex_iterator();

            for (std::sregex_iterator i = matches_begin; i != matches_end; ++i) {
                std::smatch match = *i;
                int num1 = std::stoi(match[1].str());
                int num2 = std::stoi(match[2].str());
                numbers.emplace_back(num1, num2);
            }
        }
        file.close();
    } else {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }

    int total = 0;
    for (const auto& [num1, num2] : numbers) {
        total += num1 * num2;
    }

    std::cout << total << '\n';
    return 0;
}