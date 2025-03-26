#include "feature_flags.h"
#include <glad/glad.h>
#include "logger.h"

bool FeatureFlags::CanMultisampleFbo()
{
	GLint majVers = 0, minVers = 0;
	glGetIntegerv(GL_MAJOR_VERSION, &majVers);
	glGetIntegerv(GL_MINOR_VERSION, &minVers);

	if (majVers >= 4 && minVers >= 3) {
		return true;
	}

	return false;
}
