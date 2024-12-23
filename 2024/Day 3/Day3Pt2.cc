#include <fstream>
#include <string>
#include <regex>
#include <iostream>

int main()
{
    std::ifstream file("input.txt");
    int total = 0;

    if (file.is_open())
    {
        bool toggle = true;
        std::string line;
        std::regex mul_pattern(R"(mul\((\d+),(\d+)\))");
        std::regex do_pattern(R"(do\(\))");
        std::regex dont_pattern(R"(don't\(\))");

        while (std::getline(file, line))
        {
            std::sregex_iterator it(line.begin(), line.end(), mul_pattern);
            std::sregex_iterator end;
            size_t last_pos = 0;

            while (it != end)
            {
                std::string section = line.substr(last_pos, it->position() - last_pos);
                if (std::regex_search(section, do_pattern))
                {
                    toggle = true;
                }
                else if (std::regex_search(section, dont_pattern))
                {
                    toggle = false;
                }

                if (toggle)
                {
                    int num1 = std::stoi((*it)[1].str());
                    int num2 = std::stoi((*it)[2].str());
                    total += num1 * num2;
                }

                last_pos = it->position() + it->length();
                ++it;
            }

            std::string trailing_section = line.substr(last_pos);
            if (std::regex_search(trailing_section, do_pattern))
            {
                toggle = true;
            }
            else if (std::regex_search(trailing_section, dont_pattern))
            {
                toggle = false;
            }
        }
        file.close();
    }
    else
    {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }

    std::cout << total << '\n';
    return 0;
}
