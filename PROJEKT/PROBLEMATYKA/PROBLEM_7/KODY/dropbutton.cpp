#include "dropbutton.h"
#include <QMimeData>
#include <QUrl>

DropButton::DropButton(QWidget* parent)
    : QPushButton(parent){
    setAcceptDrops(true);
}

void DropButton::dragEnterEvent(QDragEnterEvent* zdarzenie){
    if (zdarzenie->mimeData()->hasUrls()) {
        zdarzenie->acceptProposedAction();
    }
}

void DropButton::dropEvent(QDropEvent* zdarzenie){
    if (zdarzenie->mimeData()->hasUrls()) {
        QUrl url = zdarzenie->mimeData()->urls().first();
        emit plikUpuszczony(url.toLocalFile());
    }
}
