#ifndef NANACHIDB_ITERATOR_H
#define NANACHIDB_ITERATOR_H

#include "slice.h"
#include "memtable.h"

namespace Nanachidb
{

struct Slot;


// I'm not going to implment an abstarct iterator class, but a hash iterator.
class Iterator {
private:
    Slot** table;
    size_t capacity;
    size_t bucket_index;
    Slot* slot_pointer;
public:
    Iterator(Slot** table, size_t capacity);
    void SeekToFirst();
    void Next();
    bool Valide();
    Slice& key();
    Slice& value();
};
    
} // namespace Nanachidb


#endif