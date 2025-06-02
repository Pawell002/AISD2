#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMap>
#include <QPointF>
#include <QPixmap>
#include <QTimer>
#include <QQueue>
#include <QSvgRenderer>
#include <QSvgWidget>
#include <QColor>
#include "reprezentacja_danych.h"

struct ElementDoAnimacji {
    enum Typ { Wierzcholek, Krawedz } typ;
    QPointF pozycja;
    QString info;
    QString label;
    QString svgSciezka;
    QPointF celKrawedzi;
    QColor kolor;
};

class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = nullptr);
    void rysujGraf(const std::vector<Pole> &pola,
                   const std::vector<Browar> &browary,
                   const std::vector<Karczma> &karczmy,
                   const std::vector<Droga> &drogi);

protected:
    void wheelEvent(QWheelEvent *event) override;

private slots:
    void wykonajNastepnyKrokAnimacji();

private:
    QGraphicsScene *scene;
    QMap<int, QPointF> idToPosition;

    QString svgSciezkaPole;
    QString svgSciezkaBrowar;
    QString svgSciezkaKarczma;

    QTimer *timerAnimacji;
    QQueue<ElementDoAnimacji> kolejkaAnimacji;

    void wczytajSciezkiSVG();
    void dodajKlikalnyWierzcholek(float x, float y,const QString &info, const QString &svgSciezka);
    void dodajKlikalnaKrawedz(QPointF p1,QPointF p2, const QString &info,const QColor &kolor = Qt::black);

    void dodajElementDoAnimacji(const ElementDoAnimacji &elem);
    void rozpocznijAnimacje();
};
#endif

