#include <iostream>
#include "slice.h"
#include "memtable.h"
#include "database.h"
using namespace std;

void test_slice() {
    char s[] = "Welcome to Nanachi's database!";
    char t[] = "Be quite...";
    Nanachidb::Slice ss(s);
    Nanachidb::Slice st(t);
    cout << "size: " << ss.size() << endl;
    cout << "data: " << ss.data() << endl;
    cout << "Empty? " << ss.empty() << endl;
    cout << "Start with Be? " << ss.starts_with(st) << endl;
    cout << "String format: " << ss.ToString() << endl;
    cout << ss.compare(st) << endl;
}

void test_memtable() {
    Nanachidb::MemTableOptions memoption{1000};
    Nanachidb::MemTable table(memoption);
    
    char s[] = "Welcome to Nanachi's database!";
    char t[] = "Be quite...";
    Nanachidb::Slice ss(s);
    Nanachidb::Slice st(t);

    cout << "Insert slice..." << endl;
    table.Insert(ss, st);
    cout << "Is empty? " << table.empty() << endl;

    table.Insert(st, ss);

    auto res = table[st];
    cout << "Found data is " << res.data() << "." << endl;
    cout << "Remove data: " << (Nanachidb::Status::OK == table.Delete(st)) << endl;
}

void test_db() {
    Nanachidb::DBOptions option{1000};
    std::string name = "mydb";
    Nanachidb::DB db(name, option);

    char s[] = "Welcome to Nanachi's database!";
    char t[] = "Be quite...";
    Nanachidb::Slice ss(s);
    Nanachidb::Slice st(t);

    db.Put(ss, st);
    db.Delete(ss);
}

int main() {
    // test_slice();
    // test_memtable();
    test_db();
    return 0;
}