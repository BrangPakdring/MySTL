//
// Created by brang on 1/18/19.
//

#ifndef MYSTL_MYSTL_CONFIG_H
#define MYSTL_MYSTL_CONFIG_H

#include <cstdlib>
#include <algorithm>
#include <initializer_list>

namespace mystd
{
}


using std::size_t;
using std::ptrdiff_t;

using std::sort;
using std::swap;
using std::initializer_list;
using std::pair;

#define DEBUG_MYSTD 1
#if DEBUG_MYSTD == 1
#define ACCESSIBILITY(x) public
#elif DEBUG_MYSTD == 0
#define ACCESSIBILITY(x) x
#endif
#ifndef NAMESPACE_MYSTD
#define NAMESPACE_MYSTD mystd
#define BEGIN_NAMESPACE_MYSTD namespace NAMESPACE_MYSTD {
#define END_NAMESPACE_MYSTD }
#endif

#endif //MYSTL_MYSTL_CONFIG_H
