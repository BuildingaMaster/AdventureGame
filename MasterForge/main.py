import json
import re
import struct
import mainwindow_ui
import Properties_ui
import sys
from PySide6.QtCore import Qt, QPoint, QFileInfo
from PySide6.QtGui import QAction
from PySide6.QtWidgets import (QGraphicsSceneMouseEvent,QFileDialog, QDialog, QMenu, QApplication, QMainWindow,
    QMessageBox, QGraphicsScene,QGraphicsRectItem,QGraphicsItem,QGraphicsView, QGraphicsTextItem, QInputDialog)

VERSION = 1.0

class recProperties(Properties_ui.Ui_Dialog,QDialog):
    def __init__(self, *args, **kwargs):
        # INIT
        # Get the custom arguments, then delete.
        # Qt does not like any additional arguments.

        self.mainRec = kwargs["rect"]
        kwargs.pop("rect")

        super(recProperties, self).__init__(*args, **kwargs)
        # Setup interface
        self.setupUi(self)
        self.GUIWin = args[0]
        self.inUpdate = False
        self.ID = self.GUIWin.box_check[-1]["RoomID"]
        self.RoomNameEdit.setText(self.GUIWin.box_check[-1]["RoomName"])
        self.setWindowTitle(f"Properties  - {self.RoomNameEdit.text()}")
        self.RoomDescEdit.setText(self.GUIWin.box_check[-1]["RoomDesc"]) 
        self.comboAlloc = [self.AboveCombo, self.BelowCombo, self.NorthCombo, self.SouthCombo, self.EastCombo, self.WestCombo]
        self.intToNav = ["A","B","N","S","E","W"]

        # Initalize item data
        self.AboveCombo.setItemData(0,0)
        self.AboveCombo.mapDirection = 0
        self.aIndexChange = lambda data: self.indexChange(self.AboveCombo, data)

        self.BelowCombo.setItemData(0,0)
        self.BelowCombo.mapDirection = 1
        self.bIndexChange = lambda data: self.indexChange(self.BelowCombo, data)

        self.NorthCombo.setItemData(0,0)
        self.NorthCombo.mapDirection = 2
        self.nIndexChange = lambda data: self.indexChange(self.NorthCombo, data)

        self.SouthCombo.setItemData(0,0)
        self.SouthCombo.mapDirection = 3
        self.sIndexChange = lambda data: self.indexChange(self.SouthCombo, data)

        self.EastCombo.setItemData(0,0)
        self.EastCombo.mapDirection = 4
        self.eIndexChange = lambda data: self.indexChange(self.EastCombo, data)

        self.WestCombo.setItemData(0,0)
        self.WestCombo.mapDirection = 5
        self.wIndexChange = lambda data: self.indexChange(self.WestCombo, data)

        self.connectComboBoxes()
        #self.disconnectComboBoxes()
        
        # Perform update on create
        self.update()

    def setComboBoxID(self,comboType,ID):
        combo = self.comboAlloc[self.intToNav.index(comboType)]
        comboIndex = next(i for i in range(combo.count()) if combo.itemData(i) == ID)
        self.disconnectComboBoxes()
        combo.setCurrentIndex(comboIndex)
        self.connectComboBoxes()
        self.setDirectionString()
        
    def connectComboBoxes(self):
        self.AboveCombo.currentIndexChanged.connect(self.aIndexChange)
        self.BelowCombo.currentIndexChanged.connect(self.bIndexChange)
        self.NorthCombo.currentIndexChanged.connect(self.nIndexChange)
        self.SouthCombo.currentIndexChanged.connect(self.sIndexChange)
        self.EastCombo.currentIndexChanged.connect(self.eIndexChange)
        self.WestCombo.currentIndexChanged.connect(self.wIndexChange)
    
    def disconnectComboBoxes(self):
        self.AboveCombo.currentIndexChanged.disconnect(self.aIndexChange)
        self.BelowCombo.currentIndexChanged.disconnect(self.bIndexChange)
        self.NorthCombo.currentIndexChanged.disconnect(self.nIndexChange)
        self.SouthCombo.currentIndexChanged.disconnect(self.sIndexChange)
        self.EastCombo.currentIndexChanged.disconnect(self.eIndexChange)
        self.WestCombo.currentIndexChanged.disconnect(self.wIndexChange)

    # STUB
    #TODO: Backwards connectivity
    def indexChange(self,obj,index):
        if index == 0:
            return
        confirm = QMessageBox.question(self, 'Connection',
                                'Connect room as two-way?',QMessageBox.Yes,QMessageBox.No)
        if confirm == QMessageBox.No:
            return
        selectID = obj.currentData()
        oppBoxListing = next(self.GUIWin.box_check[i] for i, item in enumerate(self.GUIWin.box_check) if item['RoomID'] == selectID)
        oppElement = oppBoxListing["roomDef"]
        if (obj.mapDirection+1)%2:
            oppMapDir = obj.mapDirection+1
        else:
            oppMapDir = obj.mapDirection-1

        oppElement.properties.disconnectComboBoxes()
        oppElement.properties.comboAlloc[oppMapDir].setCurrentIndex(obj.currentIndex())
        oppBoxListing[self.intToNav[oppMapDir]] = self.ID
        oppElement.properties.connectComboBoxes()
        oppElement.properties.setDirectionString()
        #oppElement.properties

    
    # When the properies box needs to appear, change the window name and update.
    def showEvent(self,event):
        self.tabWidget.setCurrentIndex(0)
        self.setWindowTitle(f"Properties  - {self.RoomNameEdit.text()}")
        self.update()

    # Shows that a room is disconnected.
    def disconnectWarning(self):
        QMessageBox.warning(self, 'Disconnected Links',
            'One or rooms were deleted, and the connection is lost.')
        self.GUIWin.markAsUnsaved()
        self.tabWidget.setCurrentIndex(1)

    # Ensure info is up to date.
    def update(self):
        self.disconnectComboBoxes()
        
        ### Ensure that the connected room was not deleted.

        # From the properties box
        tempList = list(self.AboveCombo.itemText(i) for i in range(self.AboveCombo.count()))
    
        # From the main array
        created = ["None"] + list(i["RoomName"] for i in self.GUIWin.box_check)
        
        possible = list(created)
        possible.extend(x for x in created if x not in possible and x not in tempList)

        # Checking if the list is the same.
        if len(possible) == len(tempList):
            notSafe=False
            for i in range(len(possible)):
                if possible[i] != tempList[i]:
                    notSafe = True 
                    break
            # Its the same list, we are OK.
            if notSafe is False:
                self.connectComboBoxes()
                return

        # Save a copy of the previous data.
        AboveComboPrevID = self.AboveCombo.currentData()
        BelowComboPrevID = self.BelowCombo.currentData()
        NorthComboPrevID = self.NorthCombo.currentData()
        SouthComboPrevID = self.SouthCombo.currentData()
        EastComboPrevID = self.EastCombo.currentData()
        WestComboPrevID = self.WestCombo.currentData()

        if AboveComboPrevID == None:
            AboveComboPrevID = 0
            BelowComboPrevID = 0
            NorthComboPrevID = 0
            SouthComboPrevID = 0
            EastComboPrevID = 0
            WestComboPrevID = 0


        AboveComboArc = []
        BelowComboArc = []
        NorthComboArc = []
        SouthComboArc = []
        EastComboArc = []
        WestComboArc = []
        for i in range(self.AboveCombo.count()):
            AboveComboArc.append(self.AboveCombo.itemData(i))
            self.AboveCombo.setItemData(i,None)
            BelowComboArc.append(self.BelowCombo.itemData(i))
            self.BelowCombo.setItemData(i,None)
            NorthComboArc.append(self.NorthCombo.itemData(i))
            self.NorthCombo.setItemData(i,None)
            SouthComboArc.append(self.SouthCombo.itemData(i))
            self.SouthCombo.setItemData(i,None)
            EastComboArc.append(self.EastCombo.itemData(i))
            self.EastCombo.setItemData(i,None)
            WestComboArc.append(self.WestCombo.itemData(i))
            self.WestCombo.setItemData(i,None)
        
        # Delete combo list
        for i in range(self.AboveCombo.count()):
            self.AboveCombo.removeItem(0)
            self.BelowCombo.removeItem(0)
            self.NorthCombo.removeItem(0)
            self.SouthCombo.removeItem(0)
            self.EastCombo.removeItem(0)
            self.WestCombo.removeItem(0)

        # Add the new list
        self.AboveCombo.addItems(possible)
        self.BelowCombo.addItems(possible)
        self.NorthCombo.addItems(possible)
        self.SouthCombo.addItems(possible)
        self.EastCombo.addItems(possible)
        self.WestCombo.addItems(possible)

        # Set the new item data, if it doesn't exist, mark it as 0.
        IDCheck = [0]
        self.AboveCombo.setItemData(0,0)
        self.BelowCombo.setItemData(0,0)
        self.NorthCombo.setItemData(0,0)
        self.SouthCombo.setItemData(0,0)
        self.EastCombo.setItemData(0,0)
        self.WestCombo.setItemData(0,0)

        #for count, item in self.GUIWin.box_check:
        for count in range(len(self.GUIWin.box_check)):
            self.AboveCombo.setItemData(count+1,self.GUIWin.box_check[count]["RoomID"])
            self.BelowCombo.setItemData(count+1,self.GUIWin.box_check[count]["RoomID"])
            self.NorthCombo.setItemData(count+1,self.GUIWin.box_check[count]["RoomID"])
            self.SouthCombo.setItemData(count+1,self.GUIWin.box_check[count]["RoomID"])
            self.EastCombo.setItemData(count+1,self.GUIWin.box_check[count]["RoomID"])
            self.WestCombo.setItemData(count+1,self.GUIWin.box_check[count]["RoomID"])
            IDCheck.append(self.GUIWin.box_check[count]["RoomID"])

        self.AboveCombo.setCurrentIndex(next((i for i, x in enumerate(IDCheck) if x == AboveComboPrevID),0))
        self.BelowCombo.setCurrentIndex(next((i for i, x in enumerate(IDCheck) if x == BelowComboPrevID),0))
        self.NorthCombo.setCurrentIndex(next((i for i, x in enumerate(IDCheck) if x == NorthComboPrevID),0))
        self.SouthCombo.setCurrentIndex(next((i for i, x in enumerate(IDCheck) if x == SouthComboPrevID),0))
        self.EastCombo.setCurrentIndex(next((i for i, x in enumerate(IDCheck) if x == EastComboPrevID),0))
        self.WestCombo.setCurrentIndex(next((i for i, x in enumerate(IDCheck) if x == WestComboPrevID),0))

        # This checks if a room was deleted.

        displayedWarning = False

        if self.AboveCombo.itemData(self.AboveCombo.currentIndex()) != AboveComboPrevID and self.AboveCombo.itemData(self.AboveCombo.currentIndex()) == 0 and AboveComboPrevID != 0:
            if not displayedWarning:
                self.disconnectWarning()
                displayedWarning = True
            self.AboveLabel.setText("<strong>Above Room: [PREVIOUSLY DELETED]</strong>")

        if self.BelowCombo.itemData(self.BelowCombo.currentIndex()) != BelowComboPrevID and self.BelowCombo.itemData(self.BelowCombo.currentIndex()) == 0 and BelowComboPrevID != 0:
            if not displayedWarning:
                self.disconnectWarning()
                displayedWarning = True
            self.BelowLabel.setText("<strong>Below Room: [PREVIOUSLY DELETED]</strong>")

        if self.NorthCombo.itemData(self.NorthCombo.currentIndex()) != NorthComboPrevID and self.NorthCombo.itemData(self.NorthCombo.currentIndex()) == 0 and NorthComboPrevID != 0:
            if not displayedWarning:
                self.disconnectWarning()
                displayedWarning = True
            self.NorthLabel.setText("<strong>North Room: [PREVIOUSLY DELETED]</strong>")

        if self.SouthCombo.itemData(self.SouthCombo.currentIndex()) != SouthComboPrevID and self.SouthCombo.itemData(self.SouthCombo.currentIndex()) == 0 and SouthComboPrevID != 0:
            if not displayedWarning:
                self.disconnectWarning()
                displayedWarning = True
            self.SouthLabel.setText("<strong>South Room: [PREVIOUSLY DELETED]</strong>")

        if self.EastCombo.itemData(self.EastCombo.currentIndex()) != EastComboPrevID and self.EastCombo.itemData(self.EastCombo.currentIndex()) == 0 and EastComboPrevID != 0:
            if not displayedWarning:
                self.disconnectWarning()
                displayedWarning = True
            self.EastLabel.setText("<strong>East Room: [PREVIOUSLY DELETED]</strong>")

        if self.WestCombo.itemData(self.WestCombo.currentIndex()) != WestComboPrevID and self.WestCombo.itemData(self.WestCombo.currentIndex()) == 0 and WestComboPrevID != 0:
            if not displayedWarning:
                self.disconnectWarning()
                displayedWarning = True
            self.WestLabel.setText("<strong>West Room: [PREVIOUSLY DELETED]</strong>")



        # Set the index to the currently connected room.
        self.AboveCombo.setCurrentIndex(next((possible.index(i["RoomName"]) for i in self.GUIWin.box_check if i["RoomID"] == AboveComboArc),possible.index("None")))
        self.BelowCombo.setCurrentIndex(next((possible.index(i["RoomName"]) for i in self.GUIWin.box_check if i["RoomID"] == BelowComboArc),possible.index("None")))
        self.NorthCombo.setCurrentIndex(next((possible.index(i["RoomName"]) for i in self.GUIWin.box_check if i["RoomID"] == NorthComboArc),possible.index("None")))
        self.SouthCombo.setCurrentIndex(next((possible.index(i["RoomName"]) for i in self.GUIWin.box_check if i["RoomID"] == SouthComboArc),possible.index("None")))
        self.EastCombo.setCurrentIndex(next((possible.index(i["RoomName"]) for i in self.GUIWin.box_check if i["RoomID"] == EastComboArc),possible.index("None")))
        self.WestCombo.setCurrentIndex(next((possible.index(i["RoomName"]) for i in self.GUIWin.box_check if i["RoomID"] == WestComboArc),possible.index("None")))

        self.connectComboBoxes()

    # Save the the main array
    def accept(self):
        index = next((self.GUIWin.box_check.index(i) for i in self.GUIWin.box_check if i["RoomID"] == self.ID))
        self.GUIWin.box_check[index]["RoomName"] = self.RoomNameEdit.text()
        self.GUIWin.box_check[index]["RoomDesc"] = self.RoomDescEdit.toPlainText()
        self.mainRec.nameTextItem.setPlainText(self.RoomNameEdit.text()) 
        self.GUIWin.box_check[index]["N"] = self.NorthCombo.itemData(self.NorthCombo.currentIndex())
        self.GUIWin.box_check[index]["S"] = self.SouthCombo.itemData(self.SouthCombo.currentIndex())
        self.GUIWin.box_check[index]["E"] = self.EastCombo.itemData(self.EastCombo.currentIndex())
        self.GUIWin.box_check[index]["W"] = self.WestCombo.itemData(self.WestCombo.currentIndex())
        self.GUIWin.box_check[index]["A"] = self.AboveCombo.itemData(self.AboveCombo.currentIndex())
        self.GUIWin.box_check[index]["B"] = self.BelowCombo.itemData(self.BelowCombo.currentIndex())
        self.AboveLabel.setText("Above Room:")
        self.BelowLabel.setText("Below Room:")
        self.NorthLabel.setText("North Room:")
        self.SouthLabel.setText("South Room:")
        self.EastLabel.setText("East Room:")
        self.WestLabel.setText("West Room:")
       
        #NorthComboArc = self.NorthCombo.currentText()
        #self.GUIWin.box_check[index]["N"] = next((i["RoomID"] for i in self.GUIWin.box_check if i["RoomName"] == NorthComboArc),0)
        #self.NorthCombo.setItemData(0,self.GUIWin.box_check[index]["N"])
       
        #SouthComboArc = self.SouthCombo.currentText()
        #self.GUIWin.box_check[index]["S"] = next((i["RoomID"] for i in self.GUIWin.box_check if i["RoomName"] == SouthComboArc),0)
        #self.SouthCombo.setItemData(0,self.GUIWin.box_check[index]["S"])

        #EastComboArc = self.EastCombo.currentText()
        #self.GUIWin.box_check[index]["E"] = next((i["RoomID"] for i in self.GUIWin.box_check if i["RoomName"] == EastComboArc),0)
        #self.EastCombo.setItemData(0,self.GUIWin.box_check[index]["E"])
        
        #WestComboArc = self.WestCombo.currentText()
        #self.GUIWin.box_check[index]["W"] = next((i["RoomID"] for i in self.GUIWin.box_check if i["RoomName"] == WestComboArc),0)
        #self.WestCombo.setItemData(0,self.GUIWin.box_check[index]["W"])

        #AboveComboArc = self.AboveCombo.currentText()
        #self.GUIWin.box_check[index]["A"] = next((i["RoomID"] for i in self.GUIWin.box_check if i["RoomName"] == AboveComboArc),0)
        #self.AboveCombo.setItemData(0,self.GUIWin.box_check[index]["A"])

        #BelowComboArc = self.BelowCombo.currentText()
        #self.GUIWin.box_check[index]["B"] = next((i["RoomID"] for i in self.GUIWin.box_check if i["RoomName"] == BelowComboArc),0)
        #self.BelowCombo.setItemData(0,self.GUIWin.box_check[index]["B"])
        
        self.setDirectionString()

        self.GUIWin.markAsUnsaved()
        self.close()
    
    def setDirectionString(self):
        # Direction info
        s = ""
        if self.NorthCombo.currentIndex() > 0:
            s+="N"
        if self.SouthCombo.currentIndex() > 0:
            s+="S"
        if self.EastCombo.currentIndex() > 0:
            s+="E"
        if self.WestCombo.currentIndex() > 0:
            s+="W"
        if self.AboveCombo.currentIndex() > 0:
            s+="A"
        if self.BelowCombo.currentIndex() > 0:
            s+="B"

        self.mainRec.connectedRooms.setPlainText(s)

        




