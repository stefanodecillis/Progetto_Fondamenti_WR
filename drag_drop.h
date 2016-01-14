#ifndef DRAG_DROP_H
#define DRAG_DROP_H

#include <QWidget>

namespace Ui {
class drag_drop;
}

class drag_drop : public QWidget
{
    Q_OBJECT

public:
    explicit drag_drop(QWidget *parent = 0);
    ~drag_drop();
    void dragEnterEvent(QDragEnterEvent* event);
    void dragLeaveEvent(QDragLeaveEvent* event);
    void dragMoveEvent(QDragMoveEvent* event);
    void dropEvent(QDropEvent* event);

private:
    Ui::drag_drop *ui;
};

#endif // DRAG_DROP_H
