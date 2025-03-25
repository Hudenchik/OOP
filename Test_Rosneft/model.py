from PyQt5 import QtCore, QtGui
from PyQt5.QtCore import Qt, pyqtSignal
import numpy as np

class DataModel(QtCore.QAbstractTableModel):

    def __init__(self):
        super().__init__()
        self._data = np.random.randint(1, 5, (5, 3)).astype(float)
        self.updateData()

    def rowCount(self, parent=None):
        return self._data.shape[0]

    def columnCount(self, parent=None):
        return self._data.shape[1]

    def data(self, index, role=Qt.DisplayRole):
        if role in [Qt.DisplayRole, Qt.EditRole]:
            return float(self._data[index.row(), index.column()])

        if role == Qt.BackgroundRole and index.column() == self._data.shape[1] - 1:
            return QtGui.QBrush(QtGui.QColor("green") if self._data[index.row(), index.column()] >= 0 else QtGui.QColor("red"))

        return None

    def setData(self, index, value, role=Qt.EditRole):
        if role == Qt.EditRole and index.column() not in [self._data.shape[1] - 1, self._data.shape[1] - 2]:
            self._data[index.row(), index.column()] = float(value)
            self.updateData()
            self.dataChanged.emit(self.index(0, index.column()), self.index(self.rowCount() - 1, index.column()))
            return True
        return False

    def flags(self, index):
        return Qt.ItemIsSelectable | Qt.ItemIsEnabled | Qt.ItemIsEditable

    def headerData(self, section, orientation, role=Qt.DisplayRole):
        if role == Qt.DisplayRole:
            if orientation == Qt.Horizontal:
                if section == self._data.shape[1] - 1:
                    return "Накопленные значения"
                elif section == self._data.shape[1] - 2:
                    return "Пересчетанные значения"
                return f"Столбец {section + 1}"
            elif orientation == Qt.Vertical:
                return str(section + 1)
        return None

    def updateData(self):
        rows, cols = self.rowCount(self), self.columnCount(self)
        result = np.zeros(rows)

        for col in range(cols - 2):
            result += np.power(self._data[:, col], 3)

        self._data[:, cols - 2] = result
        self.dataChanged.emit(self.index(0, cols - 2), self.index(rows - 1, cols - 2))

        # Накопление значений
        accumulated_values = np.zeros(rows)
        for i in range(rows):
            accumulated_values[i] = np.sum(self._data[:i + 1, cols - 2])
        
        self._data[:, cols - 1] = accumulated_values
        self.dataChanged.emit(self.index(0, cols - 1), self.index(rows - 1, cols - 1))

    def changeData(self, data):
        self.beginResetModel()
        self._data = data.astype(float)
        self.updateData()
        self.endResetModel()

    def generateArr(self, col):
        if col == 0:
            self._data[:, col] = np.random.choice(range(1, 5), size=self._data.shape[0])
        else:
            self._data[:, col] = np.round(np.random.uniform(-10, 10, size=self._data.shape[0]))

        self._data = self._data.astype(float)
        self.updateData()
        self.dataChanged.emit(self.index(0, col), self.index(self.rowCount() - 1, col))

    def getData(self):
        return self._data
