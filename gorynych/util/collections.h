//
// Created by szuyev on 24.05.16.
//

#pragma once

#include <map>
#include <vector>
#include "memory.h"

namespace zzsystems { namespace gorynych {
template<typename key, typename value, typename comparator = std::less<key>>
using aligned_map = std::map<key, value, comparator, aligned_allocator<std::pair<const key, value>, alignof(value)>>;

template<typename value>
using aligned_vector = std::vector<value, aligned_allocator<value, alignof(value)>>;
    }}