from PyQt5.QtWidgets import QApplication

from view import Window
import sys

    
def application():
    app = QApplication(sys.argv)
    window = Window()
    window.show()
    sys.exit(app.exec_())

if __name__ == "__main__":
    application()