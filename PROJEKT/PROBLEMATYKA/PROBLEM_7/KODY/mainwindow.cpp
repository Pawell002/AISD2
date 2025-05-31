#include "mainwindow.h"
#include "dropbutton.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QStyle>
#include <QFont>
#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QStackedWidget>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>
#include <qevent.h>
#include <qmimedata.h>
#include <QLineEdit>
#include <QComboBox>
#include <QStackedLayout>
#include "algorytmy_tekstowe.h"
#include "huffman.h"
#include "min_cost_max_flow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {


    QWidget* centralnyWidget = new QWidget(this);
    this->setCentralWidget(centralnyWidget);

    QWidget* menu_pasek = new QWidget(this);
    menu_pasek->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    menu_pasek->setStyleSheet(
        "background-color: #121212; "
        "padding: 6px; "
        );

    QHBoxLayout* ukladMenu = new QHBoxLayout(menu_pasek);

    ukladMenu->setContentsMargins(0, 0, 0, 0);
    ukladMenu->setSpacing(0);

    QPushButton* btnWypiszWynik = new QPushButton("Wypisz wynik");
    QPushButton* btnWrzucDane = new QPushButton("Wrzuć dane");
    QPushButton* btnRysujGraf = new QPushButton("Rysuj graf");
    QPushButton* btnKompresuj = new QPushButton("Kompresuj dane");
    QPushButton* btnZnajdz = new QPushButton("Wyszukaj słowa");

    QFont czcionka;
    czcionka.setPointSize(14);
    btnWypiszWynik->setFont(czcionka);
    btnWrzucDane->setFont(czcionka);
    btnRysujGraf->setFont(czcionka);
    btnKompresuj->setFont(czcionka);
    btnZnajdz->setFont(czcionka);

    btnWypiszWynik->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    btnWrzucDane->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    btnRysujGraf->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    btnKompresuj->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    btnZnajdz->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    QString stylPrzyciskow =
        "QPushButton {"
        "   border: none;"
        "   background-color: #dce5ea;"
        "   color: #1c1c1c; "
        "   padding: 10px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #cddbe2;"
        "   color: black;"
        "}";

    btnWypiszWynik->setStyleSheet(stylPrzyciskow);
    btnWrzucDane->setStyleSheet(stylPrzyciskow);
    btnRysujGraf->setStyleSheet(stylPrzyciskow);
    btnKompresuj->setStyleSheet(stylPrzyciskow);
    btnZnajdz->setStyleSheet(stylPrzyciskow);

    ukladMenu->addWidget(btnWypiszWynik);
    ukladMenu->addWidget(btnWrzucDane);
    ukladMenu->addWidget(btnRysujGraf);
    ukladMenu->addWidget(btnKompresuj);
    ukladMenu->addWidget(btnZnajdz);

    stosWidokow = new QStackedWidget(this);

    QWidget* widok0 = new QWidget();
    widok0->setStyleSheet("background-color: #f4f7f8; color: #2e2e2e;");
    QVBoxLayout* u0 = new QVBoxLayout(widok0);

    QWidget* widok1 = new QWidget();
    widok1->setStyleSheet("background-color: #f4f7f8; color: #2e2e2el;");
    u1 = new QVBoxLayout(widok1);

    QWidget* widok2 = new QWidget();
    widok2->setStyleSheet("background-color: #a4c8e1;");
    QVBoxLayout* ukladWczytaj = new QVBoxLayout(widok2);

    obszarWrzucania = new DropButton();
    obszarWrzucania->setText("Upuść plik tutaj lub kliknij, aby wybrać");
    obszarWrzucania->setStyleSheet(
        "border: 2px dashed #aaa; "
        "padding: 20px; "
        "background-color: #f5f5f5; "
        "font-size: 14pt;"
        );
    obszarWrzucania->setMinimumHeight(180);
    obszarWrzucania->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    obszarWrzucania->setAcceptDrops(true);

    podgladPliku = new QTextEdit();
    podgladPliku->setReadOnly(true);
    podgladPliku->setStyleSheet("background-color: #b6e2d3");

    podgladPliku->setMinimumHeight(180);
    podgladPliku->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    ukladWczytaj->addWidget(podgladPliku);
    ukladWczytaj->addWidget(obszarWrzucania);

    QWidget* widok3 = new QWidget();
    widok3->setStyleSheet("background-color: black; color: white;");
    QStackedLayout* ukladGrafu = new QStackedLayout(widok3);

    QWidget* trybGraf = new QWidget();
    QVBoxLayout* ukladTrybGraf = new QVBoxLayout(trybGraf);
    ukladTrybGraf->setContentsMargins(0, 0, 0, 0);
    ukladTrybGraf->setSpacing(0);

    QWidget* kontenerPodgladu = new QWidget();
    kontenerPodgladu->setMaximumHeight(this->height() / 8);
    kontenerPodgladu->setMaximumWidth(this->width() / 4);
    QVBoxLayout* ukladPodgladu = new QVBoxLayout(kontenerPodgladu);
    ukladPodgladu->setContentsMargins(0, 0, 0, 0);
    ukladPodgladu->setSpacing(4);

    podgladDanych = new QTextEdit("Podgląd danych...");
    podgladDanych->setWordWrapMode(QTextOption::WordWrap);
    podgladDanych->setReadOnly(true);
    podgladDanych->setStyleSheet("background-color: ##b6e2d3; padding: 5px;");
    podgladDanych->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    podgladDanych->setMinimumHeight(30);
    podgladDanych->setMaximumHeight(30);

    QPushButton* przyciskRozwin = new QPushButton("Pokaż więcej");
    przyciskRozwin->setStyleSheet("padding: 4px;");
    przyciskRozwin->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    ukladPodgladu->addWidget(podgladDanych);
    ukladPodgladu->addWidget(przyciskRozwin, 0, Qt::AlignLeft);

    ukladTrybGraf->addWidget(kontenerPodgladu);
    ukladTrybGraf->addWidget(new QLabel("Tu będzie rysowany graf"));

    QWidget* trybPodglad = new QWidget();
    QVBoxLayout* ukladTrybPodglad = new QVBoxLayout(trybPodglad);
    ukladTrybPodglad->setContentsMargins(10, 10, 10, 10);

    QLabel* rozwinietyPodglad = new QLabel();
    rozwinietyPodglad->setWordWrap(true);
    rozwinietyPodglad->setStyleSheet("background-color: #b6e2d3; padding: 10px; font-size: 12pt;");
    rozwinietyPodglad->setAlignment(Qt::AlignTop);
    rozwinietyPodglad->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QPushButton* przyciskZwin = new QPushButton("Ukryj");
    ukladTrybPodglad->addWidget(rozwinietyPodglad);
    ukladTrybPodglad->addWidget(przyciskZwin, 0, Qt::AlignLeft);

    ukladGrafu->addWidget(trybGraf);
    ukladGrafu->addWidget(trybPodglad);

    ukladGrafu->setCurrentIndex(0);

    QWidget* widok4 = new QWidget();
    widok1->setStyleSheet("background-color: #f4f7f8; color: #2e2e2el;");
    QVBoxLayout* u4 = new QVBoxLayout(widok4);
    poleKompresji = new QTextEdit();
    poleKompresji->setReadOnly(true);
    poleKompresji->setStyleSheet("background-color: #dad0ec; font-size: 12pt;");
    u4->addWidget(poleKompresji);

    QWidget* widok5 = new QWidget();
    widok1->setStyleSheet("background-color: #f4f7f8; color: #2e2e2el;");
    QVBoxLayout* u5 = new QVBoxLayout(widok5);

    QTextEdit* poleWzorce = new QTextEdit();
    poleWzorce->setPlaceholderText("Wprowadź wzorzec lub wzorce dla Trie każdy w nowej linii");
    poleWzorce->setMaximumHeight(60);

    QComboBox* wyborAlgorytmu = new QComboBox();
    wyborAlgorytmu->addItems({"Naiwny", "KMP", "Rabin-Karp", "Trie", "Boyer-Moore"});

    QPushButton* przyciskSzukaj = new QPushButton("Szukaj");

    QTextEdit* wynikWyszukiwania = new QTextEdit();
    wynikWyszukiwania->setReadOnly(true);

    u5->addWidget(new QLabel("Wyszukaj wzorzec:"));
    u5->addWidget(poleWzorce);
    u5->addWidget(wyborAlgorytmu);
    u5->addWidget(przyciskSzukaj);
    u5->addWidget(wynikWyszukiwania);

    stosWidokow->addWidget(widok0);
    stosWidokow->addWidget(widok1);
    stosWidokow->addWidget(widok2);
    stosWidokow->addWidget(widok3);
    stosWidokow->addWidget(widok4);
    stosWidokow->addWidget(widok5);

    QVBoxLayout* ukladGlowny = new QVBoxLayout(centralnyWidget);
    ukladGlowny->setContentsMargins(0, 0, 0, 0);
    ukladGlowny->addWidget(menu_pasek);
    ukladGlowny->addWidget(stosWidokow);

    connect(obszarWrzucania, &QPushButton::clicked, this, &MainWindow::wybierzPlik);
    connect(obszarWrzucania, &DropButton::plikUpuszczony, this, &MainWindow::wczytajPlik);

    connect(btnWypiszWynik, &QPushButton::clicked, this, &MainWindow::wypiszWynik);
    connect(btnWrzucDane, &QPushButton::clicked, this, &MainWindow::wczytajDane);
    connect(btnRysujGraf, &QPushButton::clicked, this, &MainWindow::rysujGraf);
    connect(btnKompresuj, &QPushButton::clicked, this, &MainWindow::kompresujDane);
    connect(btnZnajdz, &QPushButton::clicked, this, &MainWindow::znajdzWzorzec);

    connect(przyciskRozwin, &QPushButton::clicked, this, [=]() {
        rozwinietyPodglad->setText(pelnaZawartosc);
        ukladGrafu->setCurrentIndex(1);
    });

    connect(przyciskZwin, &QPushButton::clicked, this, [=]() {
        ukladGrafu->setCurrentIndex(0);

        QString krotki = pelnaZawartosc.left(200);
        krotki.replace('\n', ' ');
        podgladDanych->setText(krotki + "...");
    });

    connect(przyciskSzukaj, &QPushButton::clicked, this, [=]() mutable{

        QString tekst = pelnaZawartosc;
        QString algWybrany = wyborAlgorytmu->currentText();

        QStringList wzorce = poleWzorce->toPlainText().split('\n', Qt::SkipEmptyParts);

        if(wzorce.isEmpty() || tekst.isEmpty()){
            QMessageBox::warning(this, "Błąd", "Brak wzorców lub danych!");
            return;
        }


        if (algWybrany != "Trie" && wzorce.size() > 1) {
            QMessageBox::warning(this, "Błąd", "Ten algorytm obsługuje tylko jeden wzorzec!");
            return;
        }

        vector<pair<int, int>> wyniki;
        QStringList linie = tekst.split('\n');

        for (int i = 0; i < linie.size(); ++i) {
            string linia = linie[i].toStdString();

            if (algWybrany == "Trie") {
                TrieWezel* korzen = new TrieWezel();
                int index = 1;
                for (const QString& wz : wzorce) {
                    wstaw(korzen, wz.toStdString(), index++);
                }

                auto dopasowania = znajdzWTekscie(korzen, linia);
                for (const auto& t : dopasowania) {
                    int pozycja = get<0>(t);
                    wyniki.emplace_back(i + 1, pozycja);
                }
                usun(korzen);

            } else {
                string pattern = wzorce[0].toStdString();

                if (algWybrany == "Naiwny") {
                    wyszukajNaiwnie(linia, pattern, wyniki, i + 1);
                } else if (algWybrany == "KMP") {
                    vector<int> P(pattern.size());
                    tablica_P(pattern, P);
                    KMP(linia, pattern, P, wyniki, i + 1);
                } else if (algWybrany == "Rabin-Karp") {
                    znajdzRabinKarp(pattern, linia, 101, 128, wyniki, i + 1);
                } else if (algWybrany == "Boyer-Moore"){
                    boyerMoore(linia, pattern, wyniki, i + 1);
                }
            }
        }

        if (wyniki.empty()) {
            wynikWyszukiwania->setPlainText("Nie znaleziono dopasowań.");
        } else {
            QString wynikTekst;
            for (const auto& para : wyniki) {
                wynikTekst += QString("Linia %1, pozycja %2\n").arg(para.first).arg(para.second);
            }
            wynikWyszukiwania->setPlainText(wynikTekst);
        }
    });
}

