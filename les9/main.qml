import QtQuick 2.12
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2
import QtQml.Models 2.12
import TableModel 0.1

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

    function paintSelectedRow(header, cell)
    {
        if (header === false)
        {
            cell.color = "light blue"
        }
    }

    function clear()
    {
        taskEdit.text = ""
        priority.currentIndex = 0
        calendar.text = "";
    }

    ColumnLayout
    {
        anchors.fill: parent
        anchors.margins: 1
        spacing: 1

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
                color: (header ? "pink" : "white")

                Text {
                    id: text
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    text: tabledata
                    font.bold: (row === 0 ? true : false)
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: { sm.select(tableModel.index(row, column), ItemSelectionModel.Select | ItemSelectionModel.Current);
                        selectedIndex = row; paintSelectedRow(header, cell) }
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
        title: "Add Entry"
        width: 300
        height: 94

        contentItem: Rectangle {
            anchors.margins: 1

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
                        onClicked: { clear() }
                    }
                }
            }
        }
    }
}
