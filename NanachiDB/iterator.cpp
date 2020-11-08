#include "iterator.h"

namespace Nanachidb
{

Iterator::Iterator(Slot** table_, size_t capacity_):table(table_), capacity(capacity_), bucket_index(0), slot_pointer(nullptr) {}
    
void Iterator::SeekToFirst() {
    for(bucket_index = 0; bucket_index < capacity; ++bucket_index) {
        if(table[bucket_index] != nullptr) {
            slot_pointer = table[bucket_index];
            break;
        }
    }
}

void Iterator::Next() {
    if(slot_pointer->next != nullptr) {
        slot_pointer = slot_pointer->next;
    }
    else {
        for(; bucket_index < capacity; ++bucket_index) {
            if(table[bucket_index] != nullptr) {
                slot_pointer = table[bucket_index];
                break;
            }
        }
    }

    if(bucket_index == capacity)
        slot_pointer = nullptr;
}

bool Iterator::Valide() {
    return slot_pointer != nullptr;
}

Slice& Iterator::key() {
    return slot_pointer->key;
}

Slice& Iterator::value() {
    return slot_pointer->value;
}

} // namespace Nanachidb



