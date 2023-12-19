import sys
import numpy as np
import matplotlib.pyplot as plt


# Функция для решения системы линейных уравнений A * x = b методом Гаусса
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