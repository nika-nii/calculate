// IN
   b=20;
   B=15;
   h=40;
   h0=37;
   as=3;
   B=15;
   Rb=110;
   Eb=240000;
   A=400;
   Es=2E6;
   M=1200000;
   eps_bu=0.0025;
   Rs=4000;
   m=68.6;

//OUT
    printf("lambda=%lf\n",lambda);
    printf("Rbu=%lf\n",Rbu);
    printf("eps_bu=%lf\n",eps_bu);
    printf("eps_T=%lf\n",eps_T);   
    printf("t=%lf\n",t);
    printf("w=%lf\n",w);
    printf("gamma=%lf\n",gamma);
    printf("ksi2=%lf\n",ksi2);
    printf("eps_s=eps_s%lf\n",eps_s);
    printf("k=%i\n",k );
    printf("t3=%le\n",t3);
    printf("y=%leb=20;\n",zn);
    printf("sigma_S=%le\n",sigma_S);
    printf("As=%le\n",As);
    printf("miu=%le\n",miu);



   lambda=1/(1.25+0.0015*Rb);
   Rbu=eps_bu*Eb/(1+lambda*eps_bu*Eb/Rb);
   eps_bu=Rbu/(Eb*(1-lambda*Rbu/Rb));
   t=lambda*eps_bu*Eb;
   t=Rbu/t;
   ln=log(1+1/t);
   t_ln=t*ln;
   w=(1-t_ln)/lambda;
   gamma=(0.5-t+t*t_ln)/(1-t_ln);
   t=1-gamma;
   ksi2=0.5/t*(1-sqrt(1-4*M*t/(w*b*h0*h0*Rbu)));
   l4=lambda*lambda;
   l4=l4*l4;
   zn=l4*t;
   a2=-(t+l4*(1+t))/zn;
   a1=(1+l4)/zn;
   a0=-M/(zn*w*b*h0*h0*Rb);
   Cubic(z, a2,a1,a0);
   ksi2=z[0];
   k=0;
   do{
        k++;
        ksi1=ksi2;
        t=lambda*lambda;
        t=t*t;
        Rbu=Rb*(1+t*(1-ksi1));
        eps_bu=Rbu/(Eb*(1-lambda*Rbu/Rb));
        t=lambda*eps_bu*Eb;
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
        printf("ksi2=%lf\n",ksi2);
    }while(fabs(ksi1-ksi2)>0.02);
    eps_s=eps_bu*(1-ksi2)/ksi2;
    printf("eps_s=eps_s%lf\n",eps_s);
    printf("k=%i\n",k );
    //eps_s=0.00133;
    eps_T=1.25*Rs/Es;
    printf("eps_T=%lf\n",eps_T);
    t1=m+0.2;
    t2=3.2*m;
    t3=1.6*eps_s*Es;
    //printf("t3=%le\n",t3);
    zn=bin_div(func,t1,t2,t3,Rs,-1,0,0.0001)+1;
    //printf("y=%leb=20;\n",zn);
    sigma_S=(zn)*Rs;
    printf("sigma_S=%le\n",sigma_S);
    As=M/(h0*sigma_S*(1-ksi2*(1-gamma)));
    printf("As=%le\n",As);
    miu=As*100/(b*h0);
    printf("miu=%le\n",miu);


int main()
{
   double A,As,b,B,h,h0,as,w,ksi1,ksi2,gamma,Rb,Rbu,Mb,Ms,
          Eb,Es,E0,E_T,E_R,eps_s,eps_T,eps_bu,x,lambda,
          sigma_S,sigma_R,sigma_T,S,y,y1,y2,y3,
          f1,f2,f3,M,m,Rs,miu,
          z[3],a2, a1,a0,mt,f,v,
          ln,t, t_ln, l4,zn,t1,t2,t3;
  int k, i;




}


