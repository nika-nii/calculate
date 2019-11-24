#ifndef CORE_H
#define CORE_H

class Core{
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
    // Выходы
    double As;
    double miu;
    double ksi;
    double A_0;
    double lambda;
    double sigma_S;
public:
    Core(
         double b,
         double B,
         double h,
         double h0,
         double as,
         double Rb,
         double Eb,
         double A,
         double Es,
         double M,
         double eps_bu,
         double Rs,
         double m
            ) : b(b), B(B), h(h), h0(h0), as(as), Rb(Rb), Eb(Eb), A(A), Es(Es), M(M), eps_bu(eps_bu), Rs(Rs), m(m) {}
    void calculate();
    double get_As() {return As;}
    double get_miu() {return miu;}
    double get_ksi() {return ksi;}
    double get_A_0() {return A_0;}
    double get_lambda() {return lambda;}
    double get_sigma_s() {return sigma_S;}
};

#endif // CORE_H
