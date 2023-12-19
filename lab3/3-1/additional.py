import sys
import numpy as np
import matplotlib.pyplot as plt
from main import lagrange_interpolation
from main import newton_interpolation

# Функция, для которой строится интерполяционный многочлен
def f(x):
    # return np.tan(x) + x
    return np.sqrt(x)

# Построение графика и интерполяций
def draw_graph(x_i, y_i):
    # Построение графика
    # x_plot = np.linspace(0, 3 * np.pi / 8, 100)
    x_plot = np.linspace(0, 5.1, 100)
    y_true = f(x_plot)
    y_lagrange = lagrange_interpolation(x_i, y_i, x_plot)
    y_newton = newton_interpolation(x_i, y_i, x_plot)

    plt.plot(x_plot, y_true, label='Y = sqrt(x)')
    plt.scatter(x_i, y_i, color='red', label='Data Points')
    plt.plot(x_plot, y_lagrange, color='green', label='Lagrange Interpolation')
    plt.plot(x_plot, y_newton, color='yellow', label='Newton Interpolation')

    plt.title('Interpolation Comparison')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.legend()
    plt.show()