import sys 
from PyQt5.QtWidgets import QApplication,QWidget,QPushButton,QToolTip,QMainWindow
from PyQt5.QtCore import QCoreApplication
from PyQt5.QtGui import QFont

class MyApp(QMainWindow):
	def __init__(self):
		super().__init__()
		self.initUI()

	def initUI(self):
#상태바 만들기
		self.statusBar().showMessage('Ready')
#툴팁 표시
		QToolTip.setFont(QFont('SansSerif',10))
		self.setToolTip('This is a <b>QWidget</b> widget')
#'Quit' 아이콘 넣기
		btn = QPushButton('Quit',self)
		btn.move(50,50)
		btn.resize(btn.sizeHint())
		btn.clicked.connect(QCoreApplication.instance().quit)
#window 띄우기		
		self.setWindowTitle('Quit Button')
		self.setGeometry(300,300,300,200)
		self.show()

if __name__=='__main__':
    app=QApplication(sys.argv)
    ex=MyApp()
    sys.exit(app.exec_())
            