MainWindow::~MainWindow() {}

void MainWindow::wypiszWynik() {
    if(pelnaZawartosc.isEmpty()){
        QMessageBox::warning(this, "Brak Danych!", "Najpierw załaduj dane!");
        return;
    }

    int start = 0;
    int koniec = graf.size() - 1;
    auto wynik = min_cost_max_flow(graf, start, koniec);

    QString wynikTekst = QString(
                             "==================================================================================\n"
                             "|                        PODSUMOWANIE TRANSPORTU                                 |\n"
                             "==================================================================================\n\n"
                             "Przewozony surowiec: jeczmien, piwo\n"
                             "Przelicznik: 1 jednostka jeczmienia = 1 jednostka piwa\n"
                             "----------------------------------------------------------------------------------\n"
                             "Maksymalna ilosc piwa dostarczonego do karczm: %1 litrow\n"
                             "----------------------------------------------------------------------------------\n"
                             "Calkowity koszt naprawy drog: %2 zlotych monet\n"
                             "==================================================================================\n"
                             ).arg(wynik.first).arg(wynik.second);

    QFile plikWyj("wynik.txt");
    if (plikWyj.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&plikWyj);
        out << wynikTekst;
        plikWyj.close();
    } else {
        QMessageBox::warning(this, "Błąd", "Nie można zapisać do pliku wynik.txt");
    }

    QLabel* wynikPole = new QLabel(wynikTekst);
    wynikPole->setWordWrap(true);
    wynikPole->setStyleSheet("background-color: #3399aa; padding: 10px;");

    QLayoutItem* item;
    while((item = u1->takeAt(0)) != nullptr){
        delete item->widget();
        delete item;
    }

    u1->addWidget(wynikPole);
    stosWidokow->setCurrentIndex(1);
}

