#include <string>
#include <unordered_map>
#include <iostream>
using namespace std;

class inmemoryDB {
    unordered_map<string, int> database;
    unordered_map<string, int> committed;
    bool inProgress;
public:
    inmemoryDB();
    int get(string key);
    void put(string key, int val);
    void begin_transaction();
    void commit();
    void rollback();
};

inmemoryDB::inmemoryDB() {
    inProgress = false;
}

int inmemoryDB::get(string key) {
    if (database.count(key) == 1) {
        cout << key << ": " << database[key] << endl;
        return database[key];
    }
    else {
        cout << "Key: " << key << " does not exist in database" << endl;
        return -1;
    }
}

void inmemoryDB::put(string key, int val) {
    try {
        if (inProgress) {
            committed[key] = val;
            cout << "Put value" << endl;
        }
        else {
            throw inProgress;
        }
    }
    catch (...) {
        cout << "No transaction in progress" << endl;
        exit(0);
    }
}

void inmemoryDB::begin_transaction() {
    try {
        if (!inProgress) {
            inProgress = true;
            cout << "Started transaction" << endl;
        }
        else {
            throw inProgress;
        }
    }
    catch (...) {
        cout << "Transaction already in progress" << endl;
        exit(0);
    }
}

void inmemoryDB::commit() {
    try {
        if (inProgress) {
            inProgress = false;
            for (auto transaction : committed) {
                database[transaction.first] = transaction.second;
            }
            cout << "Comitted changes and ended transaction" << endl;
        }
        else {
            throw inProgress;
        }
    }
    catch (...) {
        cout << "No transaction in progress" << endl;
        exit(0);
    }
}

void inmemoryDB::rollback() {
    try {
        if (inProgress) {
            inProgress = false;
            committed.clear();
            cout << "Rolledback changes and ended transaction" << endl;
        }
        else {
            throw inProgress;
        }
    }
    catch (...) {
        cout << "No transaction in progress" << endl;
        exit(0);
    }
}