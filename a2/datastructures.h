#include <vector>

struct tag{
 std::string name;
 struct basic_block* block;
}

struct basic_block {
public:
 std::string name;
 /* each basic block has successors and each sucessors is identified by a tag*/
 /* tags are identified by their tag string */
 /* and each tag string needs to be unique*/
 /* otherway of saying at most one sucessor per tag */
 std::vector<struct tag*> successors;
 std::vector<std::string> sucnames;
 int check_uniq(std::string tagname){
     for(std::string tname:sucnames){
        if(tname == tagname){
           return 0
          }
     }
     return 1;
 }
 void add_sucessor(struct basic_block* bb,std::name tagname){
      if(!check_uniq(tagname)){
         throw std::runtime_error("Tag name needs to be unique because each tag connect between two blocks a singular pathway")
      }
      struct tag tagsmember = new struct tag;
      tagsmember->name = tagname;
      tagsmember->block = bb;
      successors.push_back(tagsmember);
 }

};

/*module has list of functions and a functions and function has basic blocks */
struct function{
public:
  std::string name;
  /*should there be tag list? from the looks of assignment 2? to do later */
  std::vector<struct basic_block*> bb;

  void insert_bb(struct basic_block* block){
       bb.push_back(block);
  }

  void remove_by_name(std::string name){
       int iter = 0;
       for(struct basic_block* blockit:bb){
         ++iter;
         if(blockit->name == name){
           funcs.erase(iter);
           /* should we return copy */
         }
       }
  }

  void visualize(){
  std::cout<<"digraph "<<name<<"\n"
  for(struct basic_block* blockit:bb){
     std::string current = blockit->name;
     for(struct tag* tagn:blockit->successors){
      std::cout<<current<<"->"<<tagn->block->name<<"[label="<<"\""<<tagn->name"\""<<";"
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
  void remove_by_name(std::string name){
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


struct module* make_module(std::string name);
struct function* make_function(std::string name);
struct basic_block* make_bb(std::string name);
