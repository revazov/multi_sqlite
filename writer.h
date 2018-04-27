#ifndef WRITER_H
#define WRITER_H

#include <QObject>
#include <QSqlDatabase>
#include <QThread>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

class Writer : public QObject
{
    Q_OBJECT
public:
    explicit Writer(QObject *parent = 0);

signals:

public slots:
    void start();
};

#endif // WRITER_H
