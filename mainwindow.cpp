#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <ctime>
#include <QTimer>
#include <QElapsedTimer>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string>
#include <iostream>

static int callback( void *data, int argc, char **argv, char **azColName){
   int i;
   //std::cout << (const char*)data << std::endl;
   Ui::MainWindow *ui = (Ui::MainWindow*)data;
   std::string comp = azColName[1];
   if(comp== "minimo"){
   float min_ = atof(argv[1]);
   float max_ = atof(argv[2]);
   float prom_ = atof(argv[3]);
   ui->minimo_le->setText(QString::number(min_));
   ui->maximo_le->setText(QString::number(max_));
   ui->promedio_le->setText(QString::number(prom_));
   }
   else{
       std::string fecha = argv[1];
       std::string hora = argv[2];
       ui->lineEdit->setText(QString::fromStdString(fecha));
       ui->lineEdit_4->setText(QString::fromStdString(hora));
   }
   return 0;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tmr_ = new QTimer();
    tmr_->setInterval(500);
    connect(tmr_, SIGNAL(timeout()), this, SLOT(poner_datos()));
    tmr_->start();
    elt = new QElapsedTimer();
    this->elt->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::poner_datos(){
    int op = ui->selector_sensores->currentIndex();
    int time = elt->elapsed()/1000;
    std::cout<<time<<std::endl;
    ui->lineEdit_5->setText(QString::number(time));
    sqlite3 *db;
       char *zErrMsg = 0;
       int rc;
       std::string sql;
       const char* data = "He llamado la función Callback";

       double gh = 0.;

       /* Open database */
       rc = sqlite3_open("../proyecto.db", &db);

       if( rc ) {
          fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
          return;
       } else {
          fprintf(stderr, "Opened database successfully\n");
       }
       if (op == 0){
           sql = "SELECT * FROM tabla_sensort WHERE (SELECT MAX(trans) FROM tabla_sensorh) = trans;";
       }
       else if(op == 1){
           sql = "SELECT * FROM tabla_sensorh WHERE (SELECT MAX(trans) FROM tabla_sensorh) = trans;";
       }
       else if(op == 2){
           sql = "SELECT * FROM tabla_sensorhs WHERE (SELECT MAX(trans) FROM tabla_sensorh) = trans;";
       }
       else if(op == 3){
           sql = "SELECT * FROM tabla_sensorv WHERE (SELECT MAX(trans) FROM tabla_sensorh) = trans;";
       }
       else if(op == 4){
           sql = "SELECT * FROM tabla_sensordv WHERE (SELECT MAX(trans) FROM tabla_sensorh) = trans;";
       }
       else if(op == 5){
           sql = "SELECT * FROM tabla_sensorp WHERE (SELECT MAX(trans) FROM tabla_sensorh) = trans;";
       }
       else if(op == 6){
           sql = "SELECT * FROM tabla_sensori WHERE (SELECT MAX(trans) FROM tabla_sensorh) = trans;";
       }
       /* Create SQL statement */


       /* Execute SQL statement */
       rc = sqlite3_exec(db, sql.c_str(), callback, (void*)ui, &zErrMsg);

       if( rc != SQLITE_OK ) {
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
       } else {
          fprintf(stdout, "Operation done successfully\n");
       }

       sql = "SELECT * FROM info_tablap WHERE (SELECT MAX(trans) FROM tabla_sensorh) = trans;";
       rc = sqlite3_exec(db, sql.c_str(), callback, (void*)ui, &zErrMsg);

       if( rc != SQLITE_OK ) {
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
       } else {
          fprintf(stdout, "Operation done successfully\n");
       }
       sqlite3_close(db);
}

