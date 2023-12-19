import sys
import numpy as np

# Определенная функция
def f(x):
    # return 1 / (x**4 + 16)
    return 1 / (3 * x**2 + 4 * x + 2)

# Функция из методички
# def f(x):
#     return x / ((3 * x + 4)**2)

# Метод средних прямоугольников
def rectangle_method(a, b, h):

    x_i = np.arange(a, b, h) # делим на отрезки по h
    midpoints = (x_i + x_i + h) / 2 # разбиваем на середины + h
    y_i = f(midpoints)
    result = h * np.sum(y_i)

    return result

# Метод трапеций
def trapezoidal_method(a, b, h):

    x_i = np.arange(a, b + h, h)
    y_i = f(x_i)

    inner_sum = np.sum(y_i[1:-1])
    result = h * (y_i[0] / 2 + inner_sum + y_i[-1] / 2)

    return result

# Метод Симпсона
def simpsons_method(a, b, h):

    x_i = np.arange(a, b + h, h)
    y_i = f(x_i)

    inner_sum_odd = np.sum(y_i[1:-1:2])
    inner_sum_even = np.sum(y_i[2:-2:2])

    # Умножаем значения функции в точках с нечетными индексами на 4 * h/3, с четными индексами на 2 * h/3
    result = h / 3 * (y_i[0] + 4 * inner_sum_odd + 2 * inner_sum_even + y_i[-1])

    return result

# Метод Рунге-Ромберга для оценки погрешности
def runge_romberg_method(result_h1, result_h2, p):
    return result_h2 + (result_h2 - result_h1) / (2**p - 1)


if __name__ == '__main__':
    # Заданный интервал интегрирования
    a, b = -2.0, 2.0
    y_true = 1.85741868721875

    # Шаги для методов с разной точностью
    h1, h2 = 1.0, 0.5

    # Тестирование по методичке
    # a, b = -1.0, 1.0
    # y_true = -0.16474


    # Вычисление интегралов
    result_rectangle_h1 = rectangle_method(a, b, h1)
    result_rectangle_h2 = rectangle_method(a, b, h2)

    result_trapezoidal_h1 = trapezoidal_method(a, b, h1)
    result_trapezoidal_h2 = trapezoidal_method(a, b, h2)

    result_simpsons_h1 = simpsons_method(a, b, h1)
    result_simpsons_h2 = simpsons_method(a, b, h2)

    # Оценка погрешности с использованием Метода Рунге-Ромберга
    p = 2  # порядок метода
    estimated_error_rectangle = runge_romberg_method(result_rectangle_h1, result_rectangle_h2, p)
    estimated_error_trapezoidal = runge_romberg_method(result_trapezoidal_h1, result_trapezoidal_h2, p)
    estimated_error_simpsons = runge_romberg_method(result_simpsons_h1, result_simpsons_h2, p)

    # Открываем файл для записи
    with open('../resources/3-5.txt', 'w') as file:
        # Перенаправляем вывод в файл
        sys.stdout = file

        # Вывод результатов
        print(f"Метод прямоугольников (h = {h1}): {result_rectangle_h1}")
        print(f"Погрешность: {estimated_error_rectangle}\n")
        print(f"Метод прямоугольников (h = {h2}): {result_rectangle_h2}")
        print(f"Погрешность: {estimated_error_rectangle - y_true}\n\n")

        print(f"Метод трапеций (h = {h1}): {result_trapezoidal_h1}")
        print(f"Погрешность: {estimated_error_trapezoidal}\n")
        print(f"Метод трапеций (h = {h2}): {result_trapezoidal_h2}")
        print(f"Погрешность: {estimated_error_trapezoidal - y_true}\n\n")

        print(f"Метод Симпсона (h = {h1}): {result_simpsons_h1}")
        print(f"Погрешность: {estimated_error_simpsons}\n")
        print(f"Метод Симпсона (h = {h2}): {result_simpsons_h2}")
        print(f"Погрешность: {estimated_error_simpsons - y_true}\n\n")

    # Возвращаем вывод в консоль
    sys.stdout = sys.__stdout__


    # Тестирование в консоли
    # print(f"Результат метода прямоугольников (h = {h1}): {result_rectangle_h1}")
    # print(f"Оценка погрешности: {estimated_error_rectangle}\n")
    # print(f"Результат метода прямоугольников (h = {h2}): {result_rectangle_h2}")
    # print(f"Оценка погрешности: {estimated_error_rectangle - y_true}\n\n")
    #
    # print(f"Результат метода трапеций (h = {h1}): {result_trapezoidal_h1}")
    # print(f"Оценка погрешности: {estimated_error_trapezoidal}\n")
    # print(f"Результат метода трапеций (h = {h2}): {result_trapezoidal_h2}")
    # print(f"Оценка погрешности: {estimated_error_trapezoidal - y_true}\n\n")
    #
    # print(f"Результат метода Симпсона (h = {h1}): {result_simpsons_h1}")
    # print(f"Оценка погрешности: {estimated_error_simpsons}\n")
    # print(f"Результат метода Симпсона (h = {h2}): {result_simpsons_h2}")
    # print(f"Оценка погрешности: {estimated_error_simpsons - y_true}\n\n")