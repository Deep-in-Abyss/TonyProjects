# NanachiDB
Nanachi collects many relics but confused to find the wanted one quickly. So Nanachi plans to build a key-value database to manage these objects.
## API
Luckily, Nanachi found a [design](http://codecapsule.com/2012/11/07/ikvs-implementing-a-key-value-store-table-of-contents/) from a maze, which describes a detailed APIs about a key-value database! The design shows as follows:
### Basic Functionalities
- Opening and closing a database
- Reading and writing data to a database
- Iterating over the full collection of keys and values in a database
- Offer a way to tune parameters
- Offer a decent error notification interface
#### Opening and closing a database
```c++
Nanachidb::DB* db;
Nanachidb::DB::Open("/db_path/db_name", &db, Nanachidb::Options);
delete db;
```
#### Reads and Writes
```c++
string value;
db->Get("key1", &value);
db->Put("key2", value);
```
#### Iteration
```c++
Nanachidb::Iterator* it = db->NewIterator();
for(it->SeekToFIrst(); it->Valide(); it->Next()){
    cout << it->key.ToString() << ": " << it->value().ToString() << endl;
}
delete it;
```
#### Parametrization
Temporarily, Nanachi is lazy to implement it.
#### Error Management
```c++
Nanachidb::Status s = db->Put("key", "value");
if(!s.ok()){
    cerr << s.ToString() << endl;
}
```