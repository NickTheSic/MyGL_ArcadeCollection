#ifndef __FRAMEWORK_PCH__
#define __FRAMEWORK_PCH__

#ifdef _WINDOWS 
#include <Windows.h>
#endif

#include <assert.h>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <Constants.h>
#include <Debug/Debugging.h>
#include <Debug/Logger.h>

#include <Utilities/Random.h>
#include <Utilities/Utilities.h>
#include <Utilities/ColorList.h>

#include <Application.h>

#include <Graphics/ShaderProgram.h>
#include <Graphics/Renderer.h>
#include <Graphics/Shape.h>


#endif //__FRAMEWORK_PCH__