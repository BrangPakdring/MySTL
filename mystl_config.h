//
// Created by brang on 1/18/19.
//

#ifndef MYSTL_MYSTL_CONFIG_H
#define MYSTL_MYSTL_CONFIG_H

namespace mystd
{
}

#include <stdlib.h>

using std::size_t;
using std::ptrdiff_t;

#define DEBUG_MYSTD 1
#if DEBUG_MYSTD
#define ACCESSIBILITY(x) public
#else
#define ACCESSIBILITY(x) x
#endif
#ifndef NAMESPACE_MYSTD
#define NAMESPACE_MYSTD mystd
#define BEGIN_NAMESPACE_MYSTD namespace mystd {
#define END_NAMESPACE_MYSTD }
#endif

#endif //MYSTL_MYSTL_CONFIG_H
