#include <iostream>
#include "cactus.h"

class application : public cactus::application {
public:
	application() {}

	~application() {}
};

cactus::application* cactus::create_application() {
	return new application();
}