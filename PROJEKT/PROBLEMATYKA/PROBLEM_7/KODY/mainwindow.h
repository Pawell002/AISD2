#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include "reprezentacja_danych.h"
#include "graf_budowa.h"
#include "graphwidget.h"  // DODANE

class QVBoxLayout;
class QStackedWidget;
class QTextEdit;
class DropButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void wypiszWynik();
    void wczytajDane();
    void rysujGraf();
    void kompresujDane();
    void znajdzWzorzec();
    void wybierzPlik();

private:
    QStackedWidget* stosWidokow;
    DropButton* obszarWrzucania;
    QTextEdit* podgladPliku;
    QTextEdit* poleKompresji;
    QTextEdit* podgladDanych;
    GraphWidget* graphWidget;  // DODANE
    QString pelnaZawartosc;
    QString sciezkaDoPliku;
    QVBoxLayout* u1 = nullptr;

    std::vector<Pole> pola;
    std::vector<Browar> browary;
    std::vector<Karczma> karczmy;
    std::vector<Droga> drogi;
    std::vector<std::vector<Krawedz>> graf;
    int start = 0;
    int koniec = 0;

    void wczytajIZbudujGraf(const QString& tekst);
    void wczytajPlik(const QString& sciezka);
};

#endif // MAINWINDOW_H

