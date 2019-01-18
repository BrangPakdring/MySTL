//
// Created by brang on 1/18/19.
//

#ifndef MYSTL_MYSTL_CONFIG_H
#define MYSTL_MYSTL_CONFIG_H

#include <stdlib.h>
using std::size_t;
using std::ptrdiff_t;

namespace mystd{}
#ifndef NAMESPACE_MYSTD
#define NAMESPACE_MYSTD mystd
#define BEGIN_NAMESPACE_MYSTD namespace mystd {
#define END_NAMESPACE_MYSTD }
#endif

#endif //MYSTL_MYSTL_CONFIG_H
