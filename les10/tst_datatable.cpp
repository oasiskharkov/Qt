#include <QtTest>
#include  "./../les9/tablemodel.h"

class datatable_ut : public QObject
{
    Q_OBJECT

public:
    datatable_ut();
    ~datatable_ut();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void init_test_case();
    void row_count_test_case();
    void column_count_test_case();
    void entry_count_test_case();
    void remove_test_case();
    void add_test_case();
    void save_test_case();
    void clear_test_case();
    void check_date_test_case();
    void parse_string_test_case();
    void create_datatable_benchmark();

private:
    void create_test_file();

private:
    TableModel* tm;
};

datatable_ut::datatable_ut()
{
    create_test_file();
}

datatable_ut::~datatable_ut()
{

}

void datatable_ut::create_test_file()
{
    QFile file("base.txt");
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);
        out << "To do homework" << ' ' << "05.08.2022" << ' ' << "1" << "\n";
        out << "To do cleaning" << ' ' << "06.08.2022" << ' ' << "2" << "\n";
        out << "To do task" << ' ' << "07.08.2022" << ' ' << "3" << "\n";

        file.close();
        qInfo() << "Test file base.txt was successfully created!";
    }
}

void datatable_ut::initTestCase()
{
    tm = new TableModel(); // load data from test file base.txt
}

void datatable_ut::cleanupTestCase()
{
    delete tm;
}

void datatable_ut::init_test_case()
{
    QStringList headersEntry {"", "Task", "Date", "Priority"};
    QStringList entry1 {"", "To do homework", "05.08.2022", "1"};
    QStringList entry2 {"", "To do cleaning", "06.08.2022", "2"};
    QStringList entry3 {"", "To do task", "07.08.2022", "3"};

    QVERIFY2(tm != nullptr, "Datatable was created");
    QVERIFY2(tm->rowCount() == 4, "Datatable initial size");
    QVERIFY2(tm->getRow(0) == headersEntry, "Check datatable headers");

    QCOMPARE(entry1, tm->getRow(1));
    QCOMPARE(entry2, tm->getRow(2));
    QCOMPARE(entry3, tm->getRow(3));
}

void datatable_ut::row_count_test_case()
{
    QVERIFY2(tm->rowCount() == 4, "Datatable row count");
}

void datatable_ut::column_count_test_case()
{
    QVERIFY2(tm->columnCount() == 4, "Datatable column count");
}

void datatable_ut::entry_count_test_case()
{
    QVERIFY2(tm->entriesCount() == 3, "Entries count in base.txt file");
    QVERIFY2(tm->entriesCount() == tm->rowCount() - 1, "Check real entries count");
}

void datatable_ut::remove_test_case()
{
    QVERIFY2(tm->entriesCount() == 3, "Entries count before deleting");
    tm->onRemove(1);
    QVERIFY2(tm->entriesCount() == 2, "Entries count after deleting");
    QVERIFY2(tm->findTask("To do homework") == false, "Try to find deleted task");
}

void datatable_ut::add_test_case()
{
    QVERIFY2(tm->entriesCount() == 2, "Entries count before adding");
    tm->onAdd("To do homework", "05.08.2022", "1");
    QVERIFY2(tm->entriesCount() == 3, "Entries count after adding");
    QVERIFY2(tm->findTask("To do homework") == true, "Try to find added task");
}

void datatable_ut::save_test_case()
{
    tm->onSave();
    TableModel* new_tm = new TableModel();

    QStringList headersEntry {"", "Task", "Date", "Priority"};

    QStringList entry1 {"", "To do cleaning", "06.08.2022", "2"};
    QStringList entry2 {"", "To do task", "07.08.2022", "3"};
    QStringList entry3 {"", "To do homework", "05.08.2022", "1"};

    QVERIFY2(new_tm != nullptr, "Datatable was created");
    QVERIFY2(new_tm->rowCount() == 4, "Datatable initial size");
    QVERIFY2(new_tm->getRow(0) == headersEntry, "Check datatable headers");

    QCOMPARE(entry1, new_tm->getRow(1));
    QCOMPARE(entry2, new_tm->getRow(2));
    QCOMPARE(entry3, new_tm->getRow(3));

    delete new_tm;
}

void datatable_ut::clear_test_case()
{
     QVERIFY2(tm->entriesCount() == 3, "Entries count before clearing");
     tm->onClear();
     QVERIFY2(tm->entriesCount() == 0, "Entries count after clearing");
     QVERIFY2(tm->findTask("Task") == true, "Try to find headers row");
}

void datatable_ut::check_date_test_case()
{
    QString correctDate1{"22.01.2022"};
    QString correctDate2{"01-03-1999"};
    QString correctDate3{"12/12/2006"};
    QString incorrectDate1{"01.13.2015"};
    QString incorrectDate2{"99.12.2001"};
    QString incorrectDate3{"01.01.2222"};
    QString incorrectDate4{"01.01.22"};
    QString incorrectDate5{".."};
    QString incorrectDate6{".02.2021"};
    QString incorrectDate7{"1.12.2021"};
    QString incorrectDate8{"02.4.2021"};
    QString incorrectDate9{"123.233.20212"};
    QString incorrectDate10{"01.03.1111"};
    QVERIFY(tm->checkDate(correctDate1));
    QVERIFY(tm->checkDate(correctDate2));
    QVERIFY(tm->checkDate(correctDate3));
    QVERIFY(!tm->checkDate(incorrectDate1));
    QVERIFY(!tm->checkDate(incorrectDate2));
    QVERIFY(!tm->checkDate(incorrectDate3));
    QVERIFY(!tm->checkDate(incorrectDate4));
    QVERIFY(!tm->checkDate(incorrectDate5));
    QVERIFY(!tm->checkDate(incorrectDate6));
    QVERIFY(!tm->checkDate(incorrectDate7));
    QVERIFY(!tm->checkDate(incorrectDate8));
    QVERIFY(!tm->checkDate(incorrectDate9));
    QVERIFY(!tm->checkDate(incorrectDate10));
}

void datatable_ut::parse_string_test_case()
{
    QString str{"To do homework 22.03.2006 3"};
    QStringList entry = tm->parseEntry(str);
    QVERIFY2(entry.size() == 3, "Correct entry size");
    QCOMPARE(entry[0], "To do homework");
    QCOMPARE(entry[1], "22.03.2006");
    QCOMPARE(entry[2], "3");
}

void datatable_ut::create_datatable_benchmark()
{
    QBENCHMARK_ONCE
    {
        TableModel* td = new TableModel();
        delete td;
    }
}

QTEST_MAIN(datatable_ut)

#include "tst_datatable.moc"
