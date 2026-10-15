#pragma once
#include "../Framework.h"

RS_NS_START

struct SerializeObject {
	void* ptr;
	size_t size = -1;

	template<typename T>
	SerializeObject(T& val) {
		ptr = &val;
		size = sizeof(T);
	}

	                                                                                          

	SerializeObject(const SerializeObject& other) {
		ptr = other.ptr;
		size = other.size;
	}
};

RS_NS_END