#include "CrymiumInitialiser.h"

CrymiumInitialiser::CrymiumInitialiser(
	ICrymiumCefInitialiser* crymiumCefInitialiser,
	ICryInitialiser* cryInitialiser
)
:
_crymiumCefInitialiser(crymiumCefInitialiser),
_cryInitialiser(cryInitialiser),
_isInit(false)
{
}

void CrymiumInitialiser::Initialise()
{
	if (_isInit)
	{
		return;
	}

	_crymiumCefInitialiser->Initialise();

	_cryInitialiser->Initialise();

	_isInit = true;
}
