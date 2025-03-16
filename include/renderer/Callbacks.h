#pragma once

#include <GLFW/glfw3.h>
#include "Definitions.h"
inline void windowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	
	if (key == GLFW_KEY_L && action == GLFW_PRESS)
	{
		GLint polygonMode;
		glGetIntegerv(GL_POLYGON_MODE, &polygonMode);

		if (polygonMode == GL_LINE)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		else if (polygonMode == GL_FILL)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (key == GLFW_KEY_F3 && action == GLFW_PRESS)
	{
		if (const int inputMode = glfwGetInputMode(window, GLFW_CURSOR); inputMode == GLFW_CURSOR_DISABLED)
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		else
		{
			using namespace Voxels::Definitions;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			glfwSetCursorPos(window, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		}

	}
}

inline void windowFramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}