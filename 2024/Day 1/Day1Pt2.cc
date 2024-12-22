#include <algorithm>
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main (){
    std::ifstream file;
    std::map<int,int> col1{};
    std::map<int,int> col2{};
    file.open("input.txt");
    if(file.is_open()){
        std::string line;
        while(std::getline(file,line)){
            std::istringstream iss(line);
            int num1, num2;
            if(iss >> num1 >> num2){
                col1[num1]++;
                col2[num2]++;
            }
        }
        file.close();
    }
    int sim_score = 0;
    for(auto pair: col1){
        sim_score += (pair.first * pair.second * col2[pair.first]);
    }

    std::cout << sim_score << '\n';
}