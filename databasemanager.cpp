#include "DatabaseManager.h"
#include <QSqlError>
#include <QDebug>
#include <QSqlRecord>
#include <QStandardPaths>
#include <QDir>
DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent)
{
    QString dbPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/My Lists/data";
    QDir dir(dbPath);

    if (!dir.exists()) {
        if (!dir.mkpath(dbPath)) {
            qDebug() << "Error: Unable to create database directory!" << dbPath;
            return;
        }
    }

    dbPath += "/database.db";
    qDebug() << "Database path:" << dbPath;

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(dbPath);

    if (!m_db.open()) {
        qDebug() << "Error: Unable to connect to database!" << m_db.lastError();
    } else {
        createTables();
    }
}

DatabaseManager::~DatabaseManager()
{
    if (m_db.isOpen()) {
        m_db.close();
    }
}

void DatabaseManager::createTables()
{
    QSqlQuery query;

    // Create List table
    query.exec("CREATE TABLE IF NOT EXISTS List ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "name TEXT,"
               "description TEXT)");

    // Create Task table with 'ord' instead of 'order'
    query.exec("CREATE TABLE IF NOT EXISTS Task ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "name TEXT,"
               "listId INTEGER,"
               "ord INTEGER,"
               "finished BOOLEAN,"
               "FOREIGN KEY (listId) REFERENCES List(id))");
}

bool DatabaseManager::addList(const QString &name, const QString &description)
{
    QSqlQuery query;
    query.prepare("INSERT INTO List (name, description) VALUES (:name, :description)");
    query.bindValue(":name", name);
    query.bindValue(":description", description);
    return query.exec();
}

bool DatabaseManager::addTask(const QString &name, int listId)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Task (name, listId, ord, finished) "
                  "VALUES (:name, :listId, "
                  "(SELECT IFNULL(MAX(ord), 0) + 1 FROM Task WHERE listId = :listId), false)");
    query.bindValue(":name", name);
    query.bindValue(":listId", listId);
    return query.exec();
}
QVariantList DatabaseManager::getAllLists()
{
    QVariantList listData;
    QSqlQuery query(
        "SELECT List.id, List.name, List.description, "
        "(SELECT COUNT(*) FROM Task WHERE Task.listId = List.id) AS taskcount, "
        "(SELECT COUNT(*) FROM Task WHERE Task.listId = List.id AND Task.finished = 0) AS unfinishedtaskcount "
        "FROM List ORDER BY List.id");

    while (query.next()) {
        QVariantMap list;
        list["id"] = query.value("id");
        list["name"] = query.value("name");
        list["description"] = query.value("description");
        list["taskcount"] = query.value("taskcount");
        list["unfinishedtaskcount"] = query.value("unfinishedtaskcount");
        listData.append(list);
    }

    return listData;
}

QVariantList DatabaseManager::getAllTasks(int listId)
{
    QVariantList taskData;
    QSqlQuery query;
    query.prepare("SELECT id, name, listId, ord, finished FROM Task WHERE listId = :listId ORDER BY ord");
    query.bindValue(":listId", listId);
    query.exec();

    while (query.next()) {
        QVariantMap task;
        task["id"] = query.value("id");
        task["name"] = query.value("name");
        task["listId"] = query.value("listId");
        task["ord"] = query.value("ord");
        task["finished"] = query.value("finished");
        taskData.append(task);
    }

    return taskData;
}

bool DatabaseManager::editList(int id, const QString &name, const QString &description)
{
    QSqlQuery query;
    query.prepare("UPDATE List SET name = :name, description = :description WHERE id = :id");
    query.bindValue(":name", name);
    query.bindValue(":description", description);
    query.bindValue(":id", id);
    return query.exec();
}
bool DatabaseManager::editTask(int id, const QString &name)
{
    QSqlQuery query;
    query.prepare("UPDATE Task SET name = :name WHERE id = :id");
    query.bindValue(":name", name);
    query.bindValue(":id", id);
    return query.exec();
}
bool DatabaseManager::deleteTask(int id, int listid)
{
    // Start a transaction
    QSqlDatabase::database().transaction();

    // Get the ord of the task to be deleted
    QSqlQuery query2;
    query2.prepare("SELECT ord FROM Task WHERE id = :id");
    query2.bindValue(":id", id);
    if (!query2.exec() || !query2.next()) {
        QSqlDatabase::database().rollback();
        return false;
    }
    int ord = query2.value(0).toInt();

    // Delete the task
    QSqlQuery query;
    query.prepare("DELETE FROM Task WHERE id = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        QSqlDatabase::database().rollback();
        return false;
    }

    // Update the ord fields of the remaining tasks
    QSqlQuery query1;
    query1.prepare("UPDATE Task SET ord = ord - 1 WHERE listId = :listid AND ord > :ord");
    query1.bindValue(":listid", listid);
    query1.bindValue(":ord", ord);
    if (!query1.exec()) {
        QSqlDatabase::database().rollback();
        return false;
    }

    // Commit the transaction
    return QSqlDatabase::database().commit();
}

