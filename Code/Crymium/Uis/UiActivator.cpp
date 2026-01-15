#include "UiActivator.h"

UiActivator::UiActivator(
	IUiPathResolver* uiPathResolver,
	IBrowser* browser
)
:
_uiPathResolver(uiPathResolver),
_browser(browser)
{
}

void UiActivator::Activate(const char* uiName)
{	
	if (mEnv->hasShowUI 
		&& !mEnv->showUIOnLoadLevel 
		&& mEnv->showUIName == uiName)
	{
		return;
	}
	const auto uiPath = _uiPathResolver->Resolve(uiName);
	_browser->GoTo(uiPath);
	mEnv->hasShowUI = true;
}
