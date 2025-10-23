#include "datastructures.h"

struct module* make_module(std::string name){
       struct module *newmodule = new struct module;
       newmodule->name = name;
       return newmodule;
}

struct function* make_function(std::string name){
       struct function *newfunc = new struct function;
       newfunc->name = name;
       return newfunc;
}

struct basic_block* make_bb(std::string name){
       struct basic_block *newbb= new struct basic_block;
       newbb->name = name;
       return newbb;
}
