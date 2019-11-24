#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <coreadapter.h>

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
    CoreAdapter *core_adapter;

};

#endif // WIDGET_H
