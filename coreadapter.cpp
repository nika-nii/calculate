#include "coreadapter.h"

#include "core.h"

#include <QDebug>

struct concrete_params{
    double B;
    double Rb;
    double Eb;
};

static QList<concrete_params> concrete_list = {
    {3.5,   27.0,   95000.0},
    {5,     35.0,   130000.0},
    {7.5,   55.0,   160000.0},
    {10,    75.0,   190000.0},
    {12.5,  95.0,   215000.0},
    {15,    110.0,  240000.0},
    {20,    150.0,  275000.0},
    {25,    185.0,  300000.0},
    {30,    220.0,  325000.0},
    {35,    255.0,  345000.0},
    {40,    290.0,  360000.0},
    {45,    320.0,  370000.0},
    {50,    360.0,  380000.0},
    {55,    395.0,  390000.0},
    {60,    430.0,  395000.0},
    {70,    500.0,  410000.0},
    {80,    570.0,  420000.0},
    {90,    640.0,  425000.0},
    {100,   710.0,  430000.0}
};

struct armature_params{
    double Rs;
    double Es;
};

static QList<armature_params> armature_list = {
    {240, 2E6},
    {400, 2E6},
    {500, 2E6},
    {600, 2E6},
    {800, 2E6},
    {1000, 2E6},
    {500, 2E6},
    {500, 2E6},
    {1200, 2E6},
    {1300, 2E6},
    {1400, 2E6},
    {1500, 2E6},
    {1600, 2E6},
    {1400, 2E6},
    {1500, 2E6},
    {1600, 2E6},
    {1700, 2E6}
};


void CoreAdapter::check_params(){
    qDebug() << "Checking parameters" << endl;
    if (
            has_b && has_B &&
            has_h && has_h0 &&
            has_as && has_Rb &&
            has_Eb && has_A &&
            has_Es && has_M &&
            has_eps_bu && has_Rs && has_m
            ){
        qDebug() << "Everything is allright" << endl;
        Core *core = new Core(b, B, h, h0, as, Rb, Eb, A, Es, M, eps_bu, Rs, m);
        core->calculate();
        As = core->get_As();
        miu = core->get_miu();
        ksi = core->get_ksi();
        A_0 = core->get_A_0();
        lambda = core->get_lambda();
        sigma_s = core->get_sigma_s();

        emit set_As(QString::number(As));
        emit set_miu(QString::number(miu));
        emit set_ksi(QString::number(ksi));
        emit set_A_0(QString::number(A_0));
        emit set_lambda(QString::number(lambda));
        emit set_sigma_s(QString::number(sigma_s));

        delete core;
    }
}

void CoreAdapter::set_b(double value) {
    qDebug() << "b set" << endl;
    b = value;
    has_b = true;
    check_params();
}

void CoreAdapter::set_h(double value) {
    qDebug() << "h set" << endl;
    h = value;
    has_h = true;
    check_params();
}

void CoreAdapter::set_h0(double value) {
    qDebug() << "h0 set" << endl;
    h0 = value;
    has_h0 = true;
    check_params();
}

void CoreAdapter::set_as(double value) {
    qDebug() << "as set" << endl;
    as = value;
    has_as = true;
    check_params();
}

void CoreAdapter::set_concrete(int index) {
    qDebug() << "concrete set" << endl;
    concrete_params concrete = concrete_list[index];
    B = concrete.B;
    Rb = concrete.Rb;
    Eb = concrete.Eb;
    has_B = true;
    has_Rb = true;
    has_Eb = true;
    check_params();
}

void CoreAdapter::set_armature(int index) {
    qDebug() << "armature set" << endl;
    armature_params armature = armature_list[index];
    A = armature.Rs;
    Es = armature.Es;
    Rs = armature.Rs*10;
    has_A = true;
    has_Es = true;
    has_Rs = true;
    check_params();
}

void CoreAdapter::set_M(double value) {
    qDebug() << "M set" << endl;
    M = value;
    has_M = true;
    check_params();
}

void CoreAdapter::set_eps_bu(double value) {
    qDebug() << "eps_bu set" << endl;
    eps_bu = value;
    has_eps_bu = true;
    check_params();
}

void CoreAdapter::set_m(double value) {
    qDebug() << "m set" << endl;
    m = value;
    has_m = true;
    check_params();
}
