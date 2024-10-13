#include <iostream>
#include <math.h>



class Func{
private:
    double a0, a1, a2, a3, a4;
public:    
    void setKoef(double a0, double a1, double a2, double a3, double a4){
        this->a0 = a0;
        this->a1 = a1;
        this->a2 = a2;
        this->a3 = a3;
        this->a4 = a4;
    }
    double calcFunc(double x){
        return 1/(this->a0 + x*(this->a1 + x* (this->a2 + x*(this->a3 + x*this->a4))));
            
    }
};



double count_area(Func& f, double a, double b){
    return ((b-a)/6) * (f.calcFunc(a) + 4 * f.calcFunc((a+b)/2) + f.calcFunc(b));
}


double integral(Func& f, double a, double b, double Eps){
    double mid = (a+b)/2;
    double I1 = count_area(f, a, b);
    
    double I2 = 0;
    
    int n = 5;
    double h = (b - a) / n;
    for (size_t i = 0; i < n; ++i) {
        I2 += count_area(f, a + i * h, a + (i + 1) * h);
    }
    
    if (fabs(I1-I2) < Eps){
        return I2;
    }

    return integral(f, a, mid, Eps/2) + integral(f, mid, b, Eps/2);
}

double integralCalc(Func& f, double A, double B){
    double ans = 0;
    int n = 1e7;
    double h = (B - A) / n;
    for (size_t i = 0; i < n; ++i) {
        ans += integral(f, A + i * h, A + (i + 1) * h, 1e-9);
    }
    return ans;
}

int main(){
    double a0, a1, a2, a3, a4;
    Func func;
    std::cin >> a0;
    std::cin >> a1;
    std::cin >> a2;
    std::cin >> a3;
    std::cin >> a4;
    func.setKoef(a0, a1, a2, a3, a4);
    

    double A = -1e9;
    double B = 1e9;

    
    

    printf("%.11lf\n", integralCalc(func, A, B));
    return 0;
}