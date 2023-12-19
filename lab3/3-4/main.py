import sys
import numpy as np


# Функция для вычисления первой производной
def first_derivative_forward(x, y, index):
    return (y[index] - y[index - 1]) / (x[index] - x[index - 1])

# Функция для вычисления первой производной со вторым порядком точности
def first_derivate_second_approximation(x, index, first_derivate_left, first_derivate_right):
    result = (first_derivate_left + ((first_derivate_right - first_derivate_left) / (x[index + 1] - x[index - 1])) *
              (x[index] - x[index - 1]))
    return result

# Функция для вычисления второй производной
def second_derivative_forward(x, index, first_derivate_left, first_derivate_right):
    temp = 2 * ((first_derivate_right - first_derivate_left) / (x[index + 1] - x[index - 1]))
    return temp


if __name__ == '__main__':
    # Табличные данные
    x_i = np.array([-0.2, 0.0, 0.2, 0.4, 0.6])
    y_i = np.array([1.7722, 1.5708, 1.3694, 1.1593, 0.9273])
    x_star = 0.2


    # x_i = np.array([0.0, 0.1, 0.2, 0.3, 0.4])
    # y_i = np.array([1.0, 1.1052, 1.2214, 1.3499, 1.4918])
    # x_star = 0.2

    # Индекс точки, в которой нужно вычислить производные
    index_at_x_star = np.where(x_i == x_star)[0][0]

    # Вычисление первой и второй производной в точке X = 3.0
    first_derivate_left = first_derivative_forward(x_i, y_i, index_at_x_star) #[index_at_x_3]
    first_derivate_right = first_derivative_forward(x_i, y_i, index_at_x_star + 1)  # [index_at_x_3]

    first_derivate_2 = first_derivate_second_approximation(x_i, index_at_x_star, first_derivate_left, first_derivate_right)
    second_derivate = second_derivative_forward(x_i, index_at_x_star, first_derivate_left, first_derivate_right)

    # Открываем файл для записи
    with open('../resources/3-4.txt', 'w') as file:
        # Перенаправляем вывод в файл
        sys.stdout = file

        # Вывод результатов
        print("Значения x:", x_i)
        print("Значения y:", y_i)
        print("X^* =", x_star)
        print(f'В первом приближении слева производная = {first_derivate_left}')
        print(f'В первом приближении справа производная = {first_derivate_right}')
        print(f'Во втором приближении производная в точке = {first_derivate_2}')
        print(f'Вторая производная в точке = {second_derivate}')

    # Возвращаем вывод в консоль
    sys.stdout = sys.__stdout__

    # Тестирование в консоли
    # print(f'В первом приближении слева в точке {x_star} производная = {first_derivate_left}')
    # print(f'В первом приближении справа в точке {x_star} производная = {first_derivate_right}')
    # print(f'Во втором приближении производная в точке {x_star} = {first_derivate_2}')
    # print(f'Вторая производная в точке {x_star} = {second_derivate}')