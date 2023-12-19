import math
import sys
import numpy as np
# from additional_methods import *

# Выводим результаты с точностью 4 знака после запятой
np.set_printoptions(precision = 5, suppress = True)

# Решение нелинейного уравнения методом простой итерации.
def simple_iteration_solver(f, x0, epsilon, max_iterations = 1000):
    """
    :param f: Функция, представляющая уравнение f(x) = 0.
    :param x0: Начальное приближение для корня уравнения.
    :param epsilon: Допустимая погрешность (когда |f(x)| < epsilon, мы считаем, что решение найдено).
    :param max_iterations: Максимальное количество итераций.
    """

    x = x0
    iteration = 0

    while iteration < max_iterations:
        # Рассчитываем следующее приближение согласно методу простой итерации
        next_x = f(x)

        # Проверяем достижение необходимой точности
        if abs(next_x - x) < epsilon:
            return next_x, iteration

        x = next_x
        iteration += 1

    # Если не удалось достичь заданной точности за максимальное количество итераций
    raise Exception("Метод не сошелся после максимального числа итераций.")

# Решает уравнение f(x) = 0 с использованием метода Ньютона.
def newton_method(f, df, x0, epsilon = 1e-6, max_iterations = 1000):
    """
    :param f: Функция, уравнение f(x) = 0, которое нужно решить.
    :param df: Производная функции f.
    :param x0: Начальное приближение.
    :param epsilon: Точность, до которой нужно найти корень.
    :param max_iterations: Максимальное количество итераций.
    :return: Приближенное значение корня уравнения f(x) = 0.
    """

    x = x0
    iteration = 0

    while iteration < max_iterations:
        delta_x = f(x) / df(x)  # Вычисляем приращение с использованием производной
        x = x - delta_x

        # Проверяем точность
        if abs(delta_x) < epsilon:
            return x, iteration

        iteration += 1

    # Если не удалось достичь заданной точности за максимальное количество итераций
    raise ValueError("Метод Ньютона не сошелся. Увеличьте количество итераций или проверьте начальное приближение.")

# Исходная функция
def f(x):
    return math.pow(2, x) + math.pow(x, 2) - 2

# \phi(x) для метода простой итерации
def phi(x):
    return math.sqrt(2 - math.pow(2, x))

# Производная функции f(x)
def df(x):
    return (math.pow(2, x) * math.log(2)) + 2 * x


if __name__ == '__main__':

    x0 = 0.5
    # epsilon = 0.001
    print("Enter epsilon: ")
    epsilon = float(input())

    result_iteration, count_iteration = simple_iteration_solver(phi, x0, epsilon)
    result_newton, count_newton = newton_method(f, df, x0, epsilon)

    #Открываем файл для записи (существующий файл будет перезаписан)
    with open('../resources/NewtonSimple_output.txt', 'w') as file:
        # Перенаправляем вывод в файл
        sys.stdout = file

        # Выводим результаты
        print("Simple iterations:")
        print("x = ", result_iteration, "\nIterations: ", count_iteration, "\n")
        print("\nNewton:")
        print("x = ", result_newton, "\nIterations: ", count_newton, "\n")

    # Возвращаем вывод в консоль
    sys.stdout = sys.__stdout__

    # Тестирование в консоли
    # print("По методу простых итераций:")
    # print("корень =", result_iteration, "за", count_iteration, "итераций", "с точностью", epsilon)
    # print("\nПо методу Ньютона:")
    # print("корень =", result_newton, "за", count_newton, "итераций", "с точностью", epsilon)
