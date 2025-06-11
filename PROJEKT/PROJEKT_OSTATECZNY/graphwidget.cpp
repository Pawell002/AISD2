#include "graphwidget.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsSvgItem>
#include <QSvgRenderer>
#include <QPen>
#include <QBrush>
#include <QGraphicsSceneMouseEvent>
#include <QMessageBox>
#include <QWheelEvent>
#include <QPixmap>

GraphWidget::GraphWidget(QWidget *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene(this);
    setScene(scene);
    scene->setBackgroundBrush(QColor(58,58,58));

    setRenderHint(QPainter::Antialiasing);
    setRenderHint(QPainter::SmoothPixmapTransform);

    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setResizeAnchor(QGraphicsView::AnchorUnderMouse);

    wczytajSciezkiSVG();

    timerAnimacji = new QTimer(this);
    connect(timerAnimacji, &QTimer::timeout, this, &GraphWidget::wykonajNastepnyKrokAnimacji);
}

void GraphWidget::wczytajSciezkiSVG()
{
    svgSciezkaPole = "jeczmien2.svg";
    svgSciezkaBrowar = "browar2.svg";
    svgSciezkaKarczma = "karczma2.svg";
}

void GraphWidget::wheelEvent(QWheelEvent *event)
{
    const double scaleFactor = 1.15;
    if (event->angleDelta().y() > 0) {
        QGraphicsView::scale(scaleFactor, scaleFactor);
    } else {
        QGraphicsView::scale(1.0/scaleFactor,1.0/scaleFactor);
    }
}

class KlikniecieWierzcholek : public QGraphicsItem {
public:
    KlikniecieWierzcholek(QGraphicsItem *parent, const QString &info)
        : QGraphicsItem(parent), info(info) {
        setAcceptedMouseButtons(Qt::LeftButton);
    }

    QRectF boundingRect() const override {
        return parentItem()->boundingRect();
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {
        Q_UNUSED(painter)
        Q_UNUSED(option)
        Q_UNUSED(widget)
    }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            QMessageBox::information(nullptr, "Wierzchołek", info);
            event->accept();
        }
    }

private:
    QString info;
};

class KlikniecieKrawedz : public QGraphicsLineItem {
public:
    KlikniecieKrawedz(const QLineF &line, const QString &info, QGraphicsItem *parent = nullptr)
        : QGraphicsLineItem(line, parent), info(info) {
        setAcceptedMouseButtons(Qt::LeftButton);
    }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            QMessageBox::information(nullptr, "Krawędź", info);
            event->accept();
        }
    }

private:
    QString info;
};

void GraphWidget::dodajKlikalnyWierzcholek(float x, float y, const QString &info, const QString &svgSciezka)
{
    QGraphicsItem *node = nullptr;
    const int rozmiar = 60;

    if (!svgSciezka.isEmpty()) {
        QSvgRenderer *renderer = new QSvgRenderer(svgSciezka);
        if (renderer->isValid()) {
            QGraphicsSvgItem *svgItem = new QGraphicsSvgItem(svgSciezka);

            QRectF bounds = svgItem->boundingRect();
            qreal scale = rozmiar / qMax(bounds.width(), bounds.height());
            svgItem->setScale(scale);

            scene->addItem(svgItem);
            svgItem->setPos(x - (bounds.width() * scale)/2, y - (bounds.height() * scale)/2);
            node = svgItem;
        }
        delete renderer;
    }

    if (!node) {
        QGraphicsRectItem *rectItem = new QGraphicsRectItem(-rozmiar/2, -rozmiar/2, rozmiar, rozmiar);
        rectItem->setBrush(QBrush(Qt::gray));
        rectItem->setPen(QPen(Qt::black, 2));
        scene->addItem(rectItem);
        rectItem->setPos(x, y);
        node = rectItem;
    }

    node->setToolTip(info);
    node->setZValue(1);

    KlikniecieWierzcholek *klik = new KlikniecieWierzcholek(node, info);
    klik->setZValue(10);
}

void GraphWidget::dodajKlikalnaKrawedz(QPointF p1, QPointF p2, const QString &info, const QColor &kolor)
{
    QPen pen(kolor);
    pen.setWidth(3);

    KlikniecieKrawedz *line = new KlikniecieKrawedz(QLineF(p1, p2), info);
    line->setPen(pen);
    line->setToolTip(info);
    line->setZValue(-1);
    scene->addItem(line);
}

void GraphWidget::dodajElementDoAnimacji(const ElementDoAnimacji &elem)
{
    kolejkaAnimacji.enqueue(elem);
}

void GraphWidget::rozpocznijAnimacje()
{
    timerAnimacji->start(100);
}

void GraphWidget::wykonajNastepnyKrokAnimacji()
{
    if (kolejkaAnimacji.isEmpty()) {
        timerAnimacji->stop();
        return;
    }

    ElementDoAnimacji elem = kolejkaAnimacji.dequeue();
    switch (elem.typ) {
    case ElementDoAnimacji::Wierzcholek:
        dodajKlikalnyWierzcholek(elem.pozycja.x(), elem.pozycja.y(), elem.info, elem.svgSciezka);
        if (!elem.label.isEmpty()) {
            QGraphicsTextItem *text = scene->addText(elem.label);
            text->setPos(elem.pozycja.x() + 22, elem.pozycja.y() - 15);
            text->setZValue(2);
            text->setDefaultTextColor(Qt::white);
        }
        break;
    case ElementDoAnimacji::Krawedz:

        dodajKlikalnaKrawedz(elem.pozycja, elem.celKrawedzi, elem.info, elem.kolor);
        break;
    }
}