class rec(QGraphicsRectItem):
    def __init__(self, *args, **kwargs):
        # INIT
        # Get the custom arguments, then delete.
        # Qt does not like any additional arguments.
        self.graphicsWin = kwargs['graphicsWin']
        self.GUIWin = kwargs['GUIWin']
        self.name = kwargs['name']
        kwargs.pop('graphicsWin')
        kwargs.pop('GUIWin')
        kwargs.pop('name')

        super(rec, self).__init__(*args, **kwargs)
        
        self.nameTextItem = QGraphicsTextItem(self.name,self)
        self.connectedRooms = QGraphicsTextItem(self)
        self.properties = recProperties(self.GUIWin, rect = self)
        self.nameTextItem.setX(args[0])
        self.nameTextItem.setY(args[1])
        self.connectedRooms.setX(args[0])
        self.connectedRooms.setY(args[1] + 30)

        self.setFlag(QGraphicsItem.GraphicsItemFlag.ItemIsMovable,True)
        self.setFlag(QGraphicsItem.GraphicsItemFlag.ItemIsSelectable,True)

        self.rClickMenu = QMenu()
        self.editMenu = QAction()
        self.roomDel = QAction()
        self.editMenu.setObjectName("Open Properties")
        self.editMenu.setText("Open Properties")
        self.roomDel.setObjectName("Delete Room")
        self.roomDel.setText("Delete Room")

        self.editMenu.triggered.connect(self.properties.show)
        self.roomDel.triggered.connect(lambda: self.GUIWin.remove(self))
        self.rClickMenu.addAction(self.editMenu)
        self.rClickMenu.addAction(self.roomDel)
        self.setAcceptDrops(True)

    # Open the properties box on double click.
    def mouseDoubleClickEvent(self, event):
        self.properties.show()

    # Open the menu on right click.
    def contextMenuEvent(self,event):
        self.rClickMenu.exec(self.cursor().pos())

    def sceneEvent(self, event):
        # If an onbject moves, mark it as unsaved.
        if event.type() == QGraphicsSceneMouseEvent.GraphicsSceneMouseMove:
            self.GUIWin.markAsUnsaved()
        # Required here, otherwise nothing happens.
        return super(rec,self).sceneEvent(event)




