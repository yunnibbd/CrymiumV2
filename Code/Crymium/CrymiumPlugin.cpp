#include "StdAfx.h"
#include "CrymiumPlugin.h"
#include <CryCore/Platform/platform_impl.inl>
#include "CrymiumContainerComposer.h"

CrymiumPlugin::~CrymiumPlugin()
{
	gEnv->pSystem->GetISystemEventDispatcher()->RemoveListener(this);
}

bool CrymiumPlugin::Initialize(SSystemGlobalEnvironment& env, const SSystemInitParams& initParams)
{
	gEnv->pSystem->GetISystemEventDispatcher()->RegisterListener(this, "Crymium");

	_crymiumContainer = CrymiumContainerComposer::Compose();

	mEnv->pContainer = _crymiumContainer.get();

	return true;
}

void CrymiumPlugin::OnSystemEvent(ESystemEvent event, UINT_PTR wparam, UINT_PTR lparam)
{
	switch (event)
	{
	case ESYSTEM_EVENT_LEVEL_LOAD_START:
		{
			if (gEnv->IsEditor()) 
			{
				if (mEnv->showUIName != "" && mEnv->showUIOnLoadLevel && mEnv->hasShowUI)
				{
					mEnv->pContainer->GetUiCloser()->Close();
				}
				_crymiumContainer->GetCrymiumInitialiser()->Initialise();
			}
		}
		break;
	case ESYSTEM_EVENT_LEVEL_LOAD_END:
		{
			if (gEnv->IsEditor() 
				&& mEnv->showUIName != "" 
				&& mEnv->hasShowUI)
			{
				_crymiumContainer->GetCrymiumInitialiser()->Initialise();
				_crymiumContainer->GetUiActivator()->Activate(mEnv->showUIName);
			}
		}
		break;
	case ESYSTEM_EVENT_GAME_POST_INIT:
		{
			if (!gEnv->IsEditor())
			{
				_crymiumContainer->GetCrymiumInitialiser()->Initialise();
			}
		}
		break;
	case ESYSTEM_EVENT_GAME_MODE_SWITCH_END:
		{
			if (gEnv->IsEditor() && mEnv->hasShowUI && !mEnv->showUIOnLoadLevel)
			{
				mEnv->pContainer->GetUiCloser()->Close();
			}
		}
		break;
	}
}

ICrymiumContainer* CrymiumPlugin::GetCrymiumContainer()
{
	return _crymiumContainer.get();
}

CRYREGISTER_SINGLETON_CLASS(CrymiumPlugin)