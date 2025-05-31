#ifndef OBSZAR_WRZUC_H
#define OBSZAR_WRZUC_H

#include <QLabel>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QFileInfo>

class ObszarWrzucania : public QLabel {
    Q_OBJECT
public:
    explicit ObszarWrzucania(QWidget* parent = nullptr) : QLabel(parent) {
        setAcceptDrops(true);
    }

signals:
    void plikUpuszczony(const QString& sciezka);

protected:
    void dragEnterEvent(QDragEnterEvent* e) override {
        if (e->mimeData()->hasUrls())
            e->acceptProposedAction();
    }

    void dropEvent(QDropEvent* e) override {
        if (e->mimeData()->hasUrls()) {
            const QUrl url = e->mimeData()->urls().first();
            emit plikUpuszczony(url.toLocalFile());
        }
    }
};

#endif // OBSZAR_WRZUC_H
