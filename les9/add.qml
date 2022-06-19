import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4

Window {
    width: 300
    height: 100

    function clear()
    {
        taskEdit.text = ""
        priority.currentIndex = 0
        calendar.data = Date.now();
    }

    ColumnLayout
    {
        anchors.fill: parent
        anchors.margins: 1
        spacing: 1

        RowLayout
        {
            Label
            {
               width: 70
               text: qsTr("Task")
            }

            TextField
            {
                id: taskEdit
                width: 230
            }
        }

        RowLayout
        {
            Label
            {
                width: 70
                text: qsTr("Date")
            }

            Calendar
            {
                id: calendar
                width: 80
            }

            Label
            {
                width: 70
            }

            ComboBox
            {
                id: priority
                width: 80
                data: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
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
                id: add_button
                Layout.preferredHeight: 30
                Layout.fillWidth: true
                text: qsTr("Add")
                onClicked: { }
            }

            Button
            {
                id: clear_button
                Layout.preferredHeight: 30
                Layout.fillWidth: true
                text: qsTr("Add")
                onClicked: { clear() }
            }
        }
    }
}
