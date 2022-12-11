#pragma once

namespace Pear
{

	class Application
	{
	public:
		Application() = default;
		virtual ~Application() = default;
		Application(const Application&) = delete;
		Application& operator=(const Application&) = delete;
		Application(Application&&) = delete;
		Application& operator=(Application&&) = delete;

		virtual void OnUpdate(float time_step) = 0;
	};

	std::unique_ptr<Application> CreateUserApp();
}
