
from PyQt5.QtCore import Qt
from PyQt5 import QtWidgets, QtGui
from PyQt5.QtWidgets import (QMainWindow, QVBoxLayout, QHBoxLayout, 
                            QPushButton, QTableView, QWidget, 
                            QInputDialog, QMessageBox, QFileDialog)
import pyqtgraph as pq
import numpy as np
import h5py

# Импорт пользовательской модели данных
from model import DataModel

"""
Класс ComboBoxDelegate - делегат для отображения комбобокса в ячейке таблицы.
"""
class ComboBoxDelegate(QtWidgets.QStyledItemDelegate):
    
    # Создает редактор (комбобокс) для ячейки таблицы
    def createEditor(self, parent, option, index):
        # Создаем комбобокс с указанным родителем
        editor = QtWidgets.QComboBox(parent)
        # Заполняем значениями от 1 до 5
        editor.addItems([str(i) for i in range(1,6)])
        return editor
    
    # Устанавливает текущее значение из модели в редактор
    def setEditorData(self, editor, index):
        # Получаем значение из модели и преобразуем в int
        value = int(index.model().data(index, Qt.EditRole))
        # Устанавливаем текущий текст в комбобоксе
        editor.setCurrentText(str(value))

    # Сохраняет значение из редактора в модель
    def setModelData(self, editor, model, index):
        # Устанавливаем данные в модель из текущего текста комбобокса
        model.setData(index, editor.currentText(), Qt.EditRole)


