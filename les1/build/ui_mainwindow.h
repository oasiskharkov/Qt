/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *task3_groupBox;
    QTextEdit *task3_textEdit;
    QPlainTextEdit *task3_plainTextEdit;
    QPushButton *task3_add_pushButton;
    QPushButton *task3_replace_pushButton;
    QPushButton *task3_insert_pushButton;
    QGroupBox *task2_groupBox;
    QLineEdit *task2_a_lineEdit;
    QLineEdit *task2_b_lineEdit;
    QLineEdit *task2_gamma_lineEdit;
    QLineEdit *task2_c_lineEdit;
    QPushButton *task2_solve_pushButton;
    QPushButton *task2_clear_pushButton;
    QGroupBox *task2_angle_groupBox;
    QRadioButton *task2_deg_radioButton;
    QRadioButton *task2_rad_radioButton;
    QLabel *task2_a_label;
    QLabel *task2_b_label;
    QLabel *task2_gamma_label;
    QLabel *task2_c_label;
    QLabel *task1_label_2;
    QGroupBox *task1_groupBox;
    QLabel *task1_a_label;
    QLabel *task1_b_label;
    QLabel *task1_c_label;
    QLabel *task1_result_label;
    QLabel *task1_label;
    QLineEdit *task1_a_lineEdit;
    QLineEdit *task1_b_lineEdit;
    QLineEdit *task1_c_lineEdit;
    QLineEdit *task1_result_lineEdit;
    QPushButton *task1_solve_pushButton;
    QPushButton *task1_clear_pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(788, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        task3_groupBox = new QGroupBox(centralwidget);
        task3_groupBox->setObjectName(QString::fromUtf8("task3_groupBox"));
        task3_groupBox->setGeometry(QRect(360, 10, 411, 251));
        task3_textEdit = new QTextEdit(task3_groupBox);
        task3_textEdit->setObjectName(QString::fromUtf8("task3_textEdit"));
        task3_textEdit->setGeometry(QRect(10, 30, 271, 101));
        task3_plainTextEdit = new QPlainTextEdit(task3_groupBox);
        task3_plainTextEdit->setObjectName(QString::fromUtf8("task3_plainTextEdit"));
        task3_plainTextEdit->setGeometry(QRect(10, 140, 271, 101));
        task3_add_pushButton = new QPushButton(task3_groupBox);
        task3_add_pushButton->setObjectName(QString::fromUtf8("task3_add_pushButton"));
        task3_add_pushButton->setGeometry(QRect(290, 30, 111, 25));
        task3_replace_pushButton = new QPushButton(task3_groupBox);
        task3_replace_pushButton->setObjectName(QString::fromUtf8("task3_replace_pushButton"));
        task3_replace_pushButton->setGeometry(QRect(290, 60, 111, 25));
        task3_insert_pushButton = new QPushButton(task3_groupBox);
        task3_insert_pushButton->setObjectName(QString::fromUtf8("task3_insert_pushButton"));
        task3_insert_pushButton->setGeometry(QRect(290, 90, 111, 25));
        task2_groupBox = new QGroupBox(centralwidget);
        task2_groupBox->setObjectName(QString::fromUtf8("task2_groupBox"));
        task2_groupBox->setGeometry(QRect(10, 220, 329, 203));
        task2_a_lineEdit = new QLineEdit(task2_groupBox);
        task2_a_lineEdit->setObjectName(QString::fromUtf8("task2_a_lineEdit"));
        task2_a_lineEdit->setGeometry(QRect(60, 50, 113, 25));
        QFont font;
        font.setPointSize(10);
        task2_a_lineEdit->setFont(font);
        task2_a_lineEdit->setMaxLength(32767);
        task2_b_lineEdit = new QLineEdit(task2_groupBox);
        task2_b_lineEdit->setObjectName(QString::fromUtf8("task2_b_lineEdit"));
        task2_b_lineEdit->setGeometry(QRect(60, 80, 113, 25));
        task2_b_lineEdit->setFont(font);
        task2_gamma_lineEdit = new QLineEdit(task2_groupBox);
        task2_gamma_lineEdit->setObjectName(QString::fromUtf8("task2_gamma_lineEdit"));
        task2_gamma_lineEdit->setGeometry(QRect(60, 110, 113, 25));
        task2_gamma_lineEdit->setFont(font);
        task2_c_lineEdit = new QLineEdit(task2_groupBox);
        task2_c_lineEdit->setObjectName(QString::fromUtf8("task2_c_lineEdit"));
        task2_c_lineEdit->setGeometry(QRect(60, 140, 261, 25));
        task2_c_lineEdit->setFont(font);
        task2_c_lineEdit->setReadOnly(true);
        task2_solve_pushButton = new QPushButton(task2_groupBox);
        task2_solve_pushButton->setObjectName(QString::fromUtf8("task2_solve_pushButton"));
        task2_solve_pushButton->setGeometry(QRect(60, 170, 130, 25));
        task2_solve_pushButton->setFont(font);
        task2_clear_pushButton = new QPushButton(task2_groupBox);
        task2_clear_pushButton->setObjectName(QString::fromUtf8("task2_clear_pushButton"));
        task2_clear_pushButton->setGeometry(QRect(197, 170, 124, 25));
        task2_angle_groupBox = new QGroupBox(task2_groupBox);
        task2_angle_groupBox->setObjectName(QString::fromUtf8("task2_angle_groupBox"));
        task2_angle_groupBox->setGeometry(QRect(200, 52, 120, 74));
        task2_deg_radioButton = new QRadioButton(task2_angle_groupBox);
        task2_deg_radioButton->setObjectName(QString::fromUtf8("task2_deg_radioButton"));
        task2_deg_radioButton->setGeometry(QRect(10, 30, 96, 23));
        task2_deg_radioButton->setChecked(true);
        task2_rad_radioButton = new QRadioButton(task2_angle_groupBox);
        task2_rad_radioButton->setObjectName(QString::fromUtf8("task2_rad_radioButton"));
        task2_rad_radioButton->setGeometry(QRect(10, 50, 96, 23));
        task2_a_label = new QLabel(task2_groupBox);
        task2_a_label->setObjectName(QString::fromUtf8("task2_a_label"));
        task2_a_label->setGeometry(QRect(43, 53, 16, 17));
        task2_a_label->setFont(font);
        task2_a_label->setAlignment(Qt::AlignCenter);
        task2_b_label = new QLabel(task2_groupBox);
        task2_b_label->setObjectName(QString::fromUtf8("task2_b_label"));
        task2_b_label->setGeometry(QRect(43, 83, 16, 17));
        task2_b_label->setFont(font);
        task2_b_label->setAlignment(Qt::AlignCenter);
        task2_b_label->setWordWrap(false);
        task2_b_label->setMargin(0);
        task2_gamma_label = new QLabel(task2_groupBox);
        task2_gamma_label->setObjectName(QString::fromUtf8("task2_gamma_label"));
        task2_gamma_label->setGeometry(QRect(0, 113, 61, 20));
        task2_gamma_label->setFont(font);
        task2_gamma_label->setAlignment(Qt::AlignCenter);
        task2_gamma_label->setWordWrap(false);
        task2_gamma_label->setMargin(0);
        task2_c_label = new QLabel(task2_groupBox);
        task2_c_label->setObjectName(QString::fromUtf8("task2_c_label"));
        task2_c_label->setGeometry(QRect(43, 142, 16, 20));
        task2_c_label->setFont(font);
        task2_c_label->setAlignment(Qt::AlignCenter);
        task2_c_label->setWordWrap(false);
        task2_c_label->setMargin(0);
        task1_label_2 = new QLabel(task2_groupBox);
        task1_label_2->setObjectName(QString::fromUtf8("task1_label_2"));
        task1_label_2->setGeometry(QRect(60, 25, 211, 20));
        task1_label_2->setFont(font);
        task1_groupBox = new QGroupBox(centralwidget);
        task1_groupBox->setObjectName(QString::fromUtf8("task1_groupBox"));
        task1_groupBox->setGeometry(QRect(20, 10, 319, 204));
        task1_groupBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        task1_groupBox->setFlat(false);
        task1_groupBox->setCheckable(false);
        task1_a_label = new QLabel(task1_groupBox);
        task1_a_label->setObjectName(QString::fromUtf8("task1_a_label"));
        task1_a_label->setGeometry(QRect(33, 53, 16, 17));
        task1_a_label->setFont(font);
        task1_a_label->setAlignment(Qt::AlignCenter);
        task1_b_label = new QLabel(task1_groupBox);
        task1_b_label->setObjectName(QString::fromUtf8("task1_b_label"));
        task1_b_label->setGeometry(QRect(33, 84, 16, 17));
        task1_b_label->setFont(font);
        task1_b_label->setAlignment(Qt::AlignCenter);
        task1_b_label->setWordWrap(false);
        task1_b_label->setMargin(0);
        task1_c_label = new QLabel(task1_groupBox);
        task1_c_label->setObjectName(QString::fromUtf8("task1_c_label"));
        task1_c_label->setGeometry(QRect(32, 113, 16, 17));
        task1_c_label->setFont(font);
        task1_c_label->setAlignment(Qt::AlignCenter);
        task1_c_label->setWordWrap(false);
        task1_c_label->setMargin(0);
        task1_result_label = new QLabel(task1_groupBox);
        task1_result_label->setObjectName(QString::fromUtf8("task1_result_label"));
        task1_result_label->setGeometry(QRect(8, 144, 41, 17));
        task1_result_label->setFont(font);
        task1_label = new QLabel(task1_groupBox);
        task1_label->setObjectName(QString::fromUtf8("task1_label"));
        task1_label->setGeometry(QRect(30, 25, 271, 20));
        task1_label->setFont(font);
        task1_a_lineEdit = new QLineEdit(task1_groupBox);
        task1_a_lineEdit->setObjectName(QString::fromUtf8("task1_a_lineEdit"));
        task1_a_lineEdit->setGeometry(QRect(50, 50, 113, 25));
        task1_a_lineEdit->setFont(font);
        task1_a_lineEdit->setMaxLength(32767);
        task1_b_lineEdit = new QLineEdit(task1_groupBox);
        task1_b_lineEdit->setObjectName(QString::fromUtf8("task1_b_lineEdit"));
        task1_b_lineEdit->setGeometry(QRect(50, 80, 113, 25));
        task1_b_lineEdit->setFont(font);
        task1_c_lineEdit = new QLineEdit(task1_groupBox);
        task1_c_lineEdit->setObjectName(QString::fromUtf8("task1_c_lineEdit"));
        task1_c_lineEdit->setGeometry(QRect(50, 110, 113, 25));
        task1_c_lineEdit->setFont(font);
        task1_result_lineEdit = new QLineEdit(task1_groupBox);
        task1_result_lineEdit->setObjectName(QString::fromUtf8("task1_result_lineEdit"));
        task1_result_lineEdit->setGeometry(QRect(50, 140, 261, 25));
        task1_result_lineEdit->setFont(font);
        task1_result_lineEdit->setReadOnly(true);
        task1_solve_pushButton = new QPushButton(task1_groupBox);
        task1_solve_pushButton->setObjectName(QString::fromUtf8("task1_solve_pushButton"));
        task1_solve_pushButton->setGeometry(QRect(50, 170, 130, 25));
        task1_solve_pushButton->setFont(font);
        task1_clear_pushButton = new QPushButton(task1_groupBox);
        task1_clear_pushButton->setObjectName(QString::fromUtf8("task1_clear_pushButton"));
        task1_clear_pushButton->setGeometry(QRect(187, 170, 124, 25));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 788, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Lesson1", nullptr));
        task3_groupBox->setTitle(QApplication::translate("MainWindow", "Task3", nullptr));
        task3_add_pushButton->setText(QApplication::translate("MainWindow", "Add", nullptr));
        task3_replace_pushButton->setText(QApplication::translate("MainWindow", "Replace", nullptr));
        task3_insert_pushButton->setText(QApplication::translate("MainWindow", "Insert html", nullptr));
        task2_groupBox->setTitle(QApplication::translate("MainWindow", "Task2", nullptr));
        task2_solve_pushButton->setText(QApplication::translate("MainWindow", "Solve", nullptr));
        task2_clear_pushButton->setText(QApplication::translate("MainWindow", "Clear", nullptr));
        task2_angle_groupBox->setTitle(QApplication::translate("MainWindow", " Angle in:", nullptr));
        task2_deg_radioButton->setText(QApplication::translate("MainWindow", "deg", nullptr));
        task2_rad_radioButton->setText(QApplication::translate("MainWindow", "rad", nullptr));
        task2_a_label->setText(QApplication::translate("MainWindow", "a:", nullptr));
        task2_b_label->setText(QApplication::translate("MainWindow", "b:", nullptr));
        task2_gamma_label->setText(QApplication::translate("MainWindow", "gamma:", nullptr));
        task2_c_label->setText(QApplication::translate("MainWindow", "c:", nullptr));
        task1_label_2->setText(QApplication::translate("MainWindow", "Find the third side of the triangle", nullptr));
        task1_groupBox->setTitle(QApplication::translate("MainWindow", "Task1", nullptr));
        task1_a_label->setText(QApplication::translate("MainWindow", "a:", nullptr));
        task1_b_label->setText(QApplication::translate("MainWindow", "b:", nullptr));
        task1_c_label->setText(QApplication::translate("MainWindow", "c:", nullptr));
        task1_result_label->setText(QApplication::translate("MainWindow", "result:", nullptr));
        task1_label->setText(QApplication::translate("MainWindow", "Solve a quadratic equation: ax^2 + bx + c = 0 ", nullptr));
        task1_solve_pushButton->setText(QApplication::translate("MainWindow", "Solve", nullptr));
        task1_clear_pushButton->setText(QApplication::translate("MainWindow", "Clear", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
