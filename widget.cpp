#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QRegExp RegExp("^[-+]?[0-9]*[.,]?[0-9]+(?:[eE][-+]?[0-9]+)?$");
    QValidator *Validator = new QRegExpValidator(RegExp, this);

    ui->bEdit->setValidator(Validator);
    ui->BEdit->setValidator(Validator);
    ui->hEdit->setValidator(Validator);
    ui->h0Edit->setValidator(Validator);
    ui->AsEdit->setValidator(Validator);
    ui->RbEdit->setValidator(Validator);
    ui->EbEdit->setValidator(Validator);
    ui->AEdit->setValidator(Validator);
    ui->EsEdit->setValidator(Validator);
    ui->MEdit->setValidator(Validator);
    ui->eps_buEdit->setValidator(Validator);
    ui->RsEdit->setValidator(Validator);
    ui->mEdit->setValidator(Validator);
}

Widget::~Widget()
{
    delete ui;
}


#define M_PI (3.141592653589793)
#define M_2PI (2.*M_PI)
typedef double (*t_pf)(double,double,double,double,double);


double bin_div(t_pf pf, double t1, double t2, double t3, double Rs,double a, double b, double eps){
    double c;
    do{
        c=(a+b)/2;
        if (pf(a,t1,t2,t3,Rs)*pf(c,t1,t2,t3,Rs) < 0)
            b = c;
        else
            a = c;
    }while (b-a>eps);
    return c;
}

double func(double zn,double t1,double t2,double t3,double Rs){
    double t,x,v;
    x=1+t1*zn;
    t=x+sqrt(x*x-t2*zn);
    v=(zn+1)*Rs*t-t3;
    return v;
}

int Cubic(double *x,double a,double b,double c) {
    double q,r,r2,q3;
    q=(a*a-3.*b)/9.; r=(a*(2.*a*a-9.*b)+27.*c)/54.;
    r2=r*r; q3=q*q*q;
    if(r2<q3){
        double t=acos(r/sqrt(q3));
        a/=3.; q=-2.*sqrt(q);
        x[0]=q*cos(t/3.)-a;
        x[1]=q*cos((t+M_2PI)/3.)-a;
        x[2]=q*cos((t-M_2PI)/3.)-a;
        return(3);
    }else {
        double aa,bb;
        int sign=1;
        if (r<=0.) {r=-r;sign=-1;};
        aa=-sign*pow(r+sqrt(r2-q3),1./3.);
        if(aa!=0.) bb=q/aa;
        else bb=0.;
        a/=3.; q=aa+bb; r=aa-bb;
        x[0]=q-a;
        x[1]=(-0.5)*q-a;
        x[2]=(sqrt(3.)*0.5)*fabs(r);
        if(x[2]==0.) return(2);
        return(1);
    }
}

