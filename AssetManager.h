#pragma once

#include <unordered_map>
#include <exception>
#include <cassert>
#include <memory>

template <typename ID, typename Resource>
class AssetManager {
public:
	AssetManager() = default;

	void load(ID id, const std::string& filename);

	Resource& get(ID id);
	const Resource& get(ID id) const;

private:
	std::unordered_map<ID, std::unique_ptr<Resource>> _map;
};

template<typename ID, typename Resource>
inline void AssetManager<ID, Resource>::load(ID id, const std::string& filename) {
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename)) {
		throw std::runtime_error("AssetManaget::load - Failed to load " + filename);
	}

	auto inserted = _map.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}

template<typename ID, typename Resource>
inline Resource& AssetManager<ID, Resource>::get(ID id) {
	auto found = _map.find(id);
	assert(found != _map.end());

	return *found->second;
}

template<typename ID, typename Resource>
inline const Resource& AssetManager<ID, Resource>::get(ID id) const {
	const auto found = _map.find(id);
	assert(found != _map.end());

	return *found->second;
}
