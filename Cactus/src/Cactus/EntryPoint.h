#pragma once

#ifdef CACTUS_WINDOWS_PLATFORM

extern Cactus::Application* Cactus::CreateApplication();

int main(int argc, char**argv) {
	auto app = Cactus::CreateApplication();
	app->Run();
	delete app;
}

#endif