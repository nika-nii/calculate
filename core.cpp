#include "core.h"

#include <cmath>

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
    }while (b-a > eps);
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
        if (r<=0.) {r=-r;sign=-1;}
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

void Core::calculate(){

//    double A,As,b,B,h,h0,as,w,ksi1,ksi2,gamma,Rb,Rbu,Mb,Ms,
//            Eb,Es,E0,E_T,E_R,eps_s,eps_T,eps_bu,x,lambda,
//            sigma_S,sigma_R,sigma_T,S,y,y1,y2,y3,
//            f1,f2,f3,M,m,Rs,miu,
//            z[3],a2, a1,a0,mt,f,v,
//            ln,t, t_ln, l4,zn,t1,t2,t3;
//    int k, i;

    /*b=20;B=15; h=40;h0=37; as=3; B=15; Rb=110; Eb=240000;
   A=400;Es=2E6;M=1200000;
   eps_bu=0.0025; Rs=4000;m=68.6;*/

    lambda=1/(1.25+0.0015*Rb);
    //printf("lambda=%lf\n",lambda);

    double Rbu=eps_bu*Eb/(1+lambda*eps_bu*Eb/Rb);
    //printf("Rbu=%lf\n",Rbu);

    eps_bu=Rbu/(Eb*(1-lambda*Rbu/Rb));
    //printf("eps_bu=%lf\n",eps_bu);

    double t=lambda*eps_bu*Eb;
    //printf("t=%lf\n",t);

    /* это временная переменная
   ui->tLabel->setText(QString::number(t));
   */

    t=Rbu/t;
    //printf("eps_T=%lf\n",eps_T);

    double ln=log(1+1/t);
    double t_ln=t*ln;
    double w=(1-t_ln)/lambda;
    //printf("w=%lf\n",w);

    double gamma=(0.5-t+t*t_ln)/(1-t_ln);
    // printf("gamma=%lf\n",gamma);

    t=1-gamma;
    double ksi2=0.5/t*(1-sqrt(1-4*M*t/(w*b*h0*h0*Rbu)));
    //printf("ksi2=%lf\n",ksi2);

    double l4=lambda*lambda;
    l4=l4*l4;
    double zn=l4*t;
    double a2=-(t+l4*(1+t))/zn;
    double a1=(1+l4)/zn;
    double a0=-M/(zn*w*b*h0*h0*Rb);
    double z[3];
    Cubic(z, a2,a1,a0);
    ksi2=z[0];
    int k=0;
    double ksi1;
    do{
        k++;
        ksi1=ksi2;
        t=lambda*lambda;
        t=t*t;
        Rbu=Rb*(1+t*(1-ksi1));
        // printf("Rbu=%lf\n",Rbu);

        eps_bu=Rbu/(Eb*(1-lambda*Rbu/Rb));
        // printf("eps_bu=%lf\n",eps_bu);

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

        // printf("eps_T=%lf\n",eps_T);

        gamma=(0.5-t+t*t_ln)/(1-t_ln);
        //printf("gamma=%lf\n",gamma);

        t=1-gamma;
        //ksi2=0.5/t*(1-sqrt(1-4*M*t/(w*b*h0*h0*Rbu)));
        // printf("ksi2=%lf\n",ksi2);

        l4=lambda*lambda;
        l4=l4*l4;
        zn=l4*t;
        a2=-(t+l4*(1+t))/zn;
        a1=(1+l4)/zn;
        a0=-M/(zn*w*b*h0*h0*Rb);
        k = Cubic(z, a2,a1,a0);
        ksi2=z[0];
        // printf("ksi2=%lf\n",ksi2);

    }while(fabs(ksi1-ksi2)>0.02);
    double eps_s=eps_bu*(1-ksi2)/ksi2;
    //printf("eps_s=eps_s%lf\n",eps_s);

    //printf("k=%i\n",k );

    /* временная переменная
   ui->kLabel->setText(QString::number(k));
   */

    //eps_s=0.00133;
    double eps_T=1.25*Rs/Es;
    //printf("eps_T=%lf\n",eps_T);

    double t1=m+0.2;
    double t2=3.2*m;
    double t3=1.6*eps_s*Es;
    //printf("t3=%le\n",t3);
    /* временная переменная
    * ui->t3Label->setText(QString::number(t3));
    */
    zn=bin_div(func,t1,t2,t3,Rs,-1,0,0.0001)+1;
    //printf("y=%leb=20;\n",zn);

    sigma_S=(zn)*Rs;
    //printf("sigma_S=%le\n",sigma_S);

    As=M/(h0*sigma_S*(1-ksi2*(1-gamma)));
    //printf("As=%le\n",As);

    miu=As*100/(b*h0);
    //printf("miu=%le\n",miu);
}
