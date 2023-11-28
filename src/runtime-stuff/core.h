#if !defined(CORE_H)
#define CORE_H

#include <vector>
#include <string>
#include <map>

using namespace std;

struct Val{
    int integer;
    string str;
    float flt;
    string type;
};
struct Var{
   struct Val ref;
};
struct Val makeint(int in){
    struct Val v;
    v.type = "int";
    v.integer = in;
    return v;
}

#endif // CORE_H