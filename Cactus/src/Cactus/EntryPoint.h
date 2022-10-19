#pragma once

#ifdef CACTUS_WINDOWS_PLATFORM

extern Cactus::Application* Cactus::CreateApplication();

int main(int argc, char**argv) {
	Cactus::Log::Init();
	CACTUS_CORE_TRACE("123");

	auto app = Cactus::CreateApplication();
	app->Run();
	delete app;
}

#endif