void MainWindow::wczytajDane() {
    stosWidokow->setCurrentIndex(2);
}

void MainWindow::rysujGraf() {
    stosWidokow->setCurrentIndex(3);
}

void MainWindow::kompresujDane(){
    if (pelnaZawartosc.isEmpty()) {
        QMessageBox::warning(this, "Brak danych", "Najpierw załaduj dane do kompresji!");
        return;
    }

    Huffman huffman;

    huffman.kompresuj(pelnaZawartosc.toStdString());

    std::ostringstream out;

    out << "Kody Huffmana:\n";
    for (const auto& para : huffman.getMapaKodow()) {
        if (para.first == '\n') out << "\\n";
        else if (para.first == ' ') out << "' '";
        else out << para.first;
        out << " : " << para.second << "\n";
    }
    out << "\nZakodowany tekst:\n" << huffman.getZakodowanyTekst() << "\n";

    QString wynik = QString::fromStdString(out.str());
    poleKompresji->setPlainText(wynik);

    stosWidokow->setCurrentIndex(4);
}

void MainWindow::znajdzWzorzec(){
    stosWidokow->setCurrentIndex(5);
}

void MainWindow::wybierzPlik() {
    QString nazwaPliku = QFileDialog::getOpenFileName(this, "Wybierz plik");
    if (!nazwaPliku.isEmpty()) {
        wczytajPlik(nazwaPliku);
    }
}

