#pragma once

#ifdef _DEBUG

	#define LOG(...) \
	    std::cout << __FILE__ << "(" << __LINE__ << "): " << (std::format(__VA_ARGS__)) << std::endl;

	#define ASSERT(con, msg) \
		{ if(!(con)) { LOG("Assertion not met: {}", msg); __debugbreak(); } }

#else

	#define LOG(...)

	#define ASSERT(con, msg)

#endif