bool DatabaseManager::deleteList(int id)
{
    QSqlDatabase::database().transaction();
    QSqlQuery query;
    query.prepare("DELETE FROM List WHERE id = :id");
    query.bindValue(":id", id);
    if(!query.exec()) {
        QSqlDatabase::database().rollback();
        return false;
    }

    QSqlQuery query1;
    query1.prepare("DELETE FROM Task WHERE listId = :id");
    query1.bindValue(":id", id);
    if(!query1.exec()) {
        QSqlDatabase::database().rollback();
        return false;
    }
    return QSqlDatabase::database().commit();

}

void DatabaseManager::replace(int listId, int srcOrd, int destOrd)
{
    QSqlQuery query;

    if (!m_db.transaction()) {
        qDebug() << "Transaction start error:" << m_db.lastError();
        return;
    }
    srcOrd++;
    destOrd++;
    qDebug()<<listId<<srcOrd;
    // Ensure the source task exists and get its id
    query.prepare("SELECT * FROM Task WHERE listId = :listId AND ord = :srcOrd");
    query.bindValue(":listId", listId);
    query.bindValue(":srcOrd", srcOrd);
    if (!query.exec()) {
        qDebug() << "Query error:" << query.lastError();
        m_db.rollback();
        return;
    }

    if (!query.next()) {
        qDebug() << "Source task not found!";
        m_db.rollback();
        return;
    }
    int srcId = query.value("id").toInt();

    // Update source task to a temporary ord value
    query.prepare("UPDATE Task SET ord = -1 WHERE id = :srcId");
    query.bindValue(":srcId", srcId);
    if (!query.exec()) {
        qDebug() << "Query error:" << query.lastError();
        m_db.rollback();
        return;
    }

    // Update ord of tasks between srcOrd and destOrd
    if (srcOrd < destOrd) {
        // Move tasks between srcOrd and destOrd down by 1
        query.prepare("UPDATE Task SET ord = ord - 1 WHERE listId = :listId AND ord > :srcOrd AND ord <= :destOrd");
        query.bindValue(":listId", listId);
        query.bindValue(":srcOrd", srcOrd);
        query.bindValue(":destOrd", destOrd);
        if (!query.exec()) {
            qDebug() << "Query error:" << query.lastError();
            m_db.rollback();
            return;
        }
    } else {
        // Move tasks between destOrd and srcOrd up by 1
        query.prepare("UPDATE Task SET ord = ord + 1 WHERE listId = :listId AND ord >= :destOrd AND ord < :srcOrd");
        query.bindValue(":listId", listId);
        query.bindValue(":srcOrd", srcOrd);
        query.bindValue(":destOrd", destOrd);
        if (!query.exec()) {
            qDebug() << "Query error:" << query.lastError();
            m_db.rollback();
            return;
        }
    }

    // Set the new ord for the source task
    query.prepare("UPDATE Task SET ord = :destOrd WHERE id = :srcId");
    query.bindValue(":destOrd", destOrd);
    query.bindValue(":srcId", srcId);
    if (!query.exec()) {
        qDebug() << "Query error:" << query.lastError();
        m_db.rollback();
        return;
    }

    if (!m_db.commit()) {
        qDebug() << "Transaction commit error:" << m_db.lastError();
        m_db.rollback();
    }
}

