#include <iostream>
#include <string>
#include <map>
using namespace std;

/*
==============================================================
MEMENTO PATTERN - DATABASE TRANSACTION ROLLBACK
==============================================================

GOAL:
Database changes ko temporary apply karo.

If success:
COMMIT

If failure:
ROLLBACK to old snapshot

This is exactly Memento.
*/


// ==========================================================
// 1) MEMENTO
// ==========================================================

/*
This stores DATABASE SNAPSHOT.

IMPORTANT:
Ye sirf saved state hold karta hai.
*/
class DatabaseMemento {
private:
    map<string, string> data;

public:
    /*
    Snapshot creation
    Full DB copy stored
    */
    DatabaseMemento(const map<string, string>& dbData) {
        this->data = dbData;
    }

    /*
    Snapshot restore ke time state return karega
    */
    map<string, string> getState() const {
        return data;
    }
};


// ==========================================================
// 2) ORIGINATOR
// ==========================================================

/*
This is actual database.

Iska live state change hota hai.
*/
class Database {
private:
    map<string, string> records;

public:
    void insert(const string& key, const string& value) {
        records[key] = value;
        cout << "Inserted: " << key
             << " = " << value << endl;
    }

    void update(const string& key, const string& value) {
        if (records.find(key) != records.end()) {
            records[key] = value;
            cout << "Updated: " << key
                 << " = " << value << endl;
        }
    }

    void remove(const string& key) {
        auto it = records.find(key);
        if (it != records.end()) {
            records.erase(it);
            cout << "Deleted: " << key << endl;
        }
    }

    /*
    CREATE SNAPSHOT
    ----------------
    Current DB ka full backup
    */
    DatabaseMemento* createMemento() {
        cout << "Creating database backup...\n";
        return new DatabaseMemento(records);
    }

    /*
    RESTORE SNAPSHOT
    ----------------
    rollback ke time pura state replace
    */
    void restoreFromMemento(
        const DatabaseMemento& memento) {

        records = memento.getState();

        cout << "Database restored from backup!\n";
    }

    void displayRecords() {
        cout << "\n--- Current Database State ---\n";

        if (records.empty()) {
            cout << "Database empty\n";
        }

        for (auto& record : records) {
            cout << record.first
                 << " = "
                 << record.second
                 << endl;
        }

        cout << "------------------------------\n";
    }
};


// ==========================================================
// 3) CARETAKER
// ==========================================================

/*
Transaction manager backup ko manage karta hai.

Important:
It NEVER changes snapshot internals.
Just stores and restores.
*/
class TransactionManager {
private:
    DatabaseMemento* backup;

public:
    TransactionManager() {
        backup = nullptr;
    }

    ~TransactionManager() {
        delete backup;
    }

    /*
    TRANSACTION START
    -----------------
    save current DB state
    */
    void beginTransaction(Database& db) {
        cout << "=== BEGIN TRANSACTION ===\n";

        delete backup;
        backup = db.createMemento();
    }

    /*
    SUCCESS CASE
    ----------------
    backup no longer needed
    */
    void commitTransaction() {
        cout << "=== COMMIT TRANSACTION ===\n";

        delete backup;
        backup = nullptr;

        cout << "Committed successfully!\n";
    }

    /*
    FAILURE CASE
    ----------------
    restore old snapshot
    */
    void rollbackTransaction(Database& db) {
        cout << "=== ROLLBACK TRANSACTION ===\n";

        if (backup) {
            db.restoreFromMemento(*backup);

            delete backup;
            backup = nullptr;

            cout << "Rollback done!\n";
        }
    }
};


// ==========================================================
// 4) CLIENT FLOW
// ==========================================================
int main() {
    Database db;
    TransactionManager txManager;

    /*
    SUCCESS TRANSACTION
    */
    txManager.beginTransaction(db);

    db.insert("user1", "Aditya");
    db.insert("user2", "Rohit");

    txManager.commitTransaction();

    db.displayRecords();

    /*
    FAILED TRANSACTION
    */
    txManager.beginTransaction(db);

    db.insert("user3", "Saurav");
    db.insert("user4", "Manish");

    db.displayRecords();

    cout << "ERROR happened!\n";

    /*
    rollback to previous snapshot
    */
    txManager.rollbackTransaction(db);

    db.displayRecords();

    return 0;
}