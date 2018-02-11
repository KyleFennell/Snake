#pragma once
#include <string>
#include <vector>

class Map{
public:

    Map(std::string name, std::vector<std::vector<int>> map){ _name = name; _map = map; }
    std::vector<std::vector<int>> map(){ return _map; }
    int height() { return (int)_map.size(); }
    int width() { return (int)_map[0].size(); }
    std::string name() { return _name; }

private:

    std::vector<std::vector<int>> _map;
    std::string _name;

};

class MapManager{
public:

    void loadMaps();
    int mapCount(){ return (int)_maps.size(); }
    Map getMap(int i) { return _maps[i]; }
    void add(std::string name, std::vector<std::vector<int>> map);

private:

    std::vector<Map> _maps;
    int _crntMap;

};