void Widget::slotCalculate(){

    double A,As,b,B,h,h0,as,w,ksi1,ksi2,gamma,Rb,Rbu,Mb,Ms,
            Eb,Es,E0,E_T,E_R,eps_s,eps_T,eps_bu,x,lambda,
            sigma_S,sigma_R,sigma_T,S,y,y1,y2,y3,
            f1,f2,f3,M,m,Rs,miu,
            z[3],a2, a1,a0,mt,f,v,
            ln,t, t_ln, l4,zn,t1,t2,t3;
    int k, i;

    /*b=20;B=15; h=40;h0=37; as=3; B=15; Rb=110; Eb=240000;
   A=400;Es=2E6;M=1200000;
   eps_bu=0.0025; Rs=4000;m=68.6;*/


    if (ui->bEdit->text() == ""){
        ui->bEdit->setFocus(Qt::OtherFocusReason);
        return;
    }
    b = ui->bEdit->text().toDouble();

    if (ui->BEdit->text() == ""){
        ui->BEdit->setFocus(Qt::OtherFocusReason);
        return;
    }
    B = ui->hEdit->text().toDouble();

    if (ui->hEdit->text() == ""){
        ui->hEdit->setFocus(Qt::OtherFocusReason);
        return;
    }
    h = ui->hEdit->text().toDouble();

    if (ui->h0Edit->text() == ""){
        ui->h0Edit->setFocus(Qt::OtherFocusReason);
        return;
    }
    h0 = ui->h0Edit->text().toDouble();

    if (ui->AsEdit->text() == ""){
        ui->AsEdit->setFocus(Qt::OtherFocusReason);
        return;
    }
    As = ui->AsEdit->text().toDouble();

    if (ui->RbEdit->text() == ""){
        ui->RbEdit->setFocus(Qt::OtherFocusReason);
        return;
    }
    Rb = ui->RbEdit->text().toDouble();

    if (ui->EbEdit->text() == ""){
        ui->EbEdit->setFocus(Qt::OtherFocusReason);
        return;
    }
    Eb = ui->EbEdit->text().toDouble();

    if (ui->AEdit->text() == ""){
        ui->AEdit->setFocus(Qt::OtherFocusReason);
        return;
    }
    A = ui->AEdit->text().toDouble();

    if (ui->EsEdit->text() == ""){
        ui->EsEdit->setFocus(Qt::OtherFocusReason);
        return;
    }
    Es = ui->EsEdit->text().toDouble();

    if (ui->MEdit->text() == ""){
        ui->MEdit->setFocus(Qt::OtherFocusReason);
        return;
    }
    M = ui->MEdit->text().toDouble();

    if (ui->eps_buEdit->text() == ""){
        ui->eps_buEdit->setFocus(Qt::OtherFocusReason);
        return;
    }
    eps_bu = ui->eps_buEdit->text().toDouble();

    if (ui->RsEdit->text() == ""){
        ui->RsEdit->setFocus(Qt::OtherFocusReason);
        return;
    }
    Rs = ui->RsEdit->text().toDouble();

    if (ui->mEdit->text() == ""){
        ui->mEdit->setFocus(Qt::OtherFocusReason);
        return;
    }
    m = ui->mEdit->text().toDouble();

    lambda=1/(1.25+0.0015*Rb);
    //printf("lambda=%lf\n",lambda);

    ui->lambdaLabel->setText(QString::number(lambda));

    Rbu=eps_bu*Eb/(1+lambda*eps_bu*Eb/Rb);
    //printf("Rbu=%lf\n",Rbu);

    ui->RbuLabel->setText(QString::number(Rbu));

    eps_bu=Rbu/(Eb*(1-lambda*Rbu/Rb));
    //printf("eps_bu=%lf\n",eps_bu);

    ui->eps_buLabel->setText(QString::number(eps_bu));

    t=lambda*eps_bu*Eb;
    //printf("t=%lf\n",t);

    /* это временная переменная
   ui->tLabel->setText(QString::number(t));
   */

    t=Rbu/t;
    //printf("eps_T=%lf\n",eps_T);   ln=log(1+1/t);

    ui->eps_TLabel->setText(QString::number(eps_T));

    t_ln=t*ln;
    w=(1-t_ln)/lambda;
    //printf("w=%lf\n",w);

    ui->wLabel->setText(QString::number(w));

    gamma=(0.5-t+t*t_ln)/(1-t_ln);
    // printf("gamma=%lf\n",gamma);

    ui->gammaLabel->setText(QString::number(gamma));

    t=1-gamma;
    ksi2=0.5/t*(1-sqrt(1-4*M*t/(w*b*h0*h0*Rbu)));
    //printf("ksi2=%lf\n",ksi2);

    ui->ksi2Label->setText(QString::number(ksi2));

    l4=lambda*lambda;
    l4=l4*l4;
    zn=l4*t;
    a2=-(t+l4*(1+t))/zn;
    a1=(1+l4)/zn;
    a0=-M/(zn*w*b*h0*h0*Rb);
    Cubic(z, a2,a1,a0);
    ksi2=z[0];
    k=0;
    do
    { k++;
        ksi1=ksi2;
        t=lambda*lambda;
        t=t*t;
        Rbu=Rb*(1+t*(1-ksi1));
        // printf("Rbu=%lf\n",Rbu);

        ui->RbuLabel->setText(QString::number(Rbu));

        eps_bu=Rbu/(Eb*(1-lambda*Rbu/Rb));
        // printf("eps_bu=%lf\n",eps_bu);

        ui->eps_buLabel->setText(QString::number(eps_bu));

        t=lambda*eps_bu*Eb;
        //printf("t=%lf\n",t);

        /* временная переменная
     ui->tLabel->setText(QString::number(t));
     */
        t=Rbu/t;
        ln=log(1+1/t);
        t_ln=t*ln;
        w=(1-t_ln)/lambda;
        //printf("w=%lf\n",w);

        ui->wLabel->setText(QString::number(w));

        // printf("eps_T=%lf\n",eps_T);

        ui->eps_TLabel->setText(QString::number(eps_T));

        gamma=(0.5-t+t*t_ln)/(1-t_ln);
        //printf("gamma=%lf\n",gamma);

        ui->gammaLabel->setText(QString::number(gamma));

        t=1-gamma;
        //ksi2=0.5/t*(1-sqrt(1-4*M*t/(w*b*h0*h0*Rbu)));
        // printf("ksi2=%lf\n",ksi2);

        ui->ksi2Label->setText(QString::number(ksi2));

        l4=lambda*lambda;
        l4=l4*l4;
        zn=l4*t;
        a2=-(t+l4*(1+t))/zn;
        a1=(1+l4)/zn;
        a0=-M/(zn*w*b*h0*h0*Rb);
        k = Cubic(z, a2,a1,a0);
        ksi2=z[0];
        // printf("ksi2=%lf\n",ksi2);

        ui->ksi2Label->setText(QString::number(ksi2));

    }
    while(fabs(ksi1-ksi2)>0.02);
    eps_s=eps_bu*(1-ksi2)/ksi2;
    //printf("eps_s=eps_s%lf\n",eps_s);

    ui->eps_sLabel->setText(QString::number(eps_s));

    //printf("k=%i\n",k );

    /* временная переменная
   ui->kLabel->setText(QString::number(k));
   */

    //eps_s=0.00133;
    eps_T=1.25*Rs/Es;
    //printf("eps_T=%lf\n",eps_T);

    ui->eps_TLabel->setText(QString::number(eps_T));

    t1=m+0.2;
    t2=3.2*m;
    t3=1.6*eps_s*Es;
    //printf("t3=%le\n",t3);
    /* временная переменная
    * ui->t3Label->setText(QString::number(t3));
    */
    zn=bin_div(func,t1,t2,t3,Rs,-1,0,0.0001)+1;
    //printf("y=%leb=20;\n",zn);

    ui->yLabel->setText(QString::number(zn));

    sigma_S=(zn)*Rs;
    //printf("sigma_S=%le\n",sigma_S);

    ui->sigma_SLabel->setText(QString::number(sigma_S));

    As=M/(h0*sigma_S*(1-ksi2*(1-gamma)));
    //printf("As=%le\n",As);

    ui->AsLabel->setText(QString::number(As));

    miu=As*100/(b*h0);
    //printf("miu=%le\n",miu);

    ui->miuLabel->setText(QString::number(miu));

}
