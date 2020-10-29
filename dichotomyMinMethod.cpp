double dichotomyMin(double a, double b){
    double x = 0;
    while (std::abs(b - a) > eps){
        x = (a + b) / 2;
        (f(x - eps) < f(x + eps)) ? b = x : a = x;
    }
    return (a + b) / 2;
}