import sys
from PyQt5.QtWidgets import *
import time
from threading import Timer
class MyApp(QWidget):

    def __init__(self):
        super().__init__()
   
        self.hour = QLCDNumber(self)
        self.min = QLCDNumber(self)
        self.sec = QLCDNumber(self)
        self.initUI()

    def initUI(self):

        vbox = QGridLayout()
        vbox.addWidget(self.hour,0,0)
        vbox.addWidget(self.min,0,1)
        vbox.addWidget(self.sec,0,2)
        self.setLayout(vbox)

        #while True:
        self.setWindowTitle('Signal and Slot')
        self.setGeometry(300, 300, 200, 100)
        self.showTime()
        self.show()

    def showTime(self):
        t=time.time()
        kor=time.localtime(t)
        self.hour.display(kor.tm_hour)
        self.min.display(kor.tm_min)
        self.sec.display(kor.tm_sec)

        timer = Timer(1, self.showTime)
        timer.start()

if __name__ == '__main__':

    app = QApplication(sys.argv)
    w = MyApp()
    sys.exit(app.exec_())
