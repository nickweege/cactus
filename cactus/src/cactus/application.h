#pragma once

#include "events/event.h"

namespace cactus {

	class application {
	public:
		application();
		virtual ~application();
		void run();
	};

	application* create_application();

}