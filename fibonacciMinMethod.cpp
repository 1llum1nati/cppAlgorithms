double fibonacciMin(double a, double b,int n) {
    int *fibValues = new int[n];
    fibValues[0] = 1; fibValues[1] = 1;
    for (int i = 2; i < n; ++i)
        fibValues[i] = fibValues[i - 1] + fibValues[i - 2];

    double x1, x2;
    for (int i = 1; i < n - 2; i++) {
        x1 = a + ((double)fibValues[n - i - 2] / fibValues[n - i]) * (b - a);
        x2 = a + ((double)fibValues[n - i - 1] / fibValues[n - i]) * (b - a);

        (f(x1) > f(x2)) ? a = x1 : b = x2;
    }
    return (a + b) / 2;
}