bool DatabaseManager::checkTask(int id, bool finished, int listid)
{
    // Start a transaction
    if (!m_db.transaction()) {
        qDebug() << "Transaction start error:" << m_db.lastError();
        return false;
    }

    if (finished) {
        // If marking as finished, set order to 0 and update the order of remaining tasks
        QSqlQuery query2;
        query2.prepare("SELECT ord FROM Task WHERE id = :id");
        query2.bindValue(":id", id);
        if (!query2.exec() || !query2.next()) {
            qDebug() << "Query error or task not found:" << query2.lastError();
            m_db.rollback();
            return false;
        }
        int order = query2.value(0).toInt();

        // Update the ord fields of the remaining tasks
        QSqlQuery query1;
        query1.prepare("UPDATE Task SET ord = ord - 1 WHERE listId = :listid AND ord > :order");
        query1.bindValue(":order", order);
        query1.bindValue(":listid", listid);
        if (!query1.exec()) {
            qDebug() << "Query error:" << query1.lastError();
            m_db.rollback();
            return false;
        }

        // Set the ord to 0 and mark as finished
        QSqlQuery query;
        query.prepare("UPDATE Task SET finished = :finished, ord = 0 WHERE id = :id");
        query.bindValue(":finished", finished);
        query.bindValue(":id", id);
        if (!query.exec()) {
            qDebug() << "Query error:" << query.lastError();
            m_db.rollback();
            return false;
        }
    } else {
        // If marking as unfinished, set order to the last and mark as unfinished
        QSqlQuery query;
        query.prepare("UPDATE Task SET finished = :finished, ord = (SELECT IFNULL(MAX(ord), 0) + 1 FROM Task WHERE listId = :listid) WHERE id = :id");
        query.bindValue(":finished", finished);
        query.bindValue(":id", id);
        query.bindValue(":listid", listid);
        if (!query.exec()) {
            qDebug() << "Query error:" << query.lastError();
            m_db.rollback();
            return false;
        }
    }

    // Commit the transaction
    if (!m_db.commit()) {
        qDebug() << "Transaction commit error:" << m_db.lastError();
        m_db.rollback();
        return false;
    }

    return true;
}

QVariantMap DatabaseManager::getList(int id)
{
    QSqlQuery query;
    query.prepare(
        "SELECT id, name, description "
        "FROM List "
        "WHERE id=:id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qWarning() << "Failed to execute query:" << query.lastError().text();
        return QVariantMap(); // Return an empty map in case of error
    }

    QVariantMap result;
    if (query.next()) {
        result["id"] = query.value("id");
        result["name"] = query.value("name");
        result["description"] = query.value("description");
    } else {
        qWarning() << "No results found for id" << id;
    }

    return result;
}
QVariantList DatabaseManager::getAllFLists()
{
    QVariantList listData;
    QSqlQuery query(
        "SELECT List.id, List.name, List.description, "
        "(SELECT COUNT(*) FROM Task WHERE Task.listId = List.id) AS taskcount, "
        "(SELECT COUNT(*) FROM Task WHERE Task.listId = List.id AND Task.finished = 0) AS unfinishedtaskcount "
        "FROM List "
        "WHERE unfinishedtaskcount = 0 AND taskcount > 0 "
        "ORDER BY List.id");

    while (query.next()) {
        QVariantMap list;
        list["id"] = query.value("id");
        list["name"] = query.value("name");
        list["description"] = query.value("description");
        list["taskcount"] = query.value("taskcount");
        list["unfinishedtaskcount"] = query.value("unfinishedtaskcount");
        listData.append(list);
    }

    return listData;
}
QVariantList DatabaseManager::getAllULists()
{
    QVariantList listData;
    QSqlQuery query(
        "SELECT List.id, List.name, List.description, "
        "(SELECT COUNT(*) FROM Task WHERE Task.listId = List.id) AS taskcount, "
        "(SELECT COUNT(*) FROM Task WHERE Task.listId = List.id AND Task.finished = 0) AS unfinishedtaskcount "
        "FROM List "
        "WHERE unfinishedtaskcount > 0 OR taskcount = 0 "
        "ORDER BY List.id");

    while (query.next()) {
        QVariantMap list;
        list["id"] = query.value("id");
        list["name"] = query.value("name");
        list["description"] = query.value("description");
        list["taskcount"] = query.value("taskcount");
        list["unfinishedtaskcount"] = query.value("unfinishedtaskcount");
        listData.append(list);
    }

    return listData;
}
QVariantList DatabaseManager::getAllUTasks(int listId)
{
    QVariantList taskData;
    QSqlQuery query;
    query.prepare("SELECT id, name, listId, ord, finished FROM Task WHERE listId = :listId AND finished = 0 ORDER BY ord");
    query.bindValue(":listId", listId);
    query.exec();

    while (query.next()) {
        QVariantMap task;
        task["id"] = query.value("id");
        task["name"] = query.value("name");
        task["listId"] = query.value("listId");
        task["ord"] = query.value("ord");
        task["finished"] = query.value("finished");
        taskData.append(task);
    }

    return taskData;
}
QVariantList DatabaseManager::getAllFTasks(int listId)
{
    QVariantList taskData;
    QSqlQuery query;
    query.prepare("SELECT id, name, listId, ord, finished FROM Task WHERE listId = :listId AND finished = 1 ORDER by id");
    query.bindValue(":listId", listId);
    query.exec();

    while (query.next()) {
        QVariantMap task;
        task["id"] = query.value("id");
        task["name"] = query.value("name");
        task["listId"] = query.value("listId");
        task["ord"] = query.value("ord");
        task["finished"] = query.value("finished");
        taskData.append(task);
    }

    return taskData;
}


