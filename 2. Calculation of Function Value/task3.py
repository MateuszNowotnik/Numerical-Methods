import math


def f(x):
    return math.exp(x)


def fact(a):
    if a == 0:
        return 1
    return a * fact(a-1)


def derivative(x, order, eps):
    if order == 0:
        return f(x)
    elif order == 1:
        return (f(x+eps) - f(x-eps)) / (2*eps)
    else:
        return (derivative(x+eps, order-1, eps) - derivative(x-eps, order-1, eps)) / (2*eps)


def taylor_series(a, x, n, eps):
    series = 0.0
    for i in range(n+1):
        series += (derivative(a, i, eps)/fact(i))*((x-a)**i)
    return series


def trunc_error(a, h, n, eps):  # finding max using derivative n+2
    o = 0.001
    comp = abs(derivative(a+(o*h), n+1, eps))
    while o < 0.999:
        o += 0.001
        if abs(derivative(a+(o*h), n+1, eps)) > comp:
            comp = abs(derivative(a+(o*h), n+1, eps))
    return (comp/fact(n+1))*((abs(h))**(n+1))


def main():
    terms = int(input("Number of terms of Taylor series: "))
    a = int(input("Point a: "))
    x = float(input("Value of x: "))
    eps = float(input("What is the accuracy: "))  # accuracy (epsilon)

    result = taylor_series(a, x, terms, eps)
    print("\nA searched value is equal to: ", end="")
    print(result)

    t_error = trunc_error(a, x-a, terms, eps)
    print("With a truncation error of: ", end="")
    print(t_error)


if __name__ == '__main__':
    main()
