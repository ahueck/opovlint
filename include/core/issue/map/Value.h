/*
 * Value.h
 *
 *  Created on: Jul 15, 2014
 *      Author: ahueck
 */

#ifndef VALUE_H_
#define VALUE_H_

#include "ValueTraits.h"

#include <memory>

namespace opov {

class Value {
private:
	std::string type;
	std::shared_ptr<void> value;

public:

	Value() :
			type("unknown"), value(nullptr) {
	}

	template<typename T>
	Value(const T& val) :
			type(PropertyType<T>::name()), value(std::make_shared<T>(val)) {

	}

	Value(const Value& other) :
			type(other.type), value(other.value) {
	}

	Value& operator=(const Value & other) {
		if (this != &other) {
			this->type = other.type;
			this->value = other.value;
		}
		return *this;
	}

	template<typename T>
	const T & get() {
		return *((T*) value.get());
	}

	~Value() {
	}
};

} // namespace opov

#endif /* VALUE_H_ */
