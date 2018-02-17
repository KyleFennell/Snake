#include "MapManager.h"
#include <fstream>
#include <iostream>

void MapManager::loadMaps(){

    std::string line;
    std::ifstream file ("maps.txt");
    if (file.is_open()){
//        std::cout << "file opened" << std::endl;
        while ( getline(file, line) ){
            if (line.compare("begin") == 0){
                getline(file, line);
                std::string name = line;
//                std::cout << name << std::endl;
                getline(file, line);
                std::vector<std::vector<int>> mapData;
                while (line.compare("players") != 0){
                    std::vector<std::string> splitLine = split(line, ' ');
                    std::vector<int> intLine;
                    for (int i = 0; i < (int)splitLine.size(); i++){
                        intLine.push_back(stoi(splitLine[i]));
                    }
                    mapData.push_back(intLine);
                    getline(file, line);
                }
//                std::cout << "map loaded" << std::endl;
                getline(file, line);
                std::vector<Point> player;
                while (line.compare("powerups") != 0){
                    std::vector<std::string> splitLine = split(line, ' ');
                    player.push_back(Point(stoi(splitLine[0]), stoi(splitLine[1])));
                    getline(file, line);
                }
//                std::cout << "players loaded" << std::endl;
                getline(file, line);
                std::vector<PowerupSpawn> powerup;
                while (line.compare("end") != 0){
                    std::vector<std::string> splitLine = split(line, ' ');
                    powerup.push_back(PowerupSpawn(Point(stoi(splitLine[0]), stoi(splitLine[1])), stoi(splitLine[2])));
                    getline(file, line);
                }
//                std::cout << "powerup loaded" << std::endl;
                add(name, mapData, player, powerup);
//                std::cout << name << " added" << std::endl;
            }
        }
        file.close();
        std::cout << "Maps Loaded..." << std::endl;
    }
    else{
        std::cout << "Unable to open file";
    }
}

std::vector<std::string> MapManager::split(std::string in, char del){
    std::vector<std::string> out;
    std::string s;
//    std::cout << in << std::endl;
    for (int i = 0; i < (int)in.size(); i++){
//        std::cout << in[i] << std::endl;
        if (in[i] != del){
            s += in[i];
        }
        else{
//            std::cout << s << std::endl;
            out.push_back(s);
            s = "";
        }
    }
    out.push_back(s);
    return out;
}
