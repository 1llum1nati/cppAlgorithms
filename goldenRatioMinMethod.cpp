double goldenRatioMin(double a, double b) {
    double c, d;
    while (std::abs(b - a) >= eps) {
        c = b - (b - a) / phi;
        d = a + (b - a) / phi;
        (f(c) < f(d)) ? b = d : a = c;
    }
    return (a + b) / 2;
}