#ifndef __SYMBOL_H__
#define __SYMBOL_H__

#include <memory>
#include <stdint.h>

struct Symbol {
    uint32_t id;
    char name[8];

    Symbol(uint32_t symbol_id, const char symbol_name[8])
        : id(symbol_id) {
        memcpy(name, symbol_name, sizeof(name));
    }
};

#endif //!__SYMBOL_H__
