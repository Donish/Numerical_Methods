from additional import *

# Вычисление интерполяционного многочлена Лагранжа
def lagrange_interpolation(x_i, y_i, x):
    result = 0.0
    n = len(x_i)
    polynomial = ""
    # tmp = 1.0

    # цикл подсчета w'(x_i), f_i / w'(x_i) и L_i(x)
    for i in range(n):
        term = y_i[i]
        for j in range(n):
            if j != i:
                term = term * (x - x_i[j]) / (x_i[i] - x_i[j])
        result += term

    return result


# Вычисление интерполяционного многочлена Ньютона
def newton_interpolation(x_i, y_i, x):
    n = len(x_i)
    coeffs = y_i.copy()

    for i in range(1, n):
        for j in range(n - 1, i - 1, -1):
            coeffs[j] = (coeffs[j] - coeffs[j - 1]) / (x_i[j] - x_i[j - i])

    result = 0.0
    term = 1.0

    for i in range(n):
        result += coeffs[i] * term
        term *= (x - x_i[i])

    return result


if __name__ == '__main__':
    # Заданные точки
    # x_i = np.array([0, np.pi / 8, 2 * np.pi / 8, 3 * np.pi / 8], dtype=float)
    x_i = np.array([0, 1.7, 3.4, 5.1], dtype=float)
    #x_i = np.array([0, np.pi / 8, np.pi / 3, 3 * np.pi / 8], dtype=float) # буква б)
    # x_i = np.array([0, 1.7, 4.0, 5.1], dtype=float)  # буква б)
    y_i = f(x_i)

    # Точка, для которой нужно вычислить интерполяцию
    # x_star = 3 * np.pi / 16
    x_star = 1.7
    # Вычисление интерполяционных значений
    lagrange_result = lagrange_interpolation(x_i, y_i, x_star)
    newton_result = newton_interpolation(x_i, y_i, x_star)

    # Открываем файл для записи (существующий файл будет перезаписан)
    with open('../resources/3-1.txt', 'w') as file:
        # Перенаправляем вывод в файл
        sys.stdout = file

        # Вывод результатов
        # print(f"Lagrange polynomial: {lagrange_string}")
        print("Значения x:", x_i)
        print("Значения функции в xi:", y_i)
        print("X^* =", x_star)
        print(f"Lagrange = {lagrange_result} with error rate = {f(x_star) - lagrange_result}")
        print(f"Newton = {newton_result} with error rate = {f(x_star) - newton_result}")

    # Возвращаем вывод в консоль
    sys.stdout = sys.__stdout__

    # Тестирование в консоли
    # print(f"Интерполяция Лагранжа = {lagrange_result} с погрешностью = {f(x_star) - lagrange_result}")
    # print(f"Иинтерполяция Ньютона = {newton_result} с погрешностью = {f(x_star) - newton_result}")

    # Построение графика
    #draw_graph(x_i, y_i)