#include "database.h"



namespace Nanachidb
{

DB::DB(std::string &db_name, DBOptions &options): db_name_(db_name) {
    MemTableOptions mem_option{options.mem_table_capacity};
    mem_table = new MemTable(mem_option);
}

DB::~DB() {}

Status DB::Open(const std::string &db_name, const DB** db_ptr) {

}

Status DB::Delete(Slice &key) {
    return mem_table->Delete(key);
}

Status DB::Get(Slice &key, std::string* value) {
    Slice* svalue;
    auto state = mem_table->Get(key, svalue);
    *value = svalue->ToString();
    return state;
}

Status DB::Put(Slice &key, Slice &value) {
    return mem_table->Insert(key, value);
}

Iterator* DB::NewIterator() {
    return mem_table->NewIterator();
}

} // namespace Nanachidb
