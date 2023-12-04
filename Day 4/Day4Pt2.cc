#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

std::vector<std::string> ExtractText() {
  // Function takes each line from text file named input.txt and returns them as
  // a vector.
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
  std::vector<int> number_of_cards{};
  std::vector<int> card_count{};
  for (int i = 0; i < text.size(); i++) {
    card_count.push_back(1);
  }
  int current_card{0};
  for (std::string line : text) {
    int num_of_win{0};
    // Taken from Day 2 code.
    // Isolates text after the first colon (:)
    // In this case, isolates winning numbers and card numbers.
    std::string text_to_search;
    text_to_search = line.substr(line.find(":") + 1);
    std::string winning_numbers{};
    std::map<int, int> occurances;
    std::size_t pos = text_to_search.find("|");
    // pos should never be npos but check just in case.
    if (pos != std::string::npos) {
      winning_numbers = text_to_search.substr(0, pos + 1);
      pos = text_to_search.find(winning_numbers);
      text_to_search.erase(0, winning_numbers.size());
      std::stringstream ss;
      ss << winning_numbers;
      int number;
      while (ss >> number) {
        // Winning numbers don't appear to repeat themselves and the map starts
        // empty. Otherwise check for existence of key before adding value.
        occurances.insert({number, 1});
      }
      ss.clear();
      std::stringstream ss2;
      // Text to search should just be game numbers at this point.
      ss2 << text_to_search;
      while (ss2 >> number) {
        if (occurances.count(number) == 0) {
          occurances.insert({number, 1});
        } else {
          occurances[number]++;
        }
      }
    }
    for (std::map<int, int>::iterator it = occurances.begin();
         it != occurances.end(); it++) {
      if (it->second > 1) {
        num_of_win++;
      }
    }
    number_of_cards.push_back(num_of_win);
  }
  for (int j = 0; j < card_count.size(); j++) {
    for (int i = j+1; i < card_count[j] + 1; i++) {
      number_of_cards[i] += number_of_cards[j];
    }
  }
  int total_cards{0};
  for (int num : number_of_cards) {
    total_cards += num;
  }
  return total_cards;
}

int main(int argc, char const *argv[]) {
  std::vector<std::string> text = ExtractText();
  std::cout << ProcessText(text) << "\n";
  return 0;
}
