#include "cactus.h"

class blockits_application : public cactus::application {
public:
	blockits_application() {}

	~blockits_application() {}
};

cactus::application* cactus::create_application() {
	return new blockits_application();
}