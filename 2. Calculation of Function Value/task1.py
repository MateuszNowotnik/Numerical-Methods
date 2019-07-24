def horner(n, a, x0):
    result = a[n]
    for i in reversed(a[:n]):
        result = result * x0 + i
    return result


def general_form(a, x0):
    result = 0
    for i, j in enumerate(a):
        if j != 0:
            result = result + j * x0**i
    return result


def main():
    n = int(input("What is the order of the polynomial: "))
    a = []  # array of coefficients

    print("Give the coefficients of the polynomial: ")
    for c in range(0, n+1):
        a.append(float(input("")))  # append a coefficient of the polynomial into the array

    x0 = float(input("The value x0: "))

    print("The result using the Horner's method: ", end="")
    print(horner(n, a, x0))

    print("The result using the general form: ", end="")
    print(general_form(a, x0))


if __name__ == '__main__':
    main()
