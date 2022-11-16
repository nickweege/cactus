#include "cactus.h"

class layer_example : public cactus::layer {
public:
	layer_example() : layer("example layer") {}
	void on_update() override { CACTUS_INFO("layer_example::on_update"); }
	void on_event(cactus::event& event) override { CACTUS_TRACE("{0}", event); }
};

class blockits_application : public cactus::application {
public:
	blockits_application() {
		push_layer(new layer_example());
	}

	~blockits_application() {}
};

cactus::application* cactus::create_application() {
	return new blockits_application();
}