void GraphWidget::rysujGraf(const std::vector<Pole> &pola,
                            const std::vector<Browar> &browary,
                            const std::vector<Karczma> &karczmy,
                            const std::vector<Droga> &drogi)
{
    scene->clear();
    idToPosition.clear();
    kolejkaAnimacji.clear();

    QFont font;
    font.setPointSize(8);

    for (const Pole &p : pola)
        idToPosition[p.id] = QPointF(p.x, -p.y);
    for (const Browar &b : browary)
        idToPosition[b.id + 1000] = QPointF(b.x, -b.y);
    for (const Karczma &k : karczmy)
        idToPosition[k.id + 2000] = QPointF(k.x, -k.y);

    for (const Droga &d : drogi) {
        int z = d.zrodlo_id;
        int d_id = d.cel_id;
        QColor kolorKrawedzi = Qt::black;
        QString typZrodla, typCelu;
        QString nazwaZrodla, nazwaCelu;

        if (d.produkt == "jeczmien") {
            d_id += 1000;
            kolorKrawedzi = QColor(154, 205, 50);
            typZrodla = "Pole Jęczmienia";
            typCelu = "Browar";
            nazwaZrodla = QString("Pole Jęczmienia ID %1").arg(d.zrodlo_id);
            nazwaCelu = QString("Browar ID %1").arg(d.cel_id);
        } else if (d.produkt == "piwo") {
            z += 1000;
            d_id += 2000;
            kolorKrawedzi = QColor(255, 191, 0);
            typZrodla = "Browar";
            typCelu = "Karczma";
            nazwaZrodla = QString("Browar ID %1").arg(d.zrodlo_id);
            nazwaCelu = QString("Karczma ID %1").arg(d.cel_id);
        } else if (d.produkt == "karczma_do_karczmy") {
            z += 2000;
            d_id += 2000;
            kolorKrawedzi = QColor(184, 115, 51);
            typZrodla = "Karczma";
            typCelu = "Karczma";
            nazwaZrodla = QString("Karczma ID %1").arg(d.zrodlo_id);
            nazwaCelu = QString("Karczma ID %1").arg(d.cel_id);
        } else if (d.produkt == "browar_do_browaru") {
            z += 1000;
            d_id += 1000;
            kolorKrawedzi = QColor(101, 67, 33);
            typZrodla = "Browar";
            typCelu = "Browar";
            nazwaZrodla = QString("Browar ID %1").arg(d.zrodlo_id);
            nazwaCelu = QString("Browar ID %1").arg(d.cel_id);
        } else {
            continue;
        }

        if (idToPosition.contains(z) && idToPosition.contains(d_id)) {
            QPointF p1 = idToPosition[z];
            QPointF p2 = idToPosition[d_id];

            QString rzeczywistyProdukt;
            if (d.produkt == "jeczmien") {
                rzeczywistyProdukt = "Jęczmień";
            } else if (d.produkt == "piwo") {
                rzeczywistyProdukt = "Piwo";
            } else if (d.produkt == "karczma_do_karczmy") {
                rzeczywistyProdukt = "Piwo";
            } else if (d.produkt == "browar_do_browaru") {
                rzeczywistyProdukt = "Jęczmień";
            } else {
                rzeczywistyProdukt = QString::fromStdString(d.produkt);
            }


            QString info = QString("Droga ID: %1\n""Z: %2 → Do: %3\n""Produkt: %4\n""Przepustowość: %5\n""Koszt naprawy: %6").arg(d.id).arg(nazwaZrodla).arg(nazwaCelu).arg(rzeczywistyProdukt).arg(d.przepustowosc).arg(d.koszt_naprawy);
            ElementDoAnimacji e;
            e.typ = ElementDoAnimacji::Krawedz;
            e.pozycja = p1;
            e.celKrawedzi = p2;
            e.info = info;
            e.kolor = kolorKrawedzi;
            dodajElementDoAnimacji(e);
        }
    }

    auto dodajWierzcholek = [&](int id, float x, float y, const QString &label, const QString &info, const QString &svgSciezka) {
        QPointF pos(x, -y);
        ElementDoAnimacji e;
        e.typ = ElementDoAnimacji::Wierzcholek;
        e.pozycja = pos;
        e.info = info;
        e.label = label;
        e.svgSciezka = svgSciezka;
        dodajElementDoAnimacji(e);
    };

    for (const Pole &p : pola) {
        QString info = QString("Pole Jęczmienia ID: %1\nPozycja: x=%2, y=%3\nIlość jęczmienia: %4")
                           .arg(p.id).arg(p.x).arg(p.y).arg(p.ilosc_jeczmienia);
        dodajWierzcholek(p.id, p.x, p.y, QString("P%1").arg(p.id), info, svgSciezkaPole);
    }

    for (const Browar &b : browary) {
        QString info = QString("Browar ID: %1\nPozycja: x=%2, y=%3\nPojemność: %4")
                           .arg(b.id).arg(b.x).arg(b.y).arg(b.pojemnosc);
        dodajWierzcholek(b.id + 1000, b.x, b.y, QString("B%1").arg(b.id), info, svgSciezkaBrowar);
    }

    for (const Karczma &k : karczmy) {
        QString info = QString("Karczma ID: %1\nPozycja: x=%2, y=%3\nZapotrzebowanie: %4")
        .arg(k.id).arg(k.x).arg(k.y).arg(k.zapotrzebowanie);
        dodajWierzcholek(k.id + 2000, k.x, k.y, QString("K%1").arg(k.id), info, svgSciezkaKarczma);
    }

    QRectF bounds = scene->itemsBoundingRect();
    scene->setSceneRect(bounds);
    resetTransform();
    centerOn(bounds.center());
    scale(1.65,1.65);

    rozpocznijAnimacje();
}
