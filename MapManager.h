#pragma once
#include <string>
#include <vector>
#include "Point.h"

class PowerupSpawn{
public:

    PowerupSpawn(Point pos, int type){
        _pos = pos;
        _type = type;
        c_respawnTime = -1;
    }
    void resetRespawnTime(){ c_respawnTime = _respawnTime; }

    bool update(){
        if (c_respawnTime == 0){
            c_respawnTime--;
            return true;
        }
        else if (c_respawnTime > 0){
            c_respawnTime--;
        }
        return false;
    }

    Point pos(){ return _pos; }
    int type(){ return _type; }

private:

    Point _pos;
    int _type;
    int _respawnTime = 600;
    int c_respawnTime;
};

class Map{
public:

    Map(std::string name, std::vector<std::vector<int>> map, std::vector<Point> playerSpawn, std::vector<PowerupSpawn*> powerupSpawn){
        _name = name;
        _mapData = map;
        spawn_Player = playerSpawn;
        spawn_Powerup = powerupSpawn;
    }
    std::vector<std::vector<int>> map(){ return _mapData; }
    std::vector<Point> playerSpawns(){ return spawn_Player; }
    std::vector<PowerupSpawn*> powerupSpawns(){ return spawn_Powerup; }
    int height() { return (int)_mapData.size(); }
    int width() { return (int)_mapData[0].size(); }
    std::string name() { return _name; }

private:

    std::vector<std::vector<int>> _mapData;
    std::string _name;
    std::vector<Point> spawn_Player;
    std::vector<PowerupSpawn*> spawn_Powerup;

};

class MapManager{
public:

    void loadMaps();
    int mapCount(){ return (int)_maps.size(); }
    Map* getMap(int i) { return _maps[i]; }
    void add(std::string name, std::vector<std::vector<int>> map, std::vector<Point> playerSpawn, std::vector<PowerupSpawn*> powerupSpawn){
         _maps.push_back(new Map(name, map, playerSpawn, powerupSpawn));
    }

private:

    std::vector<std::string> split(std::string in, char del);
    std::vector<Map*> _maps;
    int _crntMap;

};
