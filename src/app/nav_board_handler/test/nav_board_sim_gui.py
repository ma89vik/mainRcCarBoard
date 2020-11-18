from PyQt5.QtCore import QDateTime, Qt, QTimer
from PyQt5.QtGui import QIntValidator
from PyQt5.QtWidgets import (QApplication, QCheckBox, QComboBox, QDateTimeEdit,
        QDial, QDialog, QGridLayout, QGroupBox, QHBoxLayout, QLabel, QLineEdit,
        QProgressBar, QPushButton, QRadioButton, QScrollBar, QSizePolicy,
        QSlider, QSpinBox, QStyleFactory, QTableWidget, QTabWidget, QTextEdit,
        QVBoxLayout, QWidget)


import nav_board_sim_cmds


class ControlWidget(QDialog):
    def __init__(self, control_board, parent=None):
        super(ControlWidget, self).__init__(parent)
        self.control_board = control_board
        self.originalPalette = QApplication.palette()

        styleComboBox = QComboBox()
        styleComboBox.addItems(QStyleFactory.keys())

        styleLabel = QLabel("&Style:")
        styleLabel.setBuddy(styleComboBox)

        self.useStylePaletteCheckBox = QCheckBox("&Use style's standard palette")
        self.useStylePaletteCheckBox.setChecked(True)

        self.createCarCmdWidget()

        mainLayout = QGridLayout()
        mainLayout.addWidget(self.cmdGroupBox, 0, 0)
        self.setLayout(mainLayout)

        self.setWindowTitle("Styles")
        self.changeStyle('Windows')

    def changeStyle(self, styleName):
        QApplication.setStyle(QStyleFactory.create(styleName))
        self.changePalette()

    def changePalette(self):
        if (self.useStylePaletteCheckBox.isChecked()):
            QApplication.setPalette(QApplication.style().standardPalette())
        else:
            QApplication.setPalette(self.originalPalette)


    def createControlWidget(self):
        control_group_box = QGroupBox("Speed")

        self.speed_dial = QDial(self.cmdGroupBox)
        self.speed_dial.setRange(-100, 100)
        self.speed_dial.setValue(0)
        self.speed_dial.setNotchesVisible(True)
        self.speed_dial.setTracking(False)
        self.speed_dial.valueChanged.connect(self.speed_changed)

        self.speed_stop_button = QPushButton("Stop")
        self.speed_stop_button.released.connect(self.speed_stop)

        layout = QGridLayout()
        layout.addWidget(self.speed_dial, 1, 1,)
        layout.addWidget(self.speed_stop_button, 3, 1,)

        control_group_box.setLayout(layout)

        self.cmd_layout.addWidget(control_group_box, 1, 1)

        control_group_box = QGroupBox("Steering")

        self.steering_dial = QDial(self.cmdGroupBox)
        self.steering_dial.setRange(-100, 100)
        self.steering_dial.setValue(0)
        self.steering_dial.setNotchesVisible(True)
        self.steering_dial.setTracking(False)
        self.steering_dial.valueChanged.connect(self.steering_changed)

        self.steering_stop_button = QPushButton("Stop")
        self.steering_stop_button.released.connect(self.steering_stop)

        layout = QGridLayout()
        layout.addWidget(self.steering_dial, 1, 1,)
        layout.addWidget(self.steering_stop_button, 3, 1,)

        control_group_box.setLayout(layout)

        self.cmd_layout.addWidget(control_group_box, 1, 2)


    def steering_changed(self):
        control_board.set_steering(self.steering_dial.value())

    def steering_stop(self):
        control_board.set_steering(0)

    def speed_changed(self):
        control_board.set_speed(self.speed_dial.value())

    def speed_stop(self):
        control_board.set_speed(0)


    def createCarCmdWidget(self):
        self.cmdGroupBox = QGroupBox("Cmd group")
        self.cmd_layout = QGridLayout()

        self.createControlWidget()

        self.cmdGroupBox.setLayout(self.cmd_layout)



if __name__ == '__main__':

    import sys

    control_board = nav_board_sim_cmds.ControlBoard()
    control_board.connect("/dev/ttyUSB3")

    app = QApplication(sys.argv)
    gallery = ControlWidget(control_board)
    gallery.show()
    sys.exit(app.exec_())