#include "mediciones.h"
#include "sensor.h"
#include <bits/stdc++.h>
using namespace std;

mediciones::mediciones(){
    for(int i = 0; i<7; i++){
        sensor tem(i+1);
        tipos.push_back(tem);
        vector <float> tempo;
        med.push_back(tempo);
    }
}

void mediciones::hacer_mediciones(){
    for(int i = 0; i < 7; i++){
        med[i].push_back(tipos[i].get_med());
    }   
}

vector <float> mediciones::get_min(){
    vector <float> minimos;
    for(int i = 0; i < 7; i++){
        float min_ = 400000000;
        for(int j = 0; j < med[i].size(); j++){
            if (med[i][j] < min_){
                min_ = med[i][j];
            }
        }
        minimos.push_back(min_);
    }
    return minimos;
}
vector <float> mediciones::get_max(){
    vector <float> maximos;
    for(int i = 0; i < 7; i++){
        float max_ = -800;
        for(int j = 0; j < med[i].size(); j++){
            if (med[i][j] > max_){
                max_ = med[i][j];
            }
        }
        maximos.push_back(max_);
    }
    return maximos;

}
vector <float> mediciones::get_prom(){
    vector <float> promedios;
    for(int i = 0; i < 7; i++){
        float prome = 0;
        for(int j = 0; j < med[i].size(); j++){
            prome += med[i][j];
        }
        promedios.push_back(prome/med[i].size());
    }
    return promedios;
}
void mediciones::eliminar(){
    for(int i = 0; i<7 ; i++){
        med[i].erase(med[i].begin(), med[i].end());
    }
}