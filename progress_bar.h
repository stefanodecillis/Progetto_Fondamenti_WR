#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

#include <QWidget>

namespace Ui {
class progress_bar;
}

class progress_bar : public QWidget
{
    Q_OBJECT

public:
    explicit progress_bar(QWidget *parent = 0);
    ~progress_bar();

private:
    Ui::progress_bar *ui;
};

#endif // PROGRESS_BAR_H
