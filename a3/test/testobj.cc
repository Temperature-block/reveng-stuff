#include <iostream>
#include <string>
#include <vector>
#include "../datastructures.h"

void print_module(const module* mod) {

    std::cout << "Module: " << mod->name << "\n";

    for (const function* f : mod->funcs) {
        std::cout << " Function: " << f->name;
        if (f->entry) {
            std::cout << " (Entry: " << f->entry->name << ")";
        }
        std::cout << "\n";

        for (const basic_block* b : f->bb) {
            std::cout << "  Basic Block: " << b->name;
            if (f->entry == b) std::cout << " [Entry]";
            std::cout << "\n";
        }
    }
}