void MainWindow::wczytajIZbudujGraf(const QString& tekstDanych) {
    pola.clear(); browary.clear(); karczmy.clear(); drogi.clear(); graf.clear();

    std::istringstream strumien(tekstDanych.toStdString());
    int l_pola, l_browary, l_karczmy, l_drogi;
    strumien >> l_pola >> l_browary >> l_karczmy >> l_drogi;

    for (int i = 0; i < l_pola; ++i) {
        Pole p;
        strumien >> p.id >> p.x >> p.y >> p.ilosc_jeczmienia;
        pola.push_back(p);
    }
    for (int i = 0; i < l_browary; ++i) {
        Browar b;
        strumien >> b.id >> b.x >> b.y >> b.pojemnosc;
        browary.push_back(b);
    }
    for (int i = 0; i < l_karczmy; ++i) {
        Karczma k;
        strumien >> k.id >> k.x >> k.y >> k.zapotrzebowanie;
        karczmy.push_back(k);
    }
    for (int i = 0; i < l_drogi; ++i) {
        Droga d;
        strumien >> d.id >> d.zrodlo_id >> d.cel_id >> d.produkt >> d.przepustowosc >> d.koszt_naprawy;
        drogi.push_back(d);
    }

    zbuduj_graf(pola, browary, karczmy, drogi, graf, start, koniec);
}

void MainWindow::wczytajPlik(const QString& sciezka){
    QFile plik(sciezka);

    if(!plik.open(QIODevice::ReadOnly | QIODevice::Text)){
        podgladPliku->setPlainText("Nie udało się otworzyć pliku.");
        return;
    }

    QTextStream in(&plik);
    pelnaZawartosc = in.readAll();
    podgladPliku->setPlainText(pelnaZawartosc);

    if(podgladDanych){
        QString krotkiPodglad = pelnaZawartosc.left(200);
        krotkiPodglad.replace('\n', ' ');
        podgladDanych->setText(krotkiPodglad + "...");
    }

    obszarWrzucania->setText("Załadowano: " + QFileInfo(sciezka).fileName());

    wczytajIZbudujGraf(pelnaZawartosc);
}
