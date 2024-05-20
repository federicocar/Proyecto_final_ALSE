#ifndef _MEDICIONES_H
#define _MEDICIONES_H
#include <bits/stdc++.h>
#include "sensor.h"

using namespace std;
class mediciones{
    vector <sensor> tipos;
    vector <vector<float>> med;
    public:
    mediciones();
    void hacer_mediciones();
    vector <float> get_min();
    vector <float> get_max();
    vector <float> get_prom();
    void eliminar();
};


#endif

