#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QThread>
#include "reader.h"
#include "writer.h"
#include <memory>
thread_local QSqlDatabase baseCon;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    baseCon = QSqlDatabase::addDatabase("QSQLITE", "main");
    baseCon.setDatabaseName("base.db");
    if (!baseCon.open()) {
        return a.exec();
    }

    QSqlQuery query(baseCon);
    query.exec("CREATE TABLE IF NOT EXISTS test_table(id integer);");

    std::unique_ptr<QThread> readerThread1 = std::make_unique<QThread>();
    std::unique_ptr<QThread> readerThread2 = std::make_unique<QThread>();
    std::unique_ptr<QThread> writerThread1 = std::make_unique<QThread>();
    std::unique_ptr<QThread> writerThread2 = std::make_unique<QThread>();

    std::unique_ptr<Reader> reader1 = std::make_unique<Reader>();
    reader1->moveToThread(readerThread1.get());
    QObject::connect(readerThread1.get(), SIGNAL(started()), reader1.get(), SLOT(start()));

    std::unique_ptr<Reader> reader2 = std::make_unique<Reader>();
    reader2->moveToThread(readerThread2.get());
    QObject::connect(readerThread2.get(), SIGNAL(started()), reader2.get(), SLOT(start()));

    std::unique_ptr<Writer> writer1 = std::make_unique<Writer>();
    writer1->moveToThread(writerThread1.get());
    QObject::connect(writerThread1.get(), SIGNAL(started()), writer1.get(), SLOT(start()));

    std::unique_ptr<Writer> writer2 = std::make_unique<Writer>();
    writer2->moveToThread(writerThread2.get());
    QObject::connect(writerThread2.get(), SIGNAL(started()), writer2.get(), SLOT(start()));

    readerThread1->start();
    readerThread2->start();
    writerThread1->start();
    writerThread2->start();

    return a.exec();
}
