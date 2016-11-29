#include "mainwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

DbManager::DbManager(const QString &path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
    {
        qDebug() << "Error: connection with database failed";
    }
    else
    {
        qDebug() << "Database: connection ok";
    }
}

DbManager::~DbManager()
{
    if (m_db.isOpen())
    {
        m_db.close();
    }
}

bool DbManager::isOpen() const
{
    return m_db.isOpen();
}

bool DbManager::createTable()
{
    bool success = false;

    QSqlQuery query;
    query.prepare("CREATE TABLE ratings(name TEXT PRIMARY KEY, stars INTEGER);");

    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'ratings': one might already exist.";
        success = false;
    }
    else
        success = true;

    return success;
}

bool DbManager::addTrack(const QString& name, const int stars)
{
    bool success = false;
    if (!name.isEmpty())
    {
        QSqlQuery queryAdd;
        queryAdd.prepare("INSERT INTO ratings (name,stars) VALUES (:name, :stars)");
        queryAdd.bindValue(":name", name);
        queryAdd.bindValue(":stars", stars);

        if(queryAdd.exec())
        {
            success = true;
        }
        else
        {
            qDebug() << "add track failed: " << queryAdd.lastError();
        }
    }
    else
    {
        qDebug() << "add track failed: name cannot be empty";
    }

    return success;
}

bool DbManager::removeTrack(const QString& name)
{
    bool success = false;

    if (trackExists(name))
    {
        QSqlQuery queryDelete;
        queryDelete.prepare("DELETE FROM ratings WHERE name = (:name)");
        queryDelete.bindValue(":name", name);
        success = queryDelete.exec();

        if(!success)
        {
            qDebug() << "remove track failed: " << queryDelete.lastError();
        }
    }
    else
    {
        qDebug() << "remove track failed: track doesnt exist";
    }

    return success;
}

void DbManager::printAllTracks() const
{
    qDebug() << "Track in db:";
    QSqlQuery query("SELECT * FROM ratings");
    int idName = query.record().indexOf("name");
    while (query.next())
    {
        QString name = query.value(idName).toString();
        qDebug() << "===" << name;
    }
}

bool DbManager::trackExists(const QString& name) const
{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT name FROM ratings WHERE name = (:name)");
    checkQuery.bindValue(":name", name);

    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            exists = true;
        }
    }
    else
    {
        qDebug() << "track exists failed: " << checkQuery.lastError();
    }

    return exists;
}

bool DbManager::removeAllTracks()
{
    bool success = false;

    QSqlQuery removeQuery;
    removeQuery.prepare("DELETE FROM ratings");

    if (removeQuery.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "remove all tracks failed: " << removeQuery.lastError();
    }

    return success;
}
