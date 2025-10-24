#include "../datastructures.h"
#include <iostream>
#include "test.h"
/*
struct module* make_module(std::string name);
struct function* make_function(std::string name);
struct basic_block* make_bb(std::string name);
*/

int main() {
    module* mod = make_module("TestModule");

    // Create a function with 3 basic blocks
    function* func1 = make_function("Func1");

    basic_block* bb1 = make_bb("BB1");
    basic_block* bb2 = make_bb("BB2");

    // Safely insert blocks, catching runtime errors
    try {
        func1->insert_bb(bb1, 1); // entry
        func1->insert_bb(bb2, 1);
    } catch (const std::runtime_error& e) {
        std::cerr << "xception while inserting basic block: " << e.what() << "\n";
        func1->insert_bb(bb2, 0);
    }

    mod->insert_func(func1);

    // Add successors — safely, to test tag uniqueness
    try {
        bb1->add_sucessor(bb2, "if_true");
        bb1->add_sucessor(bb2, "if_true"); // duplicate tag, throws
    } catch (const std::runtime_error& e) {
        std::cerr << "xception while adding successor: " << e.what() << "\n";
        bb1->add_sucessor(bb2, "if_false"); // duplicate tag, throws
    }

    // Print the module structure
    print_module(mod);

    // Graphviz-style visualization output for the function
    std::cout << "\n--- Graphviz Visualization ---\n";
    func1->visualize();

    

    std::cout << "\nRemoving tag 'if_true' from BB1...\n";
    bb1->remove_sucessor("if_true");

    std::cout << "\nAfter removing a successor:\n";
    func1->visualize();

delete mod;

    return 0;
}
