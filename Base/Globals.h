#ifndef __Globals_H__
#define __Globals_H__

// Macro for safe object destruction
#define RELEASE(x) if (x != nullptr) { delete x; x = nullptr;}

// Macro for finding in list
#define CONTAINS(list, element) (std::find(list.begin(), list.end(), element) != list.end())

#endif