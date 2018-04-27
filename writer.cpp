#include "writer.h"
extern thread_local QSqlDatabase baseCon;

Writer::Writer(QObject *parent) : QObject(parent)
{

}

void Writer::start()
{
    qDebug() << __PRETTY_FUNCTION__ << "writer" << thread();
    baseCon = QSqlDatabase::addDatabase("QSQLITE", QString("writer%1").arg(QString::number((long long)QThread::currentThread(), 16)));

    baseCon.setDatabaseName("base.db");
    if (!baseCon.open()) {
        return;
    }

    forever {
        QSqlQuery query(baseCon);
        if(!query.exec("INSERT INTO test_table VALUES(1);")) {
            throw(std::logic_error(QString(__PRETTY_FUNCTION__ + query.lastError().text()).toStdString()));
            qDebug() << __PRETTY_FUNCTION__ << query.lastError().text();
            break;
        }
//        thread()->msleep(100);
    }
}
