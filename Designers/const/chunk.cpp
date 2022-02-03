#ifndef CHUNK_H
#define CHUNK_H
#include "chunk.h"

//注意这些写法只有在 cpp 中才是生效的

const int NN = 10;      // file scope
const int MM = 44;      // file scope
extern const int QQ = 7; // can be accessed from other files

#endif // CHUNK_H
