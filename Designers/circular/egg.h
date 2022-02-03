#ifndef EGG_H
#define EGG_H

// ★★★★ 核心
class Chicken;              /* Forward class declaration. */

class Egg {
 public:
    Chicken* getParent();   /* Okay in declarations if they are pointers. */ 
};
//end
#endif        //  #ifndef EGG_H
