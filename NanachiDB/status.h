#ifndef NANACHIDB_STATUS_H
#define NANACHIDB_STATUS_H

namespace Nanachidb
{

enum class Status{
    OK,
    OUT_OF_MEMOERY,
    ILLEGAL_ADDRESS,
    INVALID,
    FATAL,
};

} // namespace Nanachidb



#endif