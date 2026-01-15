#pragma once
#include "Core/ICrymiumContainer.h"

namespace Crymium
{
	struct SCrymiumPluginEnv
	{
		ICrymiumContainer* pContainer = nullptr;
		string showUIName = "";
		bool showUIOnLoadLevel = false;
		bool hasShowUI = false;
	};

	extern SCrymiumPluginEnv* mEnv;
}
