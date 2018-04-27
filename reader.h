#ifndef READER_H
#define READER_H

#include <QObject>
#include <QSqlDatabase>
#include <QThread>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

class Reader : public QObject
{
    Q_OBJECT
public:
    explicit Reader(QObject *parent = 0);

signals:

public slots:
    void start();
};

#endif // READER_H
