def boundary(a, n):
    x = 0
    while True:
        result = a[n]
        for i in reversed(a[:n]):
            result = result * x + i
            if result < 0:
                x += 0.01  # the accuracy
                break
        if result >= 0:
            break
    return x


def poly_for_below(a, n):
    if n % 2 != 0:
        a[0] = -a[0]
    for i in range(1, n+1):
        if (i % 2 != 0) and (n % 2 == 0) or (i % 2 == 0) and (n % 2 != 0):
            a[i] = -a[i]
    return a


def main():
    n = int(input("Degree of the polynomial: "))
    a = []  # create an array

    print("Give the coefficients of the polynomial: ")
    for c in range(0, n+1):
        a.append(float(input("")))

    u_bound = boundary(a, n)  # upper bound of roots values
    a = poly_for_below(a, n)  # change the polynomial
    l_bound = -boundary(a, n)  # lower bound

    print("All real roots of the polynomial are contained within the interval [", end="")
    print(round(l_bound, 2), end=", ")
    print(round(u_bound, 2), end="]")


if __name__ == '__main__':
    main()
