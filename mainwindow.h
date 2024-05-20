#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ctime>
#include <QTimer>
#include <QElapsedTimer>
#include <stdlib.h>
#include <sqlite3.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    QTimer *tmr_;
    QElapsedTimer *elt;
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void poner_datos();

protected:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
