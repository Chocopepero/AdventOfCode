#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

int main (){
    std::ifstream file;
    std::vector<int> col1{};
    std::vector<int> col2{};
    file.open("input.txt");
    if(file.is_open()){
        std::string line;
        while(std::getline(file,line)){
            std::istringstream iss(line);
            int num1, num2;
            if(iss >> num1 >> num2){
                col1.push_back(num1);
                col2.push_back(num2);
            }
        }
        file.close();
    }
    std::sort(col1.begin(), col1.end());
    std::sort(col2.begin(), col2.end());
    int sum = 0;
    for(int i = 0; i < col1.size(); i++){
        sum += std::abs(col1[i] - col2[i]);
    }
    std::cout << sum << '\n';
}