#pragma once
#ifdef __APPLE__
#include <CoreServices/CoreServices.h>
#endif

namespace FileSystem {
	class Watch {
	public:
		void register_on_save_callback(const char*);
		~Watch();
	};
} // namespace FileSystem
