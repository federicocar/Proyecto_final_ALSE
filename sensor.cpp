#include "sensor.h"
#include <bits/stdc++.h>

using namespace std;

float sensor::get_med(){
    if(tipo == 1){
        int range = 45 - 10 + 1;
        float num = rand() % range;
        return num;
    }
    else if(tipo == 2){
        int range = 100 - 0 + 1;
        float num = rand() % range;
        return num;
    }
    else if(tipo == 3){
        int range = 100 - 0 + 1;
        float num = rand() % range;
        return num;
    }
    else if(tipo == 4){
        int range = 40 - 0 + 1;
        float num = rand() % range;
        return num;
    }
    else if(tipo == 5){
        float num = rand() % 360 + (-180);
        return num;
    }
    else if(tipo == 6){
        int range = 200 - 0 + 1;
        float num = rand() % range;
        return num;
    }
    else if(tipo == 7){
        int range = 4000 - 0 + 1;
        float num = rand() % range;
        return num;
    }

}