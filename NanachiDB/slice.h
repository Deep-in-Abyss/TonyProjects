#ifndef NANACHIDB_SLICE_H
#define NANACHIDB_SLICE_H

#include <cstddef>
#include <string>

namespace Nanachidb
{

class Slice{
private:
    const char* data_;
    std::size_t size_;
public:
    Slice(const char* data, std::size_t n);
    Slice(const std::string &s);
    Slice(const char* data);
    Slice(const Slice&) = default;

    Slice& operator=(const Slice&) = default;
    char operator[](std::size_t n) const;

    void clear();
    int compare(const Slice &x) const;
    const char* data();
    bool empty() const;
    void remove_prefix(std::size_t n);
    std::size_t size();
    bool starts_with(const Slice &x) const;
    std::string ToString() const;
};

} // namespace Nanachidb



#endif