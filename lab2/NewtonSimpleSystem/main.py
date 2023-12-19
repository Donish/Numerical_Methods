from additional import *

# Выводим результаты с точностью 4 знака после запятой
np.set_printoptions(precision = 5, suppress = True)

# Метод простой итерации для решения системы нелинейных уравнений
def simple_iteration_method(phi1, phi2, x0, max_iterations, epsilon = 1e-3):
    """
    :param f1 (function): Первое уравнение системы.
    :param f2 (function): Второе уравнение системы.
    :param x0 (list): Начальное приближение.
    :param max_iterations (int): Количество итераций.
    :param epsilon (float): Точность вычислений.

    :return numpy.ndarray: Решение системы.
    """
    x = np.array(x0, dtype=float)
    i = 0

    for i in range(max_iterations):
        x1 = phi1(x[0], x[1])
        x2 = phi2(x[0], x[1])
        x_next = np.array([x1, x2])

        if np.linalg.norm(x_next - x) < epsilon:
            return x_next, i

        x = x_next

    print("Метод Простой итерации не сошелся за заданное количество итераций!")
    return x_next, i


# Метод Ньютона для решения системы нелинейных уравнений
def newton_method(f1, f2, df1_dx1, df1_dx2, df2_dx1, df2_dx2, x0, max_iterations, epsilon = 1e-3):
    """
    :param f1 (function): Первое уравнение системы.
    :param f2 (function): Второе уравнение системы.
    :param df1_dx1 (function): Частная производная первого уравнения по x1.
    :param df1_dx2 (function): Частная производная первого уравнения по x2.
    :param df2_dx1 (function): Частная производная второго уравнения по x1.
    :param df2_dx2 (function): Частная производная второго уравнения по x2.
    :param x0 (list): Начальное приближение.
    :param max_iterations (int): Количество итераций.
    :param epsilon (float): Точность вычислений.

    :return numpy.ndarray: Решение системы.
    """
    x = np.array(x0, dtype=float)
    i = 0

    for i in range(max_iterations):
        f = np.array([f1(x[0], x[1]), f2(x[0], x[1])])
        jacobian = np.array([[df1_dx1(x[0], x[1]), df1_dx2(x[0], x[1])],
                             [df2_dx1(x[0], x[1]), df2_dx2(x[0], x[1])]])

        try:
            #delta_x = np.linalg.solve(jacobian, -f)
            delta_x = solve_linear_system(jacobian, -f)
            x_next = x + delta_x
        except np.linalg.LinAlgError:
            print("Сингулярная матрица Якоби. Метод Ньютона не сработал")
            break

        if np.linalg.norm(delta_x) < epsilon:
            return x_next, i

        x = x_next

    print("Метод Ньютона не сошелся за заданное количество итераций!")
    return x_next, i


if __name__ == '__main__':
    x = [1.5, 1.2]
    # epsilon = 0.001
    print("Enter epsilon:")
    epsilon = float(input())
    max_iterations = 1000

    result_simple_iteration, count_simple_iteration = simple_iteration_method(phi1, phi2, x, max_iterations, epsilon)
    result_newton, count_newton = newton_method(f1, f2, df1_dx1, df1_dx2, df2_dx1, df2_dx2, x, max_iterations, epsilon)

    #Открываем файл для записи (существующий файл будет перезаписан)
    with open('../resources/system_output.txt', 'w') as file:
        # Перенаправляем вывод в файл
        sys.stdout = file

        # Выводим результаты
        print("Simple iterations:")
        print("x = ", result_simple_iteration, "\nIterations: ", count_simple_iteration)
        print("\nNewton:")
        print("x = ", result_newton, "\nIterations: ", count_newton)

    # Возвращаем вывод в консоль
    sys.stdout = sys.__stdout__

    # Тестирование в консоли
    # print("По методу простых итераций:")
    # print("корень =", result_simple_iteration, "за", count_simple_iteration, "итераций", "с точностью", epsilon)
    # print("\nПо методу Ньютона:")
    # print("корень =", result_newton, "за", count_newton, "итераций", "с точностью", epsilon)