from PyQt5 import QtCore, QtGui
from PyQt5.QtCore import Qt, pyqtSignal
import numpy as np

"""
Класс DataModel обеспечивает хранение и обработку данных, а также их отображение в табличном виде.
"""
class DataModel(QtCore.QAbstractTableModel):

    def __init__(self):
        super().__init__()
        # Инициализация данных случайными значениями (5 строк, 3 столбца, значения от 1 до 4)
        self._data = np.random.randint(1, 5, (5, 3)).astype(float)
        # Обновление производных данных (пересчитанные и накопленные значения)
        self.updateData()

    """
    Возвращает количество строк в модели.
    """
    def rowCount(self, parent=None):

        return self._data.shape[0]

    """
    Возвращает количество столбцов в модели.
    """
    def columnCount(self, parent=None):
        
        return self._data.shape[1]

    """
    Возвращает данные для указанной роли и индекса.
    """
    def data(self, index, role=Qt.DisplayRole):

        # Для отображения и редактирования возвращаем значение ячейки
        if role in [Qt.DisplayRole, Qt.EditRole]:
            return float(self._data[index.row(), index.column()])

        # Для фона последнего столбца устанавливаем цвет в зависимости от значения
        if role == Qt.BackgroundRole and index.column() == self._data.shape[1] - 1:
            return QtGui.QBrush(QtGui.QColor("green") if self._data[index.row(), index.column()] >= 0 else QtGui.QColor("red"))

        return None

    """
    Устанавливает данные в модель по указанному индексу.
    """
    def setData(self, index, value, role=Qt.EditRole):
        # Разрешаем редактирование только для столбцов, кроме двух последних
        if role == Qt.EditRole and index.column() not in [self._data.shape[1] - 1, self._data.shape[1] - 2]:
            self._data[index.row(), index.column()] = float(value)
            self.updateData()
            # Эмитируем сигнал об изменении данных для всех ячеек
            self.dataChanged.emit(self.index(0, 0), self.index(self.rowCount() - 1, self.columnCount() - 1))
            return True
        return False

    """
    Возвращает флаги для указанного индекса.
    """
    def flags(self, index):
        if index.column() == 0:
            return Qt.ItemIsSelectable | Qt.ItemIsEnabled | Qt.ItemIsEditable
        else:
            return Qt.ItemIsSelectable | Qt.ItemIsEnabled 

    """
    Возвращает данные заголовка для указанной секции и ориентации.
    """
    def headerData(self, section, orientation, role=Qt.DisplayRole):
        
        if role == Qt.DisplayRole:
            if orientation == Qt.Horizontal:
                # Специальные названия для последних двух столбцов
                if section == self._data.shape[1] - 1:
                    return "Накопленные значения"
                elif section == self._data.shape[1] - 2:
                    return "Пересчитанные значения"
                return f"Столбец {section + 1}"
            elif orientation == Qt.Vertical:
                return str(section + 1)
        return None

    """
    Обновляет производные данные (пересчитанные и накопленные значения).
    """
    def updateData(self):
        rows, cols = self.rowCount(self), self.columnCount(self)
        result = np.zeros(rows)

        # Вычисление пересчитанных значений (сумма кубов значений в столбцах)
        for col in range(cols - 2):
            result += np.power(self._data[:, col], 3)

        self._data[:, cols - 2] = result
        self.dataChanged.emit(self.index(0, cols - 2), self.index(rows - 1, cols - 2))

        # Вычисление накопленных значений (кумулятивная сумма)
        accumulated_values = np.zeros(rows)
        for i in range(rows):
            accumulated_values[i] = np.sum(self._data[:i + 1, cols - 2])
        
        self._data[:, cols - 1] = accumulated_values
        self.dataChanged.emit(self.index(0, cols - 1), self.index(rows - 1, cols - 1))

    """
    Полностью заменяет данные модели новыми.
    """
    def changeData(self, data):
        self.beginResetModel()
        self._data = data.astype(float)
        self.updateData()
        self.endResetModel()

    """
    Заполняет указанный столбец случайными значениями.
    """
    def fillArr(self, col):
        if col == 0:
            # Для первого столбца - целые числа от 1 до 4
            self._data[:, col] = np.random.choice(range(1, 5), size=self._data.shape[0])
        else:
            # Для остальных столбцов - случайные числа от -10 до 10
            self._data[:, col] = np.round(np.random.uniform(-10, 10, size=self._data.shape[0]))

        self._data = self._data.astype(float)
        self.updateData()
        # Уведомление об изменении данных в столбце
        self.dataChanged.emit(self.index(0, col), self.index(self.rowCount() - 1, col))

        """
        Возвращает текущие данные модели.
        """
    def getData(self):
        return self._data