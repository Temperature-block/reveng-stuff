#include <vector>

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
  std::vector<struct basic_block*> entryblocks;

  void insert_bb(struct basic_block* block){
       bb.push_back(block);
  }

  void remove_by_name(string name){
       int iter = 0;
       for(struct basic_block* blockit:bb){
         ++iter;
         if(blockit->name == name){
           funcs.erase(iter);
           /* should we return copy */
         }
       }
  }
};

/*we represent module as a list of functions a module simply has a name */
struct module{
public:
  std::string name;
  std::vector<struct function*> funcs;

  void insert_func(struct func* function){
       funcs.push_back(function);
       }

  /* we assume each function has a unique name we are yet to add logic to handle unique name checking */
  void remove_by_name(string name){
       int iter = 0;
       for(struct function funcit:funcs){
         ++iter;
         if(funcit.name == name){
           funcs.erase(iter);
           /* should we return copy */
         }
       }
  }
};


struct module* make_module(string name);
struct function* make_function(string name);
struct basic_block* make_bb(string name);
