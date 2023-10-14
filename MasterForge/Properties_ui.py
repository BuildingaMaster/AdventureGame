# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'Properties.ui'
##
## Created by: Qt User Interface Compiler version 6.4.2
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import (QCoreApplication, QDate, QDateTime, QLocale,
    QMetaObject, QObject, QPoint, QRect,
    QSize, QTime, QUrl, Qt)
from PySide6.QtGui import (QBrush, QColor, QConicalGradient, QCursor,
    QFont, QFontDatabase, QGradient, QIcon,
    QImage, QKeySequence, QLinearGradient, QPainter,
    QPalette, QPixmap, QRadialGradient, QTransform)
from PySide6.QtWidgets import (QAbstractButton, QApplication, QCheckBox, QComboBox,
    QDialog, QDialogButtonBox, QGridLayout, QGroupBox,
    QHBoxLayout, QLabel, QLineEdit, QSizePolicy,
    QTabWidget, QTextEdit, QVBoxLayout, QWidget)

class Ui_Dialog(object):
    def setupUi(self, Dialog):
        if not Dialog.objectName():
            Dialog.setObjectName(u"Dialog")
        Dialog.resize(641, 639)
        Dialog.setMinimumSize(QSize(431, 383))
        font = QFont()
        font.setFamilies([u".SF NS Text"])
        Dialog.setFont(font)
        Dialog.setModal(True)
        self.verticalLayout_7 = QVBoxLayout(Dialog)
        self.verticalLayout_7.setObjectName(u"verticalLayout_7")
        self.tabWidget = QTabWidget(Dialog)
        self.tabWidget.setObjectName(u"tabWidget")
        self.GeneralTab = QWidget()
        self.GeneralTab.setObjectName(u"GeneralTab")
        self.verticalLayout_6 = QVBoxLayout(self.GeneralTab)
        self.verticalLayout_6.setObjectName(u"verticalLayout_6")
        self.GenInfo = QGroupBox(self.GeneralTab)
        self.GenInfo.setObjectName(u"GenInfo")
        self.verticalLayout_3 = QVBoxLayout(self.GenInfo)
        self.verticalLayout_3.setObjectName(u"verticalLayout_3")
        self.RoomName_Layout = QHBoxLayout()
        self.RoomName_Layout.setObjectName(u"RoomName_Layout")
        self.RoomNameLabel = QLabel(self.GenInfo)
        self.RoomNameLabel.setObjectName(u"RoomNameLabel")

        self.RoomName_Layout.addWidget(self.RoomNameLabel)

        self.RoomNameEdit = QLineEdit(self.GenInfo)
        self.RoomNameEdit.setObjectName(u"RoomNameEdit")

        self.RoomName_Layout.addWidget(self.RoomNameEdit)


        self.verticalLayout_3.addLayout(self.RoomName_Layout)

        self.RoomDesc_Layout = QHBoxLayout()
        self.RoomDesc_Layout.setObjectName(u"RoomDesc_Layout")
        self.RoomDescLabel = QLabel(self.GenInfo)
        self.RoomDescLabel.setObjectName(u"RoomDescLabel")

        self.RoomDesc_Layout.addWidget(self.RoomDescLabel)

        self.RoomDescEdit = QTextEdit(self.GenInfo)
        self.RoomDescEdit.setObjectName(u"RoomDescEdit")

        self.RoomDesc_Layout.addWidget(self.RoomDescEdit)


        self.verticalLayout_3.addLayout(self.RoomDesc_Layout)


        self.verticalLayout_6.addWidget(self.GenInfo)

        self.tabWidget.addTab(self.GeneralTab, "")
        self.ConnectionsTab = QWidget()
        self.ConnectionsTab.setObjectName(u"ConnectionsTab")
        self.verticalLayout_2 = QVBoxLayout(self.ConnectionsTab)
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.Connections = QGroupBox(self.ConnectionsTab)
        self.Connections.setObjectName(u"Connections")
        self.verticalLayout_5 = QVBoxLayout(self.Connections)
        self.verticalLayout_5.setObjectName(u"verticalLayout_5")
        self.North_Layout = QHBoxLayout()
        self.North_Layout.setObjectName(u"North_Layout")
        self.NorthLabel = QLabel(self.Connections)
        self.NorthLabel.setObjectName(u"NorthLabel")

        self.North_Layout.addWidget(self.NorthLabel)

        self.NorthCombo = QComboBox(self.Connections)
        self.NorthCombo.setObjectName(u"NorthCombo")

        self.North_Layout.addWidget(self.NorthCombo)


        self.verticalLayout_5.addLayout(self.North_Layout)

        self.South_Layout = QHBoxLayout()
        self.South_Layout.setObjectName(u"South_Layout")
        self.SouthLabel = QLabel(self.Connections)
        self.SouthLabel.setObjectName(u"SouthLabel")

        self.South_Layout.addWidget(self.SouthLabel)

        self.SouthCombo = QComboBox(self.Connections)
        self.SouthCombo.setObjectName(u"SouthCombo")

        self.South_Layout.addWidget(self.SouthCombo)


        self.verticalLayout_5.addLayout(self.South_Layout)

        self.East_Layout = QHBoxLayout()
        self.East_Layout.setObjectName(u"East_Layout")
        self.EastLabel = QLabel(self.Connections)
        self.EastLabel.setObjectName(u"EastLabel")

        self.East_Layout.addWidget(self.EastLabel)

        self.EastCombo = QComboBox(self.Connections)
        self.EastCombo.setObjectName(u"EastCombo")

        self.East_Layout.addWidget(self.EastCombo)


        self.verticalLayout_5.addLayout(self.East_Layout)

        self.West_Layout = QHBoxLayout()
        self.West_Layout.setObjectName(u"West_Layout")
        self.WestLabel = QLabel(self.Connections)
        self.WestLabel.setObjectName(u"WestLabel")

        self.West_Layout.addWidget(self.WestLabel)

        self.WestCombo = QComboBox(self.Connections)
        self.WestCombo.setObjectName(u"WestCombo")

        self.West_Layout.addWidget(self.WestCombo)


        self.verticalLayout_5.addLayout(self.West_Layout)

        self.Above_Layout = QHBoxLayout()
        self.Above_Layout.setObjectName(u"Above_Layout")
        self.AboveLabel = QLabel(self.Connections)
        self.AboveLabel.setObjectName(u"AboveLabel")

        self.Above_Layout.addWidget(self.AboveLabel)

        self.AboveCombo = QComboBox(self.Connections)
        self.AboveCombo.setObjectName(u"AboveCombo")

        self.Above_Layout.addWidget(self.AboveCombo)


        self.verticalLayout_5.addLayout(self.Above_Layout)

        self.Below_Layout = QHBoxLayout()
        self.Below_Layout.setObjectName(u"Below_Layout")
        self.BelowLabel = QLabel(self.Connections)
        self.BelowLabel.setObjectName(u"BelowLabel")

        self.Below_Layout.addWidget(self.BelowLabel)

        self.BelowCombo = QComboBox(self.Connections)
        self.BelowCombo.setObjectName(u"BelowCombo")

        self.Below_Layout.addWidget(self.BelowCombo)


        self.verticalLayout_5.addLayout(self.Below_Layout)


        self.verticalLayout_2.addWidget(self.Connections)

        self.tabWidget.addTab(self.ConnectionsTab, "")
        self.Attributes = QWidget()
        self.Attributes.setObjectName(u"Attributes")
        self.verticalLayout_8 = QVBoxLayout(self.Attributes)
        self.verticalLayout_8.setObjectName(u"verticalLayout_8")
        self.label = QLabel(self.Attributes)
        self.label.setObjectName(u"label")
        sizePolicy = QSizePolicy(QSizePolicy.Minimum, QSizePolicy.Minimum)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.label.sizePolicy().hasHeightForWidth())
        self.label.setSizePolicy(sizePolicy)
        self.label.setMaximumSize(QSize(16777215, 16))
        self.label.setAlignment(Qt.AlignCenter)

        self.verticalLayout_8.addWidget(self.label)

        self.Common = QGroupBox(self.Attributes)
        self.Common.setObjectName(u"Common")
        self.gridLayout = QGridLayout(self.Common)
        self.gridLayout.setObjectName(u"gridLayout")
        self.Option8Check = QCheckBox(self.Common)
        self.Option8Check.setObjectName(u"Option8Check")

        self.gridLayout.addWidget(self.Option8Check, 4, 1, 1, 1)

        self.Option3Check = QCheckBox(self.Common)
        self.Option3Check.setObjectName(u"Option3Check")

        self.gridLayout.addWidget(self.Option3Check, 3, 0, 1, 1)

        self.Option2Check = QCheckBox(self.Common)
        self.Option2Check.setObjectName(u"Option2Check")

        self.gridLayout.addWidget(self.Option2Check, 2, 0, 1, 1)

        self.Option6Check = QCheckBox(self.Common)
        self.Option6Check.setObjectName(u"Option6Check")

        self.gridLayout.addWidget(self.Option6Check, 2, 1, 1, 1)

        self.Option5Check = QCheckBox(self.Common)
        self.Option5Check.setObjectName(u"Option5Check")

        self.gridLayout.addWidget(self.Option5Check, 1, 1, 1, 1)

        self.Option1Check = QCheckBox(self.Common)
        self.Option1Check.setObjectName(u"Option1Check")

        self.gridLayout.addWidget(self.Option1Check, 1, 0, 1, 1)

        self.Option4Check = QCheckBox(self.Common)
        self.Option4Check.setObjectName(u"Option4Check")

        self.gridLayout.addWidget(self.Option4Check, 4, 0, 1, 1)

        self.Option7Check = QCheckBox(self.Common)
        self.Option7Check.setObjectName(u"Option7Check")

        self.gridLayout.addWidget(self.Option7Check, 3, 1, 1, 1)


        self.verticalLayout_8.addWidget(self.Common)

        self.Extended = QGroupBox(self.Attributes)
        self.Extended.setObjectName(u"Extended")
        self.horizontalLayout = QHBoxLayout(self.Extended)
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.EnabledCombo = QComboBox(self.Extended)
        self.EnabledCombo.setObjectName(u"EnabledCombo")
        sizePolicy1 = QSizePolicy(QSizePolicy.Minimum, QSizePolicy.Fixed)
        sizePolicy1.setHorizontalStretch(0)
        sizePolicy1.setVerticalStretch(0)
        sizePolicy1.setHeightForWidth(self.EnabledCombo.sizePolicy().hasHeightForWidth())
        self.EnabledCombo.setSizePolicy(sizePolicy1)

        self.horizontalLayout.addWidget(self.EnabledCombo)

        self.EnabledCheck = QCheckBox(self.Extended)
        self.EnabledCheck.setObjectName(u"EnabledCheck")
        sizePolicy2 = QSizePolicy(QSizePolicy.Maximum, QSizePolicy.Fixed)
        sizePolicy2.setHorizontalStretch(0)
        sizePolicy2.setVerticalStretch(0)
        sizePolicy2.setHeightForWidth(self.EnabledCheck.sizePolicy().hasHeightForWidth())
        self.EnabledCheck.setSizePolicy(sizePolicy2)
        self.EnabledCheck.setFont(font)

        self.horizontalLayout.addWidget(self.EnabledCheck)


        self.verticalLayout_8.addWidget(self.Extended)

        self.tabWidget.addTab(self.Attributes, "")

        self.verticalLayout_7.addWidget(self.tabWidget)

        self.buttonBox = QDialogButtonBox(Dialog)
        self.buttonBox.setObjectName(u"buttonBox")
        self.buttonBox.setOrientation(Qt.Horizontal)
        self.buttonBox.setStandardButtons(QDialogButtonBox.Cancel|QDialogButtonBox.Ok)
        self.buttonBox.setCenterButtons(False)

        self.verticalLayout_7.addWidget(self.buttonBox)


        self.retranslateUi(Dialog)
        self.buttonBox.accepted.connect(Dialog.accept)
        self.buttonBox.rejected.connect(Dialog.reject)
        self.AboveCombo.currentIndexChanged.connect(self.AboveCombo.update)
        self.BelowCombo.currentIndexChanged.connect(self.BelowCombo.update)
        self.NorthCombo.currentIndexChanged.connect(self.NorthCombo.update)
        self.SouthCombo.currentIndexChanged.connect(self.SouthCombo.update)
        self.WestCombo.currentIndexChanged.connect(self.WestCombo.update)
        self.EastCombo.currentIndexChanged.connect(self.EastCombo.update)

        self.tabWidget.setCurrentIndex(0)


        QMetaObject.connectSlotsByName(Dialog)
    # setupUi

    def retranslateUi(self, Dialog):
        Dialog.setWindowTitle(QCoreApplication.translate("Dialog", u"Properties", None))
        self.GenInfo.setTitle(QCoreApplication.translate("Dialog", u"General Info", None))
        self.RoomNameLabel.setText(QCoreApplication.translate("Dialog", u"Room Name:", None))
        self.RoomDescLabel.setText(QCoreApplication.translate("Dialog", u"Story Description:", None))
        self.RoomDescEdit.setPlaceholderText(QCoreApplication.translate("Dialog", u"Supports basic HTML formatting", None))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.GeneralTab), QCoreApplication.translate("Dialog", u"General", None))
        self.Connections.setTitle(QCoreApplication.translate("Dialog", u"Connections", None))
        self.NorthLabel.setText(QCoreApplication.translate("Dialog", u"North Room:", None))
        self.NorthCombo.setPlaceholderText(QCoreApplication.translate("Dialog", u"None", None))
        self.SouthLabel.setText(QCoreApplication.translate("Dialog", u"South Room:", None))
        self.SouthCombo.setPlaceholderText(QCoreApplication.translate("Dialog", u"None", None))
        self.EastLabel.setText(QCoreApplication.translate("Dialog", u"East Room:", None))
        self.EastCombo.setPlaceholderText(QCoreApplication.translate("Dialog", u"None", None))
        self.WestLabel.setText(QCoreApplication.translate("Dialog", u"West Room:", None))
        self.WestCombo.setPlaceholderText(QCoreApplication.translate("Dialog", u"None", None))
        self.AboveLabel.setText(QCoreApplication.translate("Dialog", u"Above Room:", None))
        self.AboveCombo.setPlaceholderText(QCoreApplication.translate("Dialog", u"None", None))
        self.BelowLabel.setText(QCoreApplication.translate("Dialog", u"Below Room:", None))
        self.BelowCombo.setPlaceholderText(QCoreApplication.translate("Dialog", u"None", None))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.ConnectionsTab), QCoreApplication.translate("Dialog", u"Connections", None))
        self.label.setText(QCoreApplication.translate("Dialog", u"NOTE: Not really implemented", None))
        self.Common.setTitle(QCoreApplication.translate("Dialog", u"Common", None))
        self.Option8Check.setText(QCoreApplication.translate("Dialog", u"Option 8", None))
        self.Option3Check.setText(QCoreApplication.translate("Dialog", u"Option 3", None))
        self.Option2Check.setText(QCoreApplication.translate("Dialog", u"Option 2", None))
        self.Option6Check.setText(QCoreApplication.translate("Dialog", u"Option 6", None))
        self.Option5Check.setText(QCoreApplication.translate("Dialog", u"Option 5", None))
        self.Option1Check.setText(QCoreApplication.translate("Dialog", u"Option 1", None))
        self.Option4Check.setText(QCoreApplication.translate("Dialog", u"Option 4", None))
        self.Option7Check.setText(QCoreApplication.translate("Dialog", u"Option 7", None))
        self.Extended.setTitle(QCoreApplication.translate("Dialog", u"Extended", None))
        self.EnabledCheck.setText(QCoreApplication.translate("Dialog", u"Enabled", None))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.Attributes), QCoreApplication.translate("Dialog", u"Attributes", None))
    # retranslateUi

