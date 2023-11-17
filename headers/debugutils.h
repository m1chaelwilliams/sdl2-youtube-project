#ifndef DEBUGUTILS_H
#define DEBUGUTILS_H

#ifdef DEBUG
#include <iostream>
#define LOG(X) std::cout << X << std::endl;
#else
#define LOG(X)
#endif

#endif