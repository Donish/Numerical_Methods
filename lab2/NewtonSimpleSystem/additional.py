import math
import sys
import numpy as np

# x1 = x1 - alpha * f(x1, x2)
def phi1(x1, x2):
    # x1 = phi2(x1, x2)
    # return math.sqrt(9 - ((9 * x2**2) / 2.25))
    # return math.exp(x2) - 2
    return math.sqrt(4 - math.pow(x2, 2))

def phi2(x1, x2):
    # x2 = phi1(x1, x2)
    # return (math.exp(x1) + x1) / 3
    # return math.sqrt(4 - math.pow(x1, 2))
    return math.log(x1 + 2)

def phi1_t(x1, x2):
    # X1 = x1 + l11 * f1 + l12 * f2
    # temp = x1 - 0.56 * (x1**2 / 9 + x2**2 / 2.25 - 1) + 0.2 * (3 * x2 - math.exp(x1) - x1)
    temp = x1 + 1.2 * (x1 - math.exp(x2) + 2) + 1.56 * (x1**2 + x2**2 - 4)
    return temp

def phi2_t(x1, x2):
    # X2 = x2 + l21 * f1 + l22 * f2
    # temp = x2 + 0.08 * (x1**2 / 9 + x2**2 / 2.25 - 1) + 0.77 * (3 * x2 - math.exp(x1) - x1)
    temp = x2 + 0.08 * (x1 - math.exp(x2) + 2) + 0.77 * (x1**2 + x2**2 - 4)
    return temp


def f1(x1, x2):
    return math.pow(x1, 2) + math.pow(x2, 2) - 4

def f2(x1, x2):
    return x1 - math.exp(x2) + 2

def df1_dx1(x1, x2):
    return 2 * x1

def df1_dx2(x1, x2):
    return 2 * x2

def df2_dx1(x1, x2):
    return 1

def df2_dx2(x1, x2):
    return -1 * math.exp(x2)


# Функция для решения системы линейных уравнений A * x = b методом Гаусса (из лабы 1.1)
def solve_linear_system(A, b):
    n = len(A)
    # Создаем копии матрицы A и вектора b
    U = A.copy()
    y = b.copy()

    # Прямой ход метода Гаусса
    for k in range(n):
        # Находим ведущий элемент
        pivot = U[k, k]
        # Обновляем строку k матрицы U и соответствующий элемент вектора y
        U[k, :] /= pivot
        y[k] /= pivot
        for i in range(k + 1, n):
            factor = U[i, k]
            U[i, :] -= factor * U[k, :]
            y[i] -= factor * y[k]

    # Обратный ход метода Гаусса
    x = np.zeros(n)
    for k in range(n - 1, -1, -1):
        x[k] = y[k]
        for i in range(k + 1, n):
            x[k] -= U[k, i] * x[i]

    return x
