from additional import *

# Функция для нахождения коэффициентов многочлена МНК
def least_squares_polynomial(x, y, degree):
    n = len(x)
    A = np.zeros((degree + 1, degree + 1))
    B = np.zeros(degree + 1)

    # Заполняем матрицу A и вектор B
    for i in range(degree + 1):
        for j in range(degree + 1):
            A[i, j] = np.sum(x**(i + j))
        B[i] = np.sum(y * x**i)

    # Решаем нормальную систему уравнений для нахождения коэффициентов
    coefficients = solve_linear_system(A, B)
    return coefficients

# Функция для вычисления значения многочлена
def evaluate_polynomial(coefficients, x):
    degree = len(coefficients) - 1
    result = np.zeros_like(x)

    # Считаем значение многочлена
    for i in range(degree + 1):
        result += coefficients[i] * (x**i)

    return result

# Функция для вычисления суммы квадратов ошибок
def sum_of_squares_error(y_true, y_approx):
    return np.sum((y_true - y_approx)**2)


if __name__ == '__main__':
    # Таблично заданные данные
    x_i = np.array([0.0, 0.2, 0.4, 0.6, 0.8, 1.0])
    y_i = np.array([1.0, 1.0032, 1.0512, 1.2592, 1.8192, 3.0])

    # Проверка по методичке
    #x_i = np.array([0.0, 1.7, 3.4, 5.1, 6.8, 8.5])
    #y_i = np.array([0.0, 1.3038, 1.8439, 2.2583, 2.6077, 2.9155])

    # Для первой степени
    degree_1 = 1
    coefficients_1 = least_squares_polynomial(x_i, y_i, degree_1)
    y_approx_1 = evaluate_polynomial(coefficients_1, x_i)
    error_1 = sum_of_squares_error(y_i, y_approx_1)

    # Для второй степени
    degree_2 = 2
    coefficients_2 = least_squares_polynomial(x_i, y_i, degree_2)
    y_approx_2 = evaluate_polynomial(coefficients_2, x_i)
    error_2 = sum_of_squares_error(y_i, y_approx_2)

    # Открываем файл для записи
    with open('../resources/3-3.txt', 'w') as file:
        # Перенаправляем вывод в файл
        sys.stdout = file

        # Вывод результатов
        print(f'Коэффициенты многочлена 1-ой степени: {coefficients_1}')
        print(f'Сумма квадратов ошибок для 1-ой степени: {error_1}')
        print(f'Коэффициенты многочлена 2-ой степени: {coefficients_2}')
        print(f'Сумма квадратов ошибок для 2-ой степени: {error_2}')

    # Возвращаем вывод в консоль
    sys.stdout = sys.__stdout__

    # Тестирование в консоли
    # print(f'Коэффициенты многочлена 1-ой степени: {coefficients_1}')
    # print(f'Сумма квадратов ошибок для 1-ой степени: {error_1}')
    # print(f'Коэффициенты многочлена 2-ой степени: {coefficients_2}')
    # print(f'Сумма квадратов ошибок для 2-ой степени: {error_2}')


    # Построение графиков
    x_values = np.linspace(min(x_i), max(x_i), 100)
    y_true = np.interp(x_values, x_i, y_i)

    plt.scatter(x_i, y_i, label = 'Табличные данные')
    plt.plot(x_values, evaluate_polynomial(coefficients_1, x_values), label = f'Полином 1-ой степени')
    plt.plot(x_values, evaluate_polynomial(coefficients_2, x_values), label = f'Полином 2-ой степени')
    plt.plot(x_values, y_true, '--', label = 'Приближаемая функция')
    plt.legend()
    plt.show()