#include "cactuspch.h"
#include "application.h"
#include "events/application_event.h"

namespace cactus {

	application::application() {}

	application::~application() {}

	void application::run() {
		log::init();

		window_resize_event e(1280, 720);
		CACTUS_TRACE(e);

		while (true);
	}
}