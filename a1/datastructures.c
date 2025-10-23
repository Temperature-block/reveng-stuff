#include "datastructures.h"

struct module* make_module(string name){
       struct module newmodule = new struct module;
       module->name = name;
       return newmodule
}

struct function* make_function(string name){
       struct function newfunc = new struct func;
       module->name = name;
       struct basic_block *bb =make_bb("entry")
       newfunc->insert_bb(bb);
       return newmodule
}

struct basic_block* make_bb(string name){
       struct basic_block newbb= new struct basic_block;
       newbb->name = name;
       return newbb;
}
