#ifndef NANACHIDB_DATABASE_H
#define NANACHIDB_DATABASE_H

#include "iterator.h"
#include "memtable.h"
#include "slice.h"
#include "status.h"

#include <string>

namespace Nanachidb
{

struct DBOptions
{
    size_t mem_table_capacity;
    DBOptions(size_t mem_capacity): mem_table_capacity(mem_capacity) {}
};


class DB{
private:
    std::string db_name_;
    MemTable* mem_table;

public:
    DB(std::string &db_name, DBOptions &option);
    ~DB();

    static Status Open(const std::string &db_name, const DB** db_ptr);

    Status Delete(Slice &key);
    Status Get(Slice &key, std::string* value);
    Status Put(Slice &key, Slice &value);
    Iterator* NewIterator();
};

} // namespace Nanachidb

#endif