class gui(mainwindow_ui.Ui_MainWindow, QMainWindow):
    def __init__(self, test_mode=False):
        # INIT
        super(gui, self).__init__()
        self.box_check = []
        self.idIter = 1
        self.scene = QGraphicsScene()
        self.hasUnsavedChanges = False        


        self.ui = mainwindow_ui.Ui_MainWindow()
        self.ui.setupUi(self)
        self.setWindowTitle("MasterForge - Untitled")

        # ACTION CONNECT
        self.ui.actionOpen.triggered.connect(self.openWorkspace)
        self.ui.actionRoom.triggered.connect(self.addRoom)
        self.ui.actionExport.triggered.connect(self.exportData)
        self.ui.actionSave.triggered.connect(self.saveWorkspace)
        self.ui.actionClose.triggered.connect(self.closeWorkspace)
        self.ui.actionBig_Brother.triggered.connect(self.bigBrother)

        # Disable closing workspace, until there is an open workspace
        self.ui.actionClose.setDisabled(True)
        
        # Setup scene
        self.scene.setSceneRect(0, 0, self.ui.graphicsView.size().width(), self.ui.graphicsView.size().height())
        self.ui.graphicsView.setScene(self.scene) 
        self.ui.graphicsView.setTransformationAnchor(QGraphicsView.NoAnchor)
        self.ui.graphicsView.setAlignment(Qt.AlignTop | Qt.AlignLeft)
        self.ui.graphicsView.setViewportUpdateMode(QGraphicsView.MinimalViewportUpdate)
        self.ui.graphicsView.show()

        # Setup save dialog
        self.saveDialog = QMessageBox()
        self.saveDialog.setText("The document has been modified.")
        self.saveDialog.setInformativeText("Do you want to save your changes?")
        self.saveDialog.setStandardButtons(QMessageBox.Save | QMessageBox.Discard | QMessageBox.Cancel)
        self.saveDialog.setDefaultButton(QMessageBox.Save)

    # Remove object from the canvas.
    def remove(self,obj):
        self.markAsUnsaved()
        self.box_check.pop(next((self.box_check.index(i) for i in self.box_check if i["roomDef"] == obj)))
        self.scene.removeItem(obj)
    
    #TODO
    def bigBrother(self):
        QMessageBox.warning(self, 'Not Implmented',
                        'Big Brother is not implmented yet. Possibly in a future release.')

    # Only select objects that are a rectangle
    def filterSceneObjs(self):
        return list(i for i in self.scene.items() if type(i) == rec)

    # Adds a room to the canvas.
    # Coordnates are optional.
    # If no coordnates are added, the object will be at the top of the window.
    def addRoom(self,x=0,y=0):
        roomName, ok = QInputDialog().getText(self,"Add room","Enter room name:")
        roomNameCheck = re.search("[^\r\n\t\f\v ]", roomName)
        if not ok:
            return
        elif roomName == "" or roomNameCheck is None:
            QMessageBox.warning(self, 'Invalid name',
                                'Please enter a name for the room.')
            return
        elif next((True for i in self.box_check if i["RoomName"] == roomName),False):
            QMessageBox.warning(self, 'Invalid name',
                                'You already have a room with this name.')
            return     
        roomName = roomName[roomNameCheck.start():]       
        self.markAsUnsaved()
        
        data = {"RoomID":self.idIter,"RoomName":roomName,"RoomDesc":"","N":0,"S":0,"E":0,"W":0,"A":0,"B":0,"attrib":0}
        self.box_check.append(data)
        self.idIter+=1
        self.scene.addItem(rec(x,y,60,60,graphicsWin=self.ui.graphicsView,GUIWin=self,name=roomName))

        # Qt likes to put new objects at the beginning of the list.
        self.box_check[-1]["roomDef"] = self.filterSceneObjs()[0]

    # Import room from a file.
    def importRoom(self,data):
        x = data["X"]
        y = data["Y"]
        # Data is popped, to keep consistancy.
        data.pop("X")
        data.pop("Y")
        self.box_check.append(data)
        self.scene.addItem(rec(x,y,60,60,graphicsWin=self.ui.graphicsView,GUIWin=self,name=data["RoomName"]))

        # Qt likes to put new objects at the beginning of the list.
        self.box_check[-1]["roomDef"] = self.filterSceneObjs()[0]
    
    # Right click on the canvas to show this menu.
    def contextMenuEvent(self,event):
        menu = QMenu()
        addmen = QAction()

        addmen.setObjectName("Add at Cursor")
        addmen.setText("Add at Cursor")
        menu.addAction(addmen)
        menu.addSeparator()  

        addmen.triggered.connect(lambda: self.addRoom(event.x(),event.y()))   

        pt = QPoint()
        pt.setX(event.globalX())
        pt.setY(event.globalY())

        menu.exec(pt)

    # Create the description file in MBMF format
    def exportData(self):
        loc, ok = QFileDialog.getSaveFileName(self,"Export map data",'map', "*.mbm")
        if not ok:
            return
        with open(loc, "wb") as dataFile:
            dataFile.write(bytes("MBMF",'utf-8')) #Magic
            dataFile.write(struct.pack('=H', 0xFEFF)) #Endian
            dataFile.write(struct.pack('=H', 0x0000)) #Version
            dataFile.write(struct.pack('=I', 0x0000)) #Hash
            dataFile.write(struct.pack('=I', len(self.box_check)))
            for item in self.box_check:
                dataFile.write(struct.pack('=I', item["RoomID"])) #ID
                dataFile.write(struct.pack('=I', item["N"])) #N
                dataFile.write(struct.pack('=I', item["S"])) #S
                dataFile.write(struct.pack('=I', item["E"])) #E
                dataFile.write(struct.pack('=I', item["W"])) #W
                dataFile.write(struct.pack('=I', item["A"])) #A
                dataFile.write(struct.pack('=I', item["B"])) #B
                dataFile.write(struct.pack('=Q', item["attrib"])) #attrib
        self.descriptionExport(loc)

    # Create the description file in MBMD format
    def descriptionExport(self,metaFile):
        fileInfo = QFileInfo(metaFile)
        baseName = fileInfo.absoluteFilePath()[:-4]
        with open(f"{baseName}.mbd", "wb") as dataFile:
            dataFile.write(bytes("MBMD",'utf-8')) #Magic
            dataFile.write(struct.pack('=H', 0xFEFF)) #Endian
            dataFile.write(struct.pack('=H', 0x0000)) #Version
            dataFile.write(struct.pack('=I', 0x0000)) #Hash
            dataFile.write(struct.pack('=I', len(self.box_check))) #Number of Rooms
            for item in self.box_check:
                dataFile.write(struct.pack('=I', item["RoomID"])) #ID
                dataFile.write(struct.pack('=I', len(item["RoomDesc"]) + (4-(len(item["RoomDesc"])))%4)) #Length
                dataFile.write(bytes(item["RoomDesc"],"utf-8")) #Room Description
                for x in range((4-(len(item["RoomDesc"])))%4): #Padding
                    dataFile.write(b'\0')
    
    # Save the workspace to a MFW file.
    def saveWorkspace(self):
        loc, ok = QFileDialog.getSaveFileName(self,"Save Project workspace",'map_workspace',"*.mfw")
        
        if not ok:
            return False
        
        file_info = QFileInfo(loc)
        wsSave = {"version":VERSION,"iteration":self.idIter,"data":[]}        
        for item in self.box_check:
            temp = item.copy()
            temp['X'] = temp["roomDef"].rect().x() + temp["roomDef"].x()
            temp['Y'] = temp["roomDef"].rect().y() + temp["roomDef"].y()
            temp.pop("roomDef")
            wsSave["data"].append(temp)
        with open("map_workspace.mfw", "w") as ws:
            json.dump(wsSave,ws)
        self.setWindowTitle(f"MasterForge - {file_info.fileName()}")
        self.hasUnsavedChanges = False
        self.ui.actionClose.setDisabled(False)
        return True
    
    # Open a workspace file
    def openWorkspace(self):
        loc, ok = QFileDialog.getOpenFileName(self,"Open Project workspace",'map_workspace',"*.mfw")
        if not ok:
            return
        data = []
        self.closeWorkspace()
        file_info = QFileInfo(loc)
        
        loc.split()
        with open(loc, "r") as ws:
            data = json.load(ws)
        if data['version'] > VERSION:
            QMessageBox.warning(self, 'New file version',
                                'This file has been created in a newer version of MasterForge. Please upgrade MasterForge to continue.')
            return
        if data['version'] < VERSION:
            ok = QMessageBox.question(self, 'Upgrade file',
                                'This file has been created in a older version of MasterForge. Update the file?',QMessageBox.Ok,QMessageBox.Cancel)
            if ok == QMessageBox.Cancel:
                return
            
        self.idIter = data['iteration']

        for item in data["data"]:
            self.importRoom(item)
        for item in self.box_check:
            item["roomDef"].properties.update()
        self.autoConnect(data["data"])
        self.setWindowTitle(f"MasterForge - {file_info.fileName()}")
        self.ui.actionClose.setDisabled(False)
        self.hasUnsavedChanges = False
    
    def autoConnect(self,data):
        for item in data:
            for x in ["A","B","N","S","E","W"]:
                item["roomDef"].properties.setComboBoxID(x,item[x])



    # Closes (and saves if necessary) the workspace
    def closeWorkspace(self):
        if self.hasUnsavedChanges:
            ret = self.saveDialog.exec()
            if ret == QMessageBox.Save:
                # Ensure saving happens first.
                saveCheck = self.saveWorkspace()
                if saveCheck:
                    self.cleanWorkSpace()                
                    return True
            elif ret == QMessageBox.Discard:
                self.cleanWorkSpace()            
                return True
            return False
        else:
            self.cleanWorkSpace()
            return True
    
    # Resets the workspace
    def cleanWorkSpace(self):
        for i, item in enumerate(self.box_check):
            self.box_check.pop(i)
        for item in self.ui.graphicsView.items():
            self.scene.removeItem(item)
        self.setWindowTitle(f"MasterForge - Untitled")
        self.ui.actionClose.setDisabled(True)
        self.idIter = 1
        self.hasUnsavedChanges = False
    
    def markAsUnsaved(self):
        if self.hasUnsavedChanges is False: 
            self.setWindowTitle(self.windowTitle()+"*")
            self.hasUnsavedChanges = True
        
    # Make sure to save work if necessary BEFORE closing the program.
    def closeEvent(self, closeEvent):
        if self.closeWorkspace():
            closeEvent.accept()
        else:
            closeEvent.ignore()
            
# Program Launch 
if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = gui()
    win.show()
    sys.exit(app.exec())