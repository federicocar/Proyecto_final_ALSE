#ifndef _SENSOR_H
#define _SENSOR_H
#include <bits/stdc++.h>

using namespace std;

class sensor{
    int tipo;
    public:
    sensor (int t){tipo = t;}
    float get_med();
};


#endif 