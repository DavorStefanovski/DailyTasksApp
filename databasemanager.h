#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QVariantList>

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = nullptr);
    ~DatabaseManager();

    void createTables();
    Q_INVOKABLE bool addList(const QString &name, const QString &description);
    Q_INVOKABLE bool addTask(const QString &name, int listId);
    Q_INVOKABLE QVariantList getAllLists();
    Q_INVOKABLE QVariantList getAllTasks(int listId);
    Q_INVOKABLE bool editList(int id, const QString &name, const QString &description);
    Q_INVOKABLE void replace(int listid, int src, int dest);
    Q_INVOKABLE bool checkTask(int id, bool finished, int listid);
    Q_INVOKABLE QVariantMap getList(int id);
    Q_INVOKABLE bool editTask(int id, const QString &name);
    Q_INVOKABLE bool deleteTask(int id, int listid);
    Q_INVOKABLE bool deleteList(int id);
    Q_INVOKABLE QVariantList getAllULists();
    Q_INVOKABLE QVariantList getAllFLists();
    Q_INVOKABLE QVariantList getAllUTasks(int listId);
    Q_INVOKABLE QVariantList getAllFTasks(int listId);
private:
    QSqlDatabase m_db;
};

#endif // DATABASEMANAGER_H
