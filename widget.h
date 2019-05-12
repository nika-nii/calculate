#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QValidator>
#include <cmath>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

private slots:
    void slotCalculate();
};

#endif // WIDGET_H
