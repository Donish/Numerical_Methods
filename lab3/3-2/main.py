from additional import *

def cubic_spline_coefficients(x, y):
    n = len(x)
    h = np.diff(x)
    b = np.diff(y) / h

    # Решение системы линейных уравнений для коэффициентов сплайна
    A = np.zeros((n - 2, n - 2))
    np.fill_diagonal(A, 2 * (h[:-1] + h[1:]))
    A[np.arange(n - 3), np.arange(n - 3) + 1] = h[1:-1]
    A[np.arange(n - 3) + 1, np.arange(n - 3)] = h[1:-1]

    # Вычисление вектора правой части системы
    r = 6 * (b[1:] - b[:-1]) / (h[:-1] + h[1:])
    c = solve_linear_system(A, r)
    c = np.insert(c, 0, 0.0)

    # Вычисление остальных коэффициентов сплайна
    a = y[:-1]
    d = np.zeros_like(a)
    d = ((c[1:] - c[:-1]) / (3 * h[1:]))
    d = np.append(d, c[-1] / (3 * h[-1]))

    b = ((y[1:-1] - y[:-2]) / h[:-1]) - (h[:-1] / 3 * (c[1:] + 2 * c[:-1]))

    b = np.append(b, (((y[-1] - y[-2]) / h[-1]) - (2 * h[-1] * c[-1] / 3 )))

    return a, b, c, d

def cubic_spline_eval(x, x_i, a, b, c, d):
    # Находим индекс интервала
    i = np.searchsorted(x_i, x) - 1
    i = np.clip(i, 0, len(x_i) - 2)

    # Оценка значения сплайна в точке x
    dx = x - x_i[i]
    result = a[i] + b[i] * dx + c[i] * dx ** 2 + d[i] * dx ** 3

    return result

if __name__ == '__main__':
    # Заданные точки
    x_i = np.array([0.0, 1.7, 3.4, 5.1, 6.8], dtype = float)
    y_i = np.array([0.0, 1.3038, 1.8439, 2.2583, 2.6077], dtype = float)

    # Точка, для которой нужно вычислить интерполяцию
    x_star = 3.0

    # # Проверка по методичке
    # x_i = np.array([0.0, 1.0, 2.0, 3.0, 4.0], dtype = float)
    # y_i = np.array([0.0, 1.8415, 2.9093, 3.1411, 3.2432], dtype = float)
    #
    # # Точка, для которой нужно вычислить интерполяцию
    # x_star = 1.5

    # Вычисление коэффициентов и сплайна в точке
    a, b, c, d = cubic_spline_coefficients(x_i, y_i)
    # Оцениваем значение сплайна в точке x_star
    result = cubic_spline_eval(x_star, x_i, a, b, c, d)

    # Открываем файл для записи (существующий файл будет перезаписан)
    with open('../resources/3-2.txt', 'w') as file:
        # Перенаправляем вывод в файл
        sys.stdout = file

        print("Значения x: ", end='')
        for i in x_i:
            print(i, end=' ')
        print()
        print("Значения f: ", end='')
        for i in y_i:
            print(i, end=' ')
        print()
        # print("Коэффициент a:", a)
        # print("Коэффициент b:", b)
        # print("Коэффициент c:", c)
        # print("Коэффициент d:", d)
        # Вывод результатов
        print(f"Сплайн в точке {x_star} = {result}")

    # Возвращаем вывод в консоль
    sys.stdout = sys.__stdout__

    # Тестирование в консоли
    # print(f"Значение сплайна в точке {x_star} = {result}")