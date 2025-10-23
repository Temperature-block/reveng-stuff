#ifndef __dtst__
#define __dtst__
#include <vector>
#include <string>
#include <stdexcept>

struct basic_block {
public:
 std::string name;
 /* todo */
};

/*module has list of functions and a functions and function has basic blocks */
struct function{
public:
  std::string name;
  /*should there be tag list? from the looks of assignment 2? to do later */
  std::vector<struct basic_block*> bb;
  struct basic_block* entry = NULL;
  void insert_bb(struct basic_block* block,int mark_entry){
       if(mark_entry){
          if(entry){
            throw std::runtime_error("There must only be one entry block");
          }
          else{
            entry = block;
          }
       }
       bb.push_back(block);
  }

  void remove_by_name(std::string name){
       int iter = 0;
       for(struct basic_block* blockit:bb){
         if(blockit->name == name){
           bb.erase(bb.begin()+iter);
           return;
           /* should we return copy */
         }
      ++iter;
       }
  }
  ~function(){
   for(struct basic_block* blockit:bb){
    delete blockit;
   }
  }
};

/*we represent module as a list of functions a module simply has a name */
struct module{
public:
  std::string name;
  std::vector<struct function*> funcs;

  void insert_func(struct function* func){
       funcs.push_back(func);
       }

  /* we assume each function has a unique name we are yet to add logic to handle unique name checking */
  void remove_by_name(std::string name){
       int iter = 0;
       for(struct function* funcit:funcs){
         if(funcit->name == name){
           funcs.erase(funcs.begin()+iter);
           return;
           /* should we return copy */
         }
      ++iter;
       }
  }

 ~module(){
   for(struct function* funcit:funcs){
   delete funcit;
   }
  }
};


struct module* make_module(std::string name);
struct function* make_function(std::string name);
struct basic_block* make_bb(std::string name);

#endif
