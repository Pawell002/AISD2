#ifndef DROPBUTTON_H
#define DROPBUTTON_H

#pragma once

#include <QPushButton>
#include <QDragEnterEvent>
#include <QDropEvent>

class DropButton : public QPushButton {
    Q_OBJECT
public:
    explicit DropButton(QWidget* parent = nullptr);

signals:
    void plikUpuszczony(const QString& sciezka);

protected:
    void dragEnterEvent(QDragEnterEvent* zdarzenie) override;
    void dropEvent(QDropEvent* zdarzenie) override;
};

#endif // DROPBUTTON_H
