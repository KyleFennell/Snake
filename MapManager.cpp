#include "MapManager.h"
#include <fstream>
#include <iostream>

void MapManager::loadMaps(){

    std::string line;
    std::ifstream file ("maps.txt");
    if (file.is_open()){
        std::cout << "file opened" << std::endl;
        while ( getline(file, line) ){
            if (line.compare("begin") == 0){
                getline(file, line);
                std::string name = line;
                std::cout << name << std::endl;
                getline(file, line);
                std::vector<std::vector<int>> mapData;
                while (line.compare("end") != 0){
                    std::vector<int> row;
                    for (int i = 0; i < (int)line.size(); i += 2){
                        row.push_back(stoi(line.substr(i,1)));
                    }
                    mapData.push_back(row);
                    getline(file, line);
                }
                add(name, mapData);
                std::cout << name << " added" << std::endl;
            }
        }
        file.close();
        std::cout << "file closed" << std::endl;
    }
    else{
        std::cout << "Unable to open file";
    }
}

void MapManager::add(std::string name, std::vector<std::vector<int>> map){
    _maps.push_back(Map(name, map));
}
