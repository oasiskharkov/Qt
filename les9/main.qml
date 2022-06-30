import QtQuick 2.12
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2
import QtQml.Models 2.12
import TableModel 0.1
import Qt.labs.qmlmodels 1.0
import QtQuick.Controls.Material 2.12

ApplicationWindow {
    id: mainWindow
    width: 600
    height: 400
    minimumWidth: 600
    maximumWidth: 600
    minimumHeight: 400
    maximumHeight: 400
    visible: true
    color: "gray"
    title: qsTr("Organizer")

    property int selectedIndex: -1

    function getWidth(col) {
        if (col === 0) return 30
        else if (col === 1) return 420
        else if (col === 2 || col === 3) return 75
    }

    function setFontBold(row)
    {
        return (row === 0 ? true : false)
    }

    function clearEntry()
    {
        taskEdit.text = ""
        priority.currentIndex = 0
        calendar.text = "";
    }

    function setHorizontalCenterAnchors(row, col, parent)
    {
        return row === 0 || col === 0 || col === 2 || col === 3 ? parent.horizontalCenter : undefined
    }

    function setLeftAnchors(row, col, parent)
    {
        return row !== 0 && col === 1 ? parent.left : undefined
    }

    function isHighlighted(row)
    {
        return row === selectedIndex && row !== 0
    }

    function getCellColor(header)
    {
        return header ? "light blue" : "white"
    }

    ColumnLayout
    {
        anchors.fill: parent
        anchors.margins: 1
        spacing: 1
        antialiasing: true

        TableView {
            id: task_list
            Layout.fillHeight: true
            Layout.fillWidth: true
            columnSpacing: 1
            rowSpacing: 1
            clip: true
            model: tableModel


            ItemSelectionModel {
                id: sm
                model: tableModel
            }

            delegate:
                Rectangle {
                id: cell
                implicitWidth: getWidth(column)
                implicitHeight: 30
                color: getCellColor(header)

                Text {
                    id: text
                    anchors.left: setLeftAnchors(row, column, parent)
                    anchors.horizontalCenter: setHorizontalCenterAnchors(row, column, parent)
                    anchors.verticalCenter: parent.verticalCenter
                    text: tabledata
                    font.bold: setFontBold(row)
                }

                ItemDelegate {
                    id: selectedItem
                    implicitWidth: getWidth(column)
                    implicitHeight: 30
                    highlighted: isHighlighted(row)

                    Text {
                        id: selectedText
                        anchors.left: setLeftAnchors(row, column, parent)
                        anchors.horizontalCenter: setHorizontalCenterAnchors(row, column, parent)
                        anchors.verticalCenter: parent.verticalCenter
                        text: (isHighlighted(row) ? tabledata : "")
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: { sm.select(tableModel.index(row, column), ItemSelectionModel.Select | ItemSelectionModel.Current); selectedIndex = row }
                }
            }
        }

        RowLayout {
            anchors.margins: 1
            spacing: 1
            Layout.alignment: Qt.AlignBottom
            Layout.fillWidth: true

            Button {
                id: add_button
                Layout.preferredHeight: 30
                Layout.fillWidth: true
                text: qsTr("Add")
                onClicked: { add_entry_dialog.open() }
            }

            Button {
                id: remove_button
                Layout.preferredHeight: 30
                Layout.fillWidth: true
                text: qsTr("Remove")
                onClicked: { tableModel.onRemove(selectedIndex) }
            }

            Button {
                id: clear_button
                Layout.preferredHeight: 30
                Layout.fillWidth: true
                text: qsTr("Clear")
                onClicked: { tableModel.onClear()}
            }

            Button {
                Layout.preferredHeight: 30
                Layout.fillWidth: true
                id: save_button
                text: qsTr("Save")
                onClicked: { tableModel.onSave(); }
            }

            Button {
                Layout.preferredHeight: 30
                Layout.fillWidth: true
                id: quit_button
                text: qsTr("Quit")
                onClicked: { Qt.quit() }
            }
        }
    }

    Dialog {
        id: add_entry_dialog
        title: "Add Task"
        width: 300
        height: 94

        contentItem: Rectangle {
            antialiasing: true
            ColumnLayout
            {
                anchors.margins: 1
                spacing: 1

                RowLayout
                {
                    anchors.margins: 1
                    spacing: 1

                    Label
                    {
                       Layout.preferredWidth:  30
                       text: qsTr("Task")
                       horizontalAlignment: Qt.AlignRight
                    }

                    TextField
                    {
                        id: taskEdit
                        width: 230
                        Layout.preferredWidth:  270
                        Layout.preferredHeight: 30
                        selectByMouse: true
                    }
                }

                RowLayout
                {
                    anchors.margins: 1
                    spacing: 1

                    Label
                    {
                        Layout.preferredWidth:  30
                        text: qsTr("Date")
                        horizontalAlignment: Qt.AlignRight
                    }

                    TextField
                    {
                        id: calendar
                        Layout.preferredWidth:  120
                        Layout.preferredHeight: 30
                        selectByMouse: true
                    }

                    Label
                    {
                        Layout.preferredWidth:  45
                        text: qsTr("Priority")
                        horizontalAlignment: Qt.AlignRight
                    }

                    ComboBox
                    {
                        id: priority
                        Layout.preferredWidth:  105
                        model: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
                        Layout.preferredHeight: 30
                        background: Rectangle { color: "white" }
                    }
                }

                RowLayout
                {
                    anchors.margins: 1
                    spacing: 1
                    Layout.alignment: Qt.AlignBottom
                    Layout.fillWidth: true

                    Button
                    {
                        id: add_entry
                        Layout.preferredHeight: 30
                        Layout.fillWidth: true
                        text: qsTr("Add")
                        onClicked: { tableModel.onAdd(taskEdit.text, calendar.text, priority.currentText); add_entry_dialog.close() }
                    }

                    Button
                    {
                        id: clear_entry
                        Layout.preferredHeight: 30
                        Layout.fillWidth: true
                        text: qsTr("Clear")
                        onClicked: { clearEntry() }
                    }
                }
            }
        }
    }
}
