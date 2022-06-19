import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.1
import QtQml.Models 2.12
import TableModel 0.1


Window {
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
        if (col === 0) return 450
        else if (col === 1) return 75
        else if (col === 2) return 75
    }

    function paintSelectedRow(header, cell)
    {
        if (header === false)
        {
            cell.color = "light blue"
        }
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
                    anchors.horizontalCenter: (header || column === 1 || column === 2) ? parent.horizontalCenter : undefined
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
                onClicked: { tableModel.onAdd() }
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
                id: quit_button
                text: qsTr("Quit")
                onClicked: { tableModel.onClose(); Qt.quit() }
            }
        }
    }
}
