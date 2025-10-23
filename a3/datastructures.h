#ifndef __dtst__
#define __dtst__
#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>
#include <algorithm>

struct tag{
 std::string name;
 struct basic_block* block;
};

struct basic_block {
public:
 std::string name;
 /* each basic block has successors and each successors is identified by a tag*/
 /* tags are identified by their tag string */
 /* and each tag string needs to be unique*/
 /* otherway of saying at most one sucessor per tag */
 std::vector<struct tag*> successors;
 std::vector<std::string> sucnames;
 int check_uniq(std::string tagname){
     for(std::string tname:sucnames){
        if(tname == tagname){
           return 0;
          }
     }
     return 1;
 }
 void add_sucessor(struct basic_block* bb,std::string tagname){
      if(!check_uniq(tagname)){
         throw std::runtime_error("Tag name needs to be unique because each tag connect between two blocks a singular pathway");
      }
      struct tag *tagsmember = new struct tag;
      tagsmember->name = tagname;
      tagsmember->block = bb;
      successors.push_back(tagsmember);
 }

 void remove_sucessor(std::string tagname){
     int iter = 0;
     for(struct tag* tagn:successors){
      if(tagn->name == tagname){
         successors.erase(successors.begin()+iter);
         return;
         }
      ++iter;
     }
 }
  ~basic_block(){
   for(struct tag* tagn:successors){
    delete tagn;
   }
  }
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

  void visualize(){
  std::cout<<"digraph "<<name<<"\n";
  for(struct basic_block* blockit:bb){
     std::string current = blockit->name;
     for(struct tag* tagn:blockit->successors){
      std::cout<<current<<"->"<<tagn->block->name<<"[label="<<"\""<<tagn->name<<"\""<<";\n";
     }
   }
  }

 std::vector<int> traverse_bb(std::vector<int> vecc,struct basic_block* block){
    int iter=0,iter2=0;
       /* should make a template function for this loop */
    for(struct basic_block* blockit:bb){
           vecc[iter] = 1;
           break;
         ++iter;
      }
    iter = 0;

   for(struct tag* stag:block->successors){
      struct basic_block* succ_block = stag->block;
      int* it = std::find(bb.begin(), bb.end(), succ_block);
      if (it != bb.end()) {
        int position = std::distance(bb.begin(), it);
        if(vecc[position] != 1){
          vecc = verify_reachability(vecc,succ_block);
        }
      }
    }
    return vecc;
 }

 void verify(){
    if(entry == NULL){
      throw std::runtime_error("Every basic block must have one entry atleast");
    }
    std::vector<int> vecc(bb.size(), 0);
    vecc = traverse_bb(vecc,entry)
    int* it = std::find(vecc.begin(), vecc.end(), 0);
    if (it != vecc.end())
    {
      throw std::runtime_error("Every basic block in a function must be reachable via entry block");
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
       for(struct function *funcit:funcs){
         if(funcit->name == name){
           funcs.erase(funcs.begin()+iter);
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

