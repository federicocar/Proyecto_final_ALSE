#include "mediciones.h"
#include "sensor.h"
#include <bits/stdc++.h>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include <thread>
#include <chrono>
#include <ctime>
 
using namespace std;
int main(int argc, char** argv){
   string sql, sql1, sql2, sql3 ;
   string sql4, sql5, sql6, sql7 ;
    if(argc != 3){
        cout << "El programa se usa así:" << endl;
        cout << "proy_final db_name periodo_datos" << endl;
        return 1;
    }
    sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   string sqlstr;
 
   /* Open database */
   char* pr_name = argv[1];
   rc = sqlite3_open(pr_name, &db);
   
   if( rc != 0 ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(1);
   } else {
      fprintf(stdout, "Opened database successfully\n");
   }
 
   /* Create SQL statement */
   sqlstr = "CREATE TABLE IF NOT EXISTS info_tablap(trans REAL PRIMARY KEY NOT NULL," \
      "Fecha TEXT NOT NULL," \
      "Hora_i TEXT NOT NULL);";
 
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sqlstr.c_str(), 0, 0, &zErrMsg);
   
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      return (2);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }
 
   /* Create SQL statement */
   sqlstr = "CREATE TABLE IF NOT EXISTS tabla_sensort(trans REAL NOT NULL," \
      "minimo REAL NOT NULL," \
      "maximo REAL NOT NULL, prom REAL NOT NULL,"\
       "FOREIGN KEY (trans) REFERENCES info_tablap(trans));";
    rc = sqlite3_exec(db, sqlstr.c_str(), 0, 0, &zErrMsg);
 
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      return (3);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }
 
   /* Create SQL statement */
   sqlstr = "CREATE TABLE IF NOT EXISTS tabla_sensorh(trans REAL NOT NULL," \
      "minimo REAL NOT NULL," \
      "maximo REAL NOT NULL, prom REAL NOT NULL,"\
       "FOREIGN KEY (trans) REFERENCES info_tablap(trans));";
   
    rc = sqlite3_exec(db, sqlstr.c_str(), 0, 0, &zErrMsg);
 
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      return (3);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }
 
   /* Create SQL statement */
   sqlstr = "CREATE TABLE IF NOT EXISTS tabla_sensorhs(trans REAL NOT NULL," \
      "minimo REAL NOT NULL," \
      "maximo REAL NOT NULL, prom REAL NOT NULL,"\
       "FOREIGN KEY (trans) REFERENCES info_tablap(trans));";
   
    rc = sqlite3_exec(db, sqlstr.c_str(), 0, 0, &zErrMsg);
 
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      return (3);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }
   
      /* Create SQL statement */
   sqlstr = "CREATE TABLE IF NOT EXISTS tabla_sensorv(trans REAL NOT NULL," \
      "minimo REAL NOT NULL," \
      "maximo REAL NOT NULL, prom REAL NOT NULL,"\
       "FOREIGN KEY (trans) REFERENCES info_tablap(trans));";
   
    rc = sqlite3_exec(db, sqlstr.c_str(), 0, 0, &zErrMsg);
 
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      return (3);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }
 
         /* Create SQL statement */
   sqlstr = "CREATE TABLE IF NOT EXISTS tabla_sensordv(trans REAL NOT NULL," \
      "minimo REAL NOT NULL," \
      "maximo REAL NOT NULL, prom REAL NOT NULL,"\
       "FOREIGN KEY (trans) REFERENCES info_tablap(trans));";
   
    rc = sqlite3_exec(db, sqlstr.c_str(), 0, 0, &zErrMsg);
 
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      return (3);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }
 
         /* Create SQL statement */
   sqlstr = "CREATE TABLE IF NOT EXISTS tabla_sensorp(trans REAL NOT NULL," \
      "minimo REAL NOT NULL," \
      "maximo REAL NOT NULL, prom REAL NOT NULL,"\
       "FOREIGN KEY (trans) REFERENCES info_tablap(trans));";
   
    rc = sqlite3_exec(db, sqlstr.c_str(), 0, 0, &zErrMsg);
 
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      return (3);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }
   
         /* Create SQL statement */
   sqlstr = "CREATE TABLE IF NOT EXISTS tabla_sensori(trans REAL NOT NULL," \
      "minimo REAL NOT NULL," \
      "maximo REAL NOT NULL, prom REAL NOT NULL,"\
       "FOREIGN KEY (trans) REFERENCES info_tablap(trans));";
   
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sqlstr.c_str(), 0, 0, &zErrMsg);
 
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      return (3);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }
    float periodo = atof(argv[2]);
    cout<<periodo<<endl;
    mediciones principal;
    time_t inicio = time(0);
    time_t ciclo_based = time(0);
    time_t now = time(0);
    float trans = now - inicio;
    int cont = 1;
    while (true) {
        now = time(0);
        trans = now - inicio;
        if(trans >= periodo*cont){
            principal.hacer_mediciones();
            cont ++;

            if(now - ciclo_based >= 60){
                string trans_ = to_string(trans);
                tm *ltm = localtime(&now);
                ciclo_based = time(0);
                vector <float> maximo,minimo,promedio;
                maximo = principal.get_max();
                minimo = principal.get_min();
                promedio = principal.get_prom();
                principal.eliminar();
                string fecha = to_string(ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon)+"/"+ to_string(1900 + ltm->tm_year) ;
                string hora_i = to_string(ltm->tm_hour)+ ":"+to_string(ltm->tm_min)+":"+to_string(ltm->tm_sec);
                sql = "INSERT INTO info_tablap (trans, fecha, hora_i) "  \
                "VALUES (" + trans_ + ", '" + fecha + "','"+ hora_i+"'); " ;
 
               
                rc = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);
                 if( rc != SQLITE_OK ){
                 fprintf(stderr, "SQL error: %s\n", zErrMsg);
                sqlite3_free(zErrMsg);
                } else {
                fprintf(stdout, "Records created successfully\n");
                }
 
 
               string minimo_ = to_string(minimo[0]);
               string maximo_ = to_string(maximo[0]);
               string prom_ = to_string(promedio[0]);
               
               sql1 = "INSERT INTO tabla_sensort (trans, minimo, maximo,prom) "  \
               "VALUES (" + trans_ + ", " + minimo_ + ","+ maximo_ +", "+ prom_ +"); " ;
 
                rc = sqlite3_exec(db, sql1.c_str(), 0, 0, &zErrMsg);
                 if( rc != SQLITE_OK ){
                 fprintf(stderr, "SQL error: %s\n", zErrMsg);
                sqlite3_free(zErrMsg);
                } else {
                fprintf(stdout, "Records created successfully\n");
                }
 
               minimo_ = to_string(minimo[1]);
               maximo_ = to_string(maximo[1]);
               prom_ = to_string(promedio[1]);
               sql2 = "INSERT INTO tabla_sensorh (trans, minimo, maximo,prom) "  \
               "VALUES (" + trans_ + ", " + minimo_ + ","+ maximo_ +", "+ prom_+"); " ;
 
                rc = sqlite3_exec(db, sql2.c_str(), 0, 0, &zErrMsg);
                 if( rc != SQLITE_OK ){
                 fprintf(stderr, "SQL error: %s\n", zErrMsg);
                sqlite3_free(zErrMsg);
                } else {
                fprintf(stdout, "Records created successfully\n");
                }
 
               minimo_ = to_string(minimo[2]);
               maximo_ = to_string(maximo[2]);
               prom_ = to_string(promedio[2]);
               sql3 = "INSERT INTO tabla_sensorhs(trans, minimo, maximo,prom) "  \
               "VALUES (" + trans_ + ", " + minimo_ + ","+ maximo_+", "+prom_+"); " ;
 
                rc = sqlite3_exec(db, sql3.c_str(), 0, 0, &zErrMsg);
                 if( rc != SQLITE_OK ){
                 fprintf(stderr, "SQL error: %s\n", zErrMsg);
                sqlite3_free(zErrMsg);
                } else {
                fprintf(stdout, "Records created successfully\n");
                }
 
               minimo_ = to_string(minimo[3]);
               maximo_ = to_string(maximo[3]);
               prom_ = to_string(promedio[3]);
               sql4 = "INSERT INTO tabla_sensorv (trans, minimo, maximo,prom) "  \
               "VALUES (" + trans_ + ", " + minimo_ + ","+ maximo_+", "+prom_+"); " ;
 
                rc = sqlite3_exec(db, sql4.c_str(), 0, 0, &zErrMsg);
                 if( rc != SQLITE_OK ){
                 fprintf(stderr, "SQL error: %s\n", zErrMsg);
                sqlite3_free(zErrMsg);
                } else {
                fprintf(stdout, "Records created successfully\n");
                }
 
               minimo_ = to_string(minimo[4]);
               maximo_ = to_string(maximo[4]);
               prom_ = to_string(promedio[4]);
               sql5 = "INSERT INTO tabla_sensordv(trans, minimo, maximo,prom) "  \
               "VALUES (" + trans_ + ", " + minimo_ + ","+ maximo_+", "+prom_+"); " ;
 
                rc = sqlite3_exec(db, sql5.c_str(), 0, 0, &zErrMsg);
                 if( rc != SQLITE_OK ){
                 fprintf(stderr, "SQL error: %s\n", zErrMsg);
                sqlite3_free(zErrMsg);
                } else {
                fprintf(stdout, "Records created successfully\n");
                }
 
               minimo_ = to_string(minimo[5]);
               maximo_ = to_string(maximo[5]);
               prom_ = to_string(promedio[5]);
               sql6 = "INSERT INTO tabla_sensorp(trans, minimo, maximo,prom) "  \
               "VALUES (" + trans_ + ", " + minimo_ + ","+ maximo_+", "+prom_+"); " ;
 
                rc = sqlite3_exec(db, sql6.c_str(), 0, 0, &zErrMsg);
                 if( rc != SQLITE_OK ){
                 fprintf(stderr, "SQL error: %s\n", zErrMsg);
                sqlite3_free(zErrMsg);
                } else {
                fprintf(stdout, "Records created successfully\n");
                }
 
               minimo_ = to_string(minimo[6]);
               maximo_ = to_string(maximo[6]);
               prom_ = to_string(promedio[6]);
               sql7 = "INSERT INTO tabla_sensori(trans, minimo, maximo,prom) "  \
               "VALUES (" + trans_ + ", " + minimo_ + ","+ maximo_+", "+prom_+"); " ;
 
                rc = sqlite3_exec(db, sql7.c_str(), 0, 0, &zErrMsg);
                 if( rc != SQLITE_OK ){
                 fprintf(stderr, "SQL error: %s\n", zErrMsg);
                sqlite3_free(zErrMsg);
                } else {
                fprintf(stdout, "Records created successfully\n");
                }
          /*
                for(int i = 0; i<7; i++){
                    cout<<maximo[i]<<endl;
                }
                cout<<"minimos:"<<endl;
                for(int i = 0; i<7; i++){
                    cout<<minimo[i]<<endl;
                }
                cout<<"promedios:"<<endl;
                for(int i = 0; i<7; i++){
                    cout<<promedio[i]<<endl;
                }*/
 
            }
            cout << "Number of sec since January 1,1970 is:: " << now << endl;
            tm *ltm = localtime(&now);
       
            cout<<"Tiempo transcurrido: "<< now - inicio<<endl;
            // print various components of tm structure.
            cout << "Year:" << 1900 + ltm->tm_year<<endl;
            cout << "Month: "<< 1 + ltm->tm_mon<< endl;
            cout << "Day: "<< ltm->tm_mday << endl;
            cout << "Time: "<< ltm->tm_hour << ":";
            cout << ltm->tm_min << ":";
            cout << ltm->tm_sec << endl;
        }
       
}

sqlite3_close(db);
return 0;
}