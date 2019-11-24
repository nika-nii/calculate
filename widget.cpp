#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    core_adapter = new CoreAdapter;

    // Подключение сигналов-слотов
    QObject::connect(ui->input_b, QOverload<double>::of(&QDoubleSpinBox::valueChanged), core_adapter, &CoreAdapter::set_b);
    QObject::connect(ui->input_h, QOverload<double>::of(&QDoubleSpinBox::valueChanged), core_adapter, &CoreAdapter::set_h);
    QObject::connect(ui->input_h0, QOverload<double>::of(&QDoubleSpinBox::valueChanged), core_adapter, &CoreAdapter::set_h0);
    QObject::connect(ui->input_a_s, QOverload<double>::of(&QDoubleSpinBox::valueChanged), core_adapter, &CoreAdapter::set_as);
    QObject::connect(ui->input_M, QOverload<double>::of(&QDoubleSpinBox::valueChanged), core_adapter, &CoreAdapter::set_M);
    QObject::connect(ui->input_eps_bu, QOverload<double>::of(&QDoubleSpinBox::valueChanged), core_adapter, &CoreAdapter::set_eps_bu);
    QObject::connect(ui->input_m, QOverload<double>::of(&QDoubleSpinBox::valueChanged), core_adapter, &CoreAdapter::set_m);
    QObject::connect(ui->concrete_class, QOverload<int>::of(&QComboBox::currentIndexChanged), core_adapter, &CoreAdapter::set_concrete);
    QObject::connect(ui->armature_class, QOverload<int>::of(&QComboBox::currentIndexChanged), core_adapter, &CoreAdapter::set_armature);
    QObject::connect(core_adapter, &CoreAdapter::set_As, ui->output_A_s, &QLineEdit::setText);
    QObject::connect(core_adapter, &CoreAdapter::set_miu, ui->output_miu, &QLineEdit::setText);
    QObject::connect(core_adapter, &CoreAdapter::set_ksi, ui->output_ksi, &QLineEdit::setText);
    QObject::connect(core_adapter, &CoreAdapter::set_A_0, ui->output_A_0, &QLineEdit::setText);
    QObject::connect(core_adapter, &CoreAdapter::set_lambda, ui->output_lambda, &QLineEdit::setText);
    QObject::connect(core_adapter, &CoreAdapter::set_sigma_s, ui->output_sigma_s, &QLineEdit::setText);

    // Установка стандартных значений
    core_adapter->set_b(0);
    core_adapter->set_h(0);
    core_adapter->set_h0(0);
    core_adapter->set_as(0);
    core_adapter->set_M(0);
    core_adapter->set_eps_bu(0);
    core_adapter->set_m(0);
    core_adapter->set_concrete(0);
    core_adapter->set_armature(0);

    core_adapter->update();
}

Widget::~Widget()
{
    delete core_adapter;
    delete ui;
}

