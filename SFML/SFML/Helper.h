#pragma once
#include <map>

template<typename K, typename V>
inline void CleanupMap(std::map<K, V>& _map)
{
	auto it = _map.begin();
	while (it != _map.end())
	{
		it = _map.erase(it);
	}
	_map.clear();
}

