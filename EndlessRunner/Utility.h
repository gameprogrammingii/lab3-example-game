#pragma once

#include <vector>
#include <algorithm>

// Taken from stack overflow: https://stackoverflow.com/questions/7631996/remove-an-element-from-a-vector-by-value-c
template<typename T>
inline void remove(std::vector<T>& v, const T& item)
{
	v.erase(std::remove(v.begin(), v.end(), item), v.end());
}
