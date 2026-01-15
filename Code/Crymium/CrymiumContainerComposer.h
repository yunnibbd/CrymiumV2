#pragma once
#include "Crymium/Core/ICrymiumContainer.h"
#include <string>
#include <memory>

namespace Crymium
{
	class CrymiumContainerComposer
	{
	public:
		__declspec(dllexport) static std::unique_ptr<ICrymiumContainer> Compose(const char* uiDirectory = nullptr);
	};
}

using namespace Crymium;