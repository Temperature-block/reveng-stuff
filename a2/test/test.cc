#include "../datastructures.h"
#include <iostream>
#include "test.h"
/*
struct module* make_module(std::string name);
struct function* make_function(std::string name);
struct basic_block* make_bb(std::string name);
*/

int main() {
    // Create a module
    module* mod = make_module("TestModule");

    // Create a function and its basic blocks
    function* func1 = make_function("Func1");
    basic_block* bb1 = make_bb("BB1");
    basic_block* bb2 = make_bb("BB2");

    func1->insert_bb(bb1, 1); // mark entry
    func1->insert_bb(bb2, 0);

    mod->insert_func(func1);

    // Another function
    function* func2 = make_function("Func2");
    basic_block* bb3 = make_bb("BB3");
    basic_block* bb4 = make_bb("BB4");
try {
    func2->insert_bb(bb3, 1); // first entry block
    func2->insert_bb(bb4, 1); // second entry -> throws
} catch (const std::runtime_error& e) {
    std::cerr << "Caught exception: " << e.what() << std::endl;
    // Continue execution
}
    mod->insert_func(func2);


    print_module(mod);
    // Remove a basic block by name
    func1->remove_by_name("BB2");
    print_module(mod);
    // Remove a function by name
    mod->remove_by_name("Func2");
    print_module(mod);
    // Cleanup
    delete mod;

    return 0;
}
