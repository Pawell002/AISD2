#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include "reprezentacja_danych.h"
#include "graf_budowa.h"
#include "graphwidget.h"

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
    QTextEdit* podgladDanych2;
    GraphWidget* graphWidget;
    QString pelnaZawartosc;
    QString sciezkaDoPliku;
    QVBoxLayout* u1 = nullptr;
    QString zapamietanyWynikTekst;
    bool wynikObliczony = false;
    bool daneSkompresowane = false;
    bool narysowany = false;
    std::string zakodowanyTekst;
    std::unordered_map<char, std::string> zakodowanaMapa;

    std::vector<Pole> pola;
    std::vector<Browar> browary;
    std::vector<Karczma> karczmy;
    std::vector<Droga> drogi;
    std::vector<std::vector<Krawedz>> graf;
    int start = 0;
    int koniec = 0;

    void wczytajIZbudujGraf(const QString& tekst);
    void podswietlWystapienia(QTextEdit* poleTekst, const QString& tekst, const QString& wzorzec);
    void wczytajPlik(const QString& sciezka);
    QString obliczOtoczkeIPole();
};

#endif // MAINWINDOW_H
