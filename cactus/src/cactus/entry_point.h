#pragma once

#ifdef CACTUS_WINDOWS_PLATFORM

extern cactus::application* cactus::create_application();

int main(int argc, char**argv) {
	auto app = cactus::create_application();
	app->run();
	delete app;
}

#endif