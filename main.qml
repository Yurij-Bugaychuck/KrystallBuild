import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs.qml 1.0

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Button {
        id: button
        x: 197
        y: 383
        width: 247
        height: 63
        text: qsTr("Визуализировать")
        z: 0
        rotation: 0
        enabled: true
        smooth: true
        antialiasing: false
        scale: 1
        font.pointSize: 10
        padding: 16
        autoExclusive: false
        highlighted: false
        flat: false
        autoRepeat: false
        font.bold: false
        checked: false
        checkable: false
        transformOrigin: Item.Center
    }

    Connections {
        target: button
        onClicked: {
            var s = MainWindow.buttonClicked(element4.text, element5.text, element6.text);
            element2.text = s;
            MainWindow.buttonClickedDraw(element4.text, element5.text, element6.text);
        }
    }
    Connections {
        target: button1
        onClicked: {
            var s = MainWindow.buttonClicked(element4.text, element5.text, element6.text);
            element2.text = s;
//            MainWindow.buttonClickedDraw(indexMiller.text);
        }
    }

    Rectangle {
        id: rectangle
        x: 180
        y: 133
        width: 37
        height: 25
        color: "#ffffff"
        radius: 1
        border.width: 2
        border.color: "#bdbdbd"

        TextEdit {
            id: element4
            x: 0
            y: 0
            width: parent.width
            height: parent.height
            text: qsTr("1")
            readOnly: false
            cursorVisible: false
            textFormat: Text.PlainText
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 12
        }
    }
    Rectangle {
        id: rectangle2
        x: 224
        y: 133
        width: 38
        height: 25
        color: "#ffffff"
        radius: 1
        border.width: 2
        border.color: "#bdbdbd"

        TextEdit {
            id: element5
            x: 0
            y: 0
            width: parent.width
            height: parent.height
            text: qsTr("1")
            textFormat: Text.PlainText
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 12
        }
    }
    Rectangle {
        id: rectangle3
        x: 268
        y: 133
        width: 38
        height: 25
        color: "#ffffff"
        radius: 1
        border.width: 2
        border.color: "#bdbdbd"

        TextEdit {
            id: element6
            x: 0
            y: 0
            width: parent.width
            height: parent.height
            text: qsTr("1")
            textFormat: Text.PlainText
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 12
        }
    }

    Text {
        id: element
        x: 33
        y: 139
        width: 119
        height: 14
        text: qsTr("Индекс Миллера:")
        font.pixelSize: 12
    }

    Button {
        id: button1
        x: 369
        y: 88
        width: 247
        height: 37
        text: qsTr("Рассчитать")
        checked: false
        antialiasing: false
        checkable: false
        smooth: true
        padding: 16
        autoRepeat: false
        scale: 1
        flat: false
        enabled: true
        autoExclusive: false
        rotation: 0
        transformOrigin: Item.Center
        font.bold: false
        z: 0
        highlighted: false
        font.pointSize: 10

    }

    ComboBox {
        id: comboBox
        x: 180
        y: 80
        width: 127
        height: 40
        wheelEnabled: false
        enabled: false
        clip: false
        flat: false
        editable: true
        currentIndex: -1
         model: [ "ОЦК", "ГПУ" ]
    }

    Text {
        id: element1
        x: 33
        y: 95
        width: 119
        height: 14
        text: qsTr("Тип решётки")
        font.pixelSize: 12
    }

    Text {
        id: element2
        x: 369
        y: 131
        width: 247
        height: 197
        text: qsTr("Text")
        font.pixelSize: 12
    }
    ComboBox {
        id: comboBox1
        x: 181
        y: 24
        width: 127
        height: 40
        currentIndex: -1
        model: [ "Рений", "Бериллий", "Магний" ]
    }

    Text {
        id: element3
        x: 34
        y: 37
        width: 119
        height: 14
        text: qsTr("Метал")
        font.pixelSize: 12
    }


}

/*##^##
Designer {
    D{i:1;anchors_x:244;anchors_y:327}D{i:2;anchors_height:55;anchors_width:200;anchors_x:85;anchors_y:87}
D{i:3;anchors_height:55;anchors_width:200;anchors_x:85;anchors_y:87}D{i:4;anchors_height:20;anchors_width:80;anchors_x:8;anchors_y:57}
D{i:6;anchors_x:244;anchors_y:327}
}
##^##*/
