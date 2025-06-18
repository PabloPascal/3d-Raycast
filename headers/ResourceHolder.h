#pragma once
#include <string>
#include "map.h"
#include <unordered_map>
#include <fstream>
#include <memory>
#include <SFML/Graphics.hpp>
#include <cassert>


template <typename Identifier,typename Resource>
class ResourceHolder {

	std::unordered_map<Identifier, std::unique_ptr<Resource>> mResourceMap;

public:

	void load(Identifier id, std::string& filename);

	Resource& get(Identifier id);

	const Resource& get(Identifier id) const;

};

template <typename Identifier, typename Resource>
void ResourceHolder<Identifier, Resource>::load(Identifier id, std::string& filename){

	std::unique_ptr<Resource> res = std::make_unique<Resource>(Resource());
	
	if (!res->loadFromFile(filename)) {
		throw std::runtime_error("ResourceHolder::load can't load file" + filename);
	}

	auto inserted = mResourceMap.insert(std::make_pair(id, std::move(res)));
	assert(inserted.second);

}


template <typename Identifier, typename Resource>
Resource& ResourceHolder<Identifier, Resource>::get(Identifier id) {

	auto it = mResourceMap.find(id);

	//assert(it != mResourceMap.end());

	return (*it->second);
}


template <typename Identifier, typename Resource>
const Resource& ResourceHolder<Identifier, Resource>::get(Identifier id) const
{

	auto it = mResourceMap.find(id);

	assert(it != mResourceMap.end());

	return (*it->second);
}

