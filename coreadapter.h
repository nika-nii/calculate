#ifndef COREADAPTER_H
#define COREADAPTER_H

#include <QObject>
#include <QMap>

class CoreAdapter : public QObject
{
    Q_OBJECT
private:
    // Входы
    double b;
    double B;
    double h;
    double h0;
    double as;
    double Rb;
    double Eb;
    double A;
    double Es;
    double M;
    double eps_bu;
    double Rs;
    double m;
    bool has_b;
    bool has_B;
    bool has_h;
    bool has_h0;
    bool has_as;
    bool has_Rb;
    bool has_Eb;
    bool has_A;
    bool has_Es;
    bool has_M;
    bool has_eps_bu;
    bool has_Rs;
    bool has_m;
    // Выходы
    double As;
    double miu;
    double ksi;
    double A_0;
    double lambda;
    double sigma_s;
    void check_params();
public:
    CoreAdapter() :
        has_b(false),
        has_B(false),
        has_h(false),
        has_h0(false),
        has_as(false),
        has_Rb(false),
        has_Eb(false),
        has_A(false),
        has_Es(false),
        has_M(false),
        has_eps_bu(false),
        has_Rs(false),
        has_m(false){}
public slots:
    // Входы
    void set_b(double value);
    void set_h(double value);
    void set_h0(double value);
    void set_as(double value);
    void set_concrete(int index);
    void set_armature(int index);
    void set_M(double value);
    void set_eps_bu(double value);
    void set_m(double value);
    void update(void){check_params();};
signals:
    // Выходы
    void set_As(QString);
    void set_miu(QString);
    void set_ksi(QString);
    void set_A_0(QString);
    void set_lambda(QString);
    void set_sigma_s(QString);
};

#endif // COREADAPTER_H
