from PyQt5.QtCore import Qt
from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QMainWindow, QVBoxLayout, QHBoxLayout, QPushButton, QTableView, QWidget, QInputDialog, QMessageBox, QFileDialog
import pyqtgraph as pq
import numpy as np

from model import DataModel

class ComboBoxDelegate(QtWidgets.QStyledItemDelegate):

    def createEditor(self, parent, option, index):
        editor = QtWidgets.QComboBox(parent)
        editor.addItems([str(i) for i in range(1,6)])
        return editor
    
    def setEditorData(self, editor, index):
        value = int(index.model().data(index, Qt.EditRole))
        editor.setCurrentText(str(value))

    def setModelData(self, editor, model, index):
        model.setData(index, editor.currentText(), Qt.EditRole)


class Window(QMainWindow):
    #Инициализация основног окна
    def __init__(self):
        super(Window, self).__init__()
        self.setWindowTitle("Приложение") #Название окна
        self.setMinimumSize(900, 700) # Минимальный размер окна

        self.central_widjet = QWidget() #Создание центрального виджета
        self.setCentralWidget(self.central_widjet) #Назначаем наш виджет центральным

        self.mainLayout = QVBoxLayout() #Создаем вертикальный layout для окна
        self.buttonsLayout = QHBoxLayout() #Создаем горизонтальный layout для кнопок

        self.model = DataModel() #Создаем объект модели данных 
        # self.model.dataChanged.connect(self.updateGraph) #Вызываем слот обновления графика на сигнал изменения данных

        #Создание таблицы
        self.tableView = QTableView() #Создаем таблицу
        self.tableView.setModel(self.model) #Устанавливаем модель данных для таблицы
        self.tableView.setItemDelegateForColumn(0, ComboBoxDelegate()) #Устанавливаем делегат для первого столбца

        #Создание и настройка графика
        self.graph = pq.PlotWidget(self)
        self.graph.setBackground('black')
        self.pen = pq.mkPen(color = 'white', width = 3)
        self.graph.setLabel('left', 'Y') 
        self.graph.setLabel('bottom', 'X') 
        self.graph.showGrid(x = True, y = True)
        self.graph.getAxis('left').setPen(self.pen)
        self.graph.getAxis('bottom').setPen(self.pen)

        #Добавляем таблицы и графика в основной layout
        self.mainLayout.addWidget(self.tableView, stretch=1)
        self.mainLayout.addWidget(self.graph, stretch=1)

        #Создаем кнопки
        self.saveButton = QPushButton()
        self.saveButton.setText("Сохранить данные")
        
        self.loadButton = QPushButton()
        self.loadButton.setText("Загрузить данные")

        self.changeArrSizeButton = QPushButton()
        self.changeArrSizeButton.setText("Изменить размер массива")
        self.changeArrSizeButton.clicked.connect(self.changeArr)

        self.fillArrButton = QPushButton()
        self.fillArrButton.setText("Заполнить массив значениями")

        self.scipyButton = QPushButton()
        self.scipyButton.setText("Построить график cos(x)")

        self.createGraphButton = QPushButton();
        self.createGraphButton.setText("Построить график")
        self.createGraphButton.clicked.connect(self.chooseGraph)

        #Добавление кнопок в layout 
        self.buttonsLayout.addWidget(self.saveButton)
        self.buttonsLayout.addWidget(self.loadButton)
        self.buttonsLayout.addWidget(self.changeArrSizeButton)
        self.buttonsLayout.addWidget(self.fillArrButton)
        self.buttonsLayout.addWidget(self.scipyButton)
        
        self.mainLayout.addLayout(self.buttonsLayout) #Добавление buttonLayout и кнопки showGraph в основной layout
        self.mainLayout.addWidget(self.createGraphButton)
        self.central_widjet.setLayout(self.mainLayout) # Добавление основного layout в главный виджет

    def chooseGraph(self):
        col1, ok1 = QInputDialog().getInt(self, "Выбор осей графика", "Введите столбец, который будет осью X", 1, 1, self.model.columnCount())
        if ok1:
            col2, ok2 = QInputDialog().getInt(self, "Выбор осей графика", "Введите столбец, который будет осью Y", 1, 1, self.model.columnCount())

        if col1 == col2:
            QMessageBox.warning(self, "Предупреждение!", "Ведите разные столбцы")
        self.showGraph(col1-1, col2-1)

    def showGraph(self, col1, col2):
        data = self.model.getData()
        x = data[:, col1]
        y = data[:, col2]

        self.graph.clear()

        self.graph.plot(x, y, pen = 'b')

    def changeArr(self):
        rows, ok1 = QInputDialog().getInt(self, "Изменение размера массива", "Введите количеество строк(от 1 до 10)", self.model.rowCount(), 1, 10)
        if ok1:
            cols, ok2 = QInputDialog().getInt(self, "Изменение размера массива", "Введите количеество столбцов(от 3 до 10)", self.model.columnCount(), 3, 10)

        if (rows!= self.model.rowCount() and cols!= self.model.columnCount()):
            data = np.random.randint(1, 5, (rows, cols))
            self.model.changeData(data)
            self.graph.clear()

