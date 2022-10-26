#include "application.h"
#include "log.h"
#include "events/application_event.h"

namespace cactus {

	application::application() {}

	application::~application() {}

	void application::run() {
		window_resize_event _event(1280, 720);
		// CACTUS_TRACE(_event);
		while (true);
	}

}