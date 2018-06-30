#ifndef LIFE_H
#define LIFE_H

#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <string>
#include <cmath>

class Life{
private:
    int dim;

    std::vector<std::vector<bool> > world;


    bool getAdjCell(int x, int y, int dir);

public:
    bool wrap;
    std::vector<bool> stasisRules;
    std::vector<bool> lifeRules;
    Life();
    Life(int d, bool w);

    bool getCell(int x, int y);
    int getDim();
    bool getRefreshedCell(int x, int y);
    void modCell(int x, int y, bool live);
    void refreshWorld();
    void clearWorld();
    void simWorld(int n);
    void changeStasisRule(int,bool);
    void changeLifeRule(int,bool);

};

#endif
