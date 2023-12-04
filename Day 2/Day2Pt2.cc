#include <fstream>
#include <iostream>
#include <vector>

std::vector<std::string> ExtractText() {
  std::fstream infile;
  std::vector<std::string> input_lines;
  infile.open("input.txt");
  if (infile.is_open()) {
    std::string text;
    while (getline(infile, text)) {
      input_lines.push_back(text);
    }
  }
  return input_lines;
}

int ProcessText(std::vector<std::string> text) {
  int answer{0};
  for (std::string line : text) {
    std::string text_to_search;
    text_to_search = line.substr(line.find(":") + 1);
    bool valid_game{true};
    int red_num{0};
    int blue_num{0};
    int green_num{0};
    while (text_to_search.size() > 0) {
      std::string round{};
      std::size_t pos = text_to_search.find(";");
      if (pos != std::string::npos) {
        round = text_to_search.substr(0, pos + 1);
        pos = text_to_search.find(round);
        text_to_search.erase(pos, round.size());
      } else {
        round = text_to_search;
        text_to_search.clear();
      }
      std::string red;
      std::size_t color_pos = round.find("red");
      if (color_pos != std::string::npos) {
        red = round.substr(color_pos - 3, 3);
        if (red_num < std::stoi(red)) {
          red_num = std::stoi(red);
        }
      }
      std::string blue;
      color_pos = round.find("blue");
      if (color_pos != std::string::npos) {
        blue = round.substr(color_pos - 3, 3);
        if (blue_num < std::stoi(blue)) {
          blue_num = std::stoi(blue);
        }
      }
      std::string green;
      color_pos = round.find("green");
      if (color_pos != std::string::npos) {
        green = round.substr(color_pos - 3, 3);
        if (green_num < std::stoi(green)) {
          green_num = std::stoi(green);
        }
      }
    }
    if (red_num == 0){
      red_num = 1;
    }
    if (blue_num == 0){
      blue_num = 1;
    }
    if (green_num == 0) {
      green_num = 1;
    }
    answer += (red_num * blue_num * green_num);
  }
  return answer;
}

int main() { std::cout << ProcessText(ExtractText()) << "\n"; }