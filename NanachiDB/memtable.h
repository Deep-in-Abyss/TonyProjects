#ifndef NANACHI_MEMTABLE_H
#define NANACHI_MEMTABLE_H

#include "iterator.h"
#include "slice.h"
#include "status.h"

#include <cstddef>

namespace Nanachidb
{

class Iterator;

struct MemTableOptions
{
    std::size_t capacity_;
    MemTableOptions(std::size_t capacity): capacity_(capacity) {}
};

struct Slot
{
    Slice key;
    Slice value;
    Slot* next;
    Slot(Slice &key_, Slice &value_): key(key_), value(value_), next(nullptr) {}
};

    
class MemTable {
private:
    std::size_t capacity_;
    std::size_t size_;

    Slot** buckets_table_;

public:
    MemTable(MemTableOptions &options);
    ~MemTable();

    Status Delete(Slice &key);
    Status Insert(Slice &key, Slice &value);
    Status Get(Slice &key, Slice *value);

    bool empty() const;
    std::size_t size() const;
    Slice operator[](Slice &key);
    Iterator* NewIterator();
private:
    Slot** bucket_slot(Slice &key);
};

} // namespace Nanachidb



#endif