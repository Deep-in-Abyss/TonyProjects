#include "slice.h"

#include <cassert>
#include <cstring>

namespace Nanachidb
{

Slice::Slice(const char* data, std::size_t n): data_(data), size_(n) {}

Slice::Slice(const std::string &s): data_(s.data()), size_(s.length()) {}

Slice::Slice(const char* data): data_(data), size_(strlen(data)) {}

char Slice::operator[](std::size_t n) const {
    assert(n < size_);
    return data_[n];
}

void Slice::clear() {
    data_ = "";
    size_ = 0;
}

int Slice::compare(const Slice &x) const {
    int res;
    if(size_ < x.size_) {
        res = memcmp(data_, x.data_, size_);
        if(res == 0) res = -1;
    }
    else if(size_ == x.size_) {
        res = memcmp(data_, x.data_, size_);
    }
    else {
        res = memcmp(data_, x.data_, x.size_);
        if(res == 0) res = 1;
    }
    return res;
}

const char* Slice::data() {
    return data_;
}

bool Slice::empty() const {
    return 0 == size_;
}

void Slice::remove_prefix(std::size_t n) {
    assert(n <= size());
    data_ += n;
    size_ -= n;
}

std::size_t Slice::size() {
    return size_;
}

bool Slice::starts_with(const Slice &x) const {
    return (x.size_ <= size_) and (memcmp(data_, x.data_, x.size_) == 0);
}

std::string Slice::ToString() const {
    return std::string(data_, size_);
}

} // namespace Nanachidb
