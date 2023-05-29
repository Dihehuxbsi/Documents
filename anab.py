import numpy as np
# Запросить у пользователя количество столбцов матрицы
n = int(input("Введите количество столбцов матрицы: "))
# Рассчитать количество строк матрицы
m = 2 ** n
# Создать матрицу планирования эксперимента
matrix = np.ones((m, n))
# Разбить матрицу на блоки и заполнить их значениями -1
for j in range(n):
    block_size = 2 ** j
    block_repeats = m // (2 * block_size)
    block = np.repeat(np.array([-1, 1]), block_size)
    block = np.tile(block, block_repeats)
    block = np.resize(block, m)  # изменить размерность массива
    matrix[:, j] = block
# Вывести результат
print("Матрица планирования эксперимента:")
print(matrix)
matrix2 = matrix + 10
print(matrix2)

#СДЕЛАЙ ТАК ЧТОБЫ ЧИСЛО H БЫЛО КАЖДЫЙ РАЗ НОВОЕ
# Создаем новую матрицу
new_matrix = np.zeros((matrix2.shape[0], 1))
for i in range(matrix2.shape[0]):
    # Создаем число по закону нормального распределения
    h = np.random.normal(0, 0.5)
    # Возводим все элементы матрицы в квадрат
    squared_row = np.square(matrix2[i])
    # Суммируем квадраты элементов и случайное число
    sum_sq_h = np.sum(squared_row) + h
    # Добавляем значение в новую матрицу
    new_matrix[i, 0] = sum_sq_h
# Выводим новую матрицу
print(new_matrix)
# Создаем новый массив для результатов
result_array = np.zeros((1, n))
# Вычисляем произведение каждого столбца матрицы на столбец новой матрицы и делим на количество строк матрицы matrix
for j in range(n):
    column_product = np.dot(matrix[:, j], new_matrix[:, 0]) / m
    result_array[0, j] = column_product
# Выводим результат
print("Результат произведения столбцов матрицы на столбец новой матрицы:")
print(result_array)