"""
Класс главного окна приложения.
"""
class Window(QMainWindow):
    
    # Конструктор класса
    def __init__(self):
        # Вызов конструктора родительского класса
        super(Window, self).__init__()
        
        # Настройка основных параметров окна
        self.setWindowTitle("Приложение")  # Заголовок окна
        self.setMinimumSize(900, 700)  # Минимальные размеры окна (ширина, высота)

        # Создание центрального виджета и layout'ов
        self.central_widjet = QWidget()  # Центральный виджет-контейнер
        self.setCentralWidget(self.central_widjet)  # Установка центрального виджета
        
        # Основные layout'ы:
        self.mainLayout = QVBoxLayout()  # Вертикальный layout для всего содержимого
        self.buttonsLayout = QHBoxLayout()  # Горизонтальный layout для кнопок

        # Создание модели данных
        self.model = DataModel()  # Экземпляр пользовательской модели данных
        
        # Подключение сигнала изменения данных к слоту обновления графика
        self.model.dataChanged.connect(self.updateGraph)

        # Настройка таблицы для отображения данных
        self.tableView = QTableView()  # Создание виджета таблицы
        self.tableView.setModel(self.model)  # Установка модели данных
        
        # Настройка размеров столбцов:
        self.tableView.horizontalHeader().setDefaultSectionSize(100)  # Ширина по умолчанию
        # Ширина последних двух столбцов (180 пикселей)
        self.tableView.setColumnWidth(self.model.columnCount() - 1, 180)
        self.tableView.setColumnWidth(self.model.columnCount() - 2, 180)
        
        # Настройка шрифта для таблицы
        font = QtGui.QFont("Times New Roman", 12)  # Шрифт Times New Roman, размер 12
        font.setBold(True)  # Жирное начертание
        self.tableView.setFont(font)  # Применение шрифта
        
        # Установка делегата комбобокса для первого столбца
        self.tableView.setItemDelegateForColumn(0, ComboBoxDelegate())
        
        # Настройка графика (используется pyqtgraph)
        self.graph = pq.PlotWidget(self)  # Создание виджета графика
        self.graph.setBackground('black')  # Черный фон графика
        
        # Настройка пера (стиля линий) для осей
        self.pen = pq.mkPen(color='white', width=3)  # Белая линия толщиной 3px
        
        # Подписи осей:
        self.graph.setLabel('left', 'Y')  # Левая ось (Y)
        self.graph.setLabel('bottom', 'X')  # Нижняя ось (X)
        
        # Включение сетки:
        self.graph.showGrid(x=True, y=True)  # Сетка по обеим осям
        
        # Применение стиля к осям:
        self.graph.getAxis('left').setPen(self.pen)  # Левая ось
        self.graph.getAxis('bottom').setPen(self.pen)  # Нижняя ось

        # Флаг, указывающий, отображается ли график в данный момент
        self.showGraphFlag = False

        # Добавление виджетов в основной layout
        self.mainLayout.addWidget(self.tableView, stretch=1)  # Таблица с коэффициентом растяжения 1
        self.mainLayout.addWidget(self.graph, stretch=1)  # График с таким же коэффициентом

        # Создание кнопок управления:
        
        # Кнопка сохранения данных
        self.saveButton = QPushButton("Сохранить данные")
        self.saveButton.clicked.connect(self.saveData)  # Подключение обработчика
        
        # Кнопка загрузки данных
        self.loadButton = QPushButton("Загрузить данные")
        self.loadButton.clicked.connect(self.loadData)
        
        # Кнопка изменения размера массива
        self.changeArrSizeButton = QPushButton("Изменить размер массива")
        self.changeArrSizeButton.clicked.connect(self.changeArr)
        
        # Кнопка заполнения массива значениями
        self.fillArrButton = QPushButton("Заполнить массив значениями")
        self.fillArrButton.clicked.connect(self.changeArrData)
        
        # Кнопка построения графика
        self.createGraphButton = QPushButton("Построить график")
        self.createGraphButton.clicked.connect(self.chooseGraph)

        # Добавление кнопок в горизонтальный layout
        self.buttonsLayout.addWidget(self.saveButton)
        self.buttonsLayout.addWidget(self.loadButton)
        self.buttonsLayout.addWidget(self.changeArrSizeButton)
        self.buttonsLayout.addWidget(self.fillArrButton)
        self.buttonsLayout.addWidget(self.createGraphButton)
        
        # Добавление layout с кнопками в основной layout
        self.mainLayout.addLayout(self.buttonsLayout)
        
        # Установка основного layout для центрального виджета
        self.central_widjet.setLayout(self.mainLayout)

    """
    Метод для сохранения данных в файл формата HDF5
    """
    def saveData(self):
        # Открытие диалогового окна для выбора места сохранения
        file_path, _ = QFileDialog.getSaveFileName(
            self,                  # Родительское окно
            "Сохранить данные",    # Заголовок окна
            "",                    # Начальная директория (пустая = текущая)
            "HDF5 Files (*.h5)"    # Фильтр файлов (только .h5)
        )

        # Если пользователь отменил диалог (не выбрал файл)
        if not file_path:
            return  # Выход из метода
        
        try:
            # Открытие файла для записи ('w' - write mode)
            with h5py.File(file_path, 'w') as f:
                # Получение данных из модели (numpy массив)
                data = self.model.getData()
                # Создание набора данных в HDF5 файле
                f.create_dataset('dataset_name', data=data)
            # Показ сообщения об успешном сохранении
            QMessageBox.information(self, "Успешно!", "Данные сохранены!")
        except Exception as e:  # Обработка возможных ошибок
            # Показ сообщения об ошибке с деталями
            QMessageBox.critical(self, "Ошибка", 
                               f"Не удалось сохранить файл:\n{str(e)}")

    """
    Метод для загрузки данных из HDF5 файла
    """
    def loadData(self):
        # Открытие диалогового окна для выбора файла
        file_path, _ = QFileDialog.getOpenFileName(
            self,                # Родительское окно
            "Загрузить данные",  # Заголовок окна
            "",                  # Начальная директория
            "HDF5 Files (*.h5)"  # Фильтр файлов
        )

        # Если файл не выбран
        if not file_path:
            return  # Выход из метода

        try:
            # Открытие файла для чтения ('r' - read mode)
            with h5py.File(file_path, "r") as f:
                # Получение набора данных по имени
                dataset = f["dataset_name"]
                # Обновление модели новыми данными
                self.model.changeData(dataset[:])
            # Сообщение об успешной загрузке
            self.showGraphFlag = False
            self.graph.clear()
            QMessageBox.information(self, "Успешно!", "Данные загружены!")
        except Exception as e:  # Обработка ошибок
            # Сообщение об ошибке с деталями
            QMessageBox.critical(self, "Ошибка", 
                               f"Не удалось открыть файл:\n{str(e)}")

    """
    Метод для изменения размера массива данных
    """
    def changeArr(self):
        # Запрос количества строк через диалоговое окно
        rows, ok1 = QInputDialog().getInt(
            self,  # Родительское окно
            "Изменение размера массива",  # Заголовок
            "Введите количество строк(от 1 до 10)",  # Текст подсказки
            self.model.rowCount(),  # Текущее значение
            1, 10  # Минимальное и максимальное значение
        )
        
        # Если пользователь не отменил ввод строк
        if ok1:
            # Аналогичный запрос для столбцов
            cols, ok2 = QInputDialog().getInt(
                self,
                "Изменение размера массива",
                "Введите количество столбцов(от 3 до 10)",
                self.model.columnCount(),
                3, 10
            )

        # Если размеры изменились
        if (rows != self.model.rowCount() or cols != self.model.columnCount()):
            # Генерация случайных данных (числа от 1 до 4)
            data = np.random.randint(1, 5, (rows, cols))
            # Обновление модели новыми данными
            self.model.changeData(data)
            # Очистка графика
            self.graph.clear()
        
        # Обновление размеров столбцов таблицы
        self.tableView.horizontalHeader().setDefaultSectionSize(100)
        self.tableView.setColumnWidth(self.model.columnCount() - 1, 180)
        self.tableView.setColumnWidth(self.model.columnCount() - 2, 180)

    """
    Метод для заполнения выбранного столбца случайными значениями
    """
    def changeArrData(self):
        # Запрос номера столбца для заполнения
        generateCol, ok = QInputDialog.getInt(
            self,
            "Заполнение случайными величинами",
            "Выберите столбец для заполнения случайными величинами:",
            1,  # Текущее значение
            1,  # Минимальное значение
            self.model.columnCount() - 2  # Максимальное значение
        )
        
        # Если пользователь подтвердил выбор
        if ok:
            # Вызов метода модели для заполнения столбца
            # (передаем индекс столбца, уменьшенный на 1)
            self.model.fillArr(generateCol - 1)

    """
    Метод для выбора столбцов, которые будут отображаться на графике
    """
    def chooseGraph(self):
        # Бесконечный цикл для повторного запроса при ошибках
        while True:
            # Запрос столбца для оси X
            col1, ok1 = QInputDialog().getInt(
                self,
                "Выбор осей графика",
                "Введите столбец, который будет осью X",
                1,  # Текущее значение
                1,  # Минимальное значение
                self.model.columnCount()  # Максимальное значение
            )
            
            # Если пользователь отменил ввод
            if not ok1:
                return  # Выход из метода

            # Аналогичный запрос для оси Y
            col2, ok2 = QInputDialog().getInt(
                self,
                "Выбор осей графика",
                "Введите столбец, который будет осью Y",
                1,
                1,
                self.model.columnCount()
            )
            
            # Если пользователь отменил ввод
            if not ok2:
                return

            # Проверка, что выбраны разные столбцы
            if col1 == col2:
                # Показать предупреждение
                QMessageBox.warning(self, "Предупреждение!", 
                                  "Выберите разные столбцы")
            else:
                # Отображение графика (индексы уменьшаем на 1)
                self.showGraph(col1-1, col2-1)
                break  # Выход из цикла

    """
    Метод для отображения графика по выбранным столбцам
    """
    def showGraph(self, col1, col2):
        # Получение данных из модели
        data = self.model.getData()
        # Данные для оси X (все строки, столбец col1)
        x = data[:, col1]
        # Сохранение индекса столбца X для обновлений
        self.col1 = col1
        # Данные для оси Y (все строки, столбец col2)
        y = data[:, col2]
        # Сохранение индекса столбца Y
        self.col2 = col2

        # Очистка предыдущего графика
        self.graph.clear()
        # Построение нового графика (синяя линия)
        self.graph.plot(x, y, pen='b')
        # Установка флага, что график отображается
        self.showGraphFlag = True

    """
    Метод для обновления графика при изменении данных в модели
    """
    def updateGraph(self, topLeft, bottomRight):
        # Если график в данный момент отображается
        if self.showGraphFlag:
            # Получение текущих данных
            data = self.model.getData()
            # Данные для оси X
            x = data[:, self.col1]
            # Данные для оси Y
            y = data[:, self.col2]
            # Очистка графика
            self.graph.clear()
            # Построение обновленного графика
            self.graph.plot(x, y, pen="b")