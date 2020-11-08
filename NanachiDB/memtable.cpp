#include "memtable.h"
#include "utils/hash.h"


namespace Nanachidb
{

MemTable::MemTable(MemTableOptions &options): capacity_(options.capacity_) {
    buckets_table_ = new Slot*[capacity_];

    for(auto i = 0; i < capacity_; ++i) buckets_table_[i] = nullptr; 
}

MemTable::~MemTable() {
    delete buckets_table_;
}

Status MemTable::Delete(Slice &key) {
    auto slotPtr = bucket_slot(key);
    auto previousPtr = slotPtr;

    while((*slotPtr) != nullptr) {
        if((*slotPtr)->key.compare(key) == 0) break;
        else {
            previousPtr = slotPtr;
            slotPtr = &(*slotPtr)->next;
        }
    }

    if((*previousPtr) == nullptr) return Status::INVALID;
    else {
        if(previousPtr == slotPtr) {
            // head element
            delete *slotPtr;
            slotPtr = nullptr;
        }
        else {
            (*previousPtr)->next = (*slotPtr)->next;
            delete slotPtr;
        }
    }
    --size_;
    return Status::OK;
}

Status MemTable::Insert(Slice &key, Slice &value) {
    auto slotPtr = bucket_slot(key);

    while((*slotPtr) != nullptr) 
        slotPtr = &(*slotPtr)->next;

    auto newSlot = new Slot(key, value);
    if(newSlot == nullptr) return Status::OUT_OF_MEMOERY;

    *slotPtr = newSlot;
    ++size_;
    return Status::OK;
}

Status MemTable::Get(Slice &key, Slice *value) {
    auto slotPtr = bucket_slot(key);

    while((*slotPtr) != nullptr) {
        if((*slotPtr)->key.compare(key) == 0) {
            value = &(*slotPtr)->value;
            break;
        }
        else {
            slotPtr = &(*slotPtr)->next;
        }
    }
    if((*slotPtr) == nullptr) return Status::INVALID;
    else return Status::OK;
}

bool MemTable::empty() const {
    return 0 == size();
}

std::size_t MemTable::size() const {
    return size_;
}

Slice MemTable::operator[](Slice &key) {
    auto slotPtr = bucket_slot(key);

    while((*slotPtr) != nullptr) {
        if((*slotPtr)->key.compare(key) == 0) {
            return (*slotPtr)->value;
        }
        else {
            slotPtr = &(*slotPtr)->next;
        }
    }

    Slice nil{""};
    return nil;
}

Slot** MemTable::bucket_slot(Slice &key) {
    auto bucketNum = Hash(key.data(), key.size(), 0) % capacity_;
    return &buckets_table_[bucketNum];
}

Iterator* MemTable::NewIterator() {
    auto it = new Iterator{buckets_table_, capacity_};
    return it;
}
    
} // namespace Nanachidb
