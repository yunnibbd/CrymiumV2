#pragma once
#include "StdAfx.h"
#include <CryFlowGraph/IFlowBaseNode.h>

using namespace Crymium;

class CFlowNode_CrymiumContailer final : public CFlowBaseNode<eNCT_Singleton>
{
private:
	enum EInputPorts
	{
		eIP_Show = 0,
		eIP_Hide,
		eIP_UIName,
		eIP_ShowInEditor,
	};

	enum EOutputPorts
	{
		eOP_AfterShow,
		eOP_AfterHide,
	};

public:
	CFlowNode_CrymiumContailer(SActivationInfo* pActInfo)
	{
	}

	virtual void GetConfiguration(SFlowNodeConfig& config) override
	{
		static const SInputPortConfig inputPorts[] = {
			InputPortConfig_Void("Show", "Show Crymium UI"),
			InputPortConfig_Void("Hide", "Hide Crymium UI"),
			InputPortConfig<string>("UIName", "Show UI Name"),
			InputPortConfig<bool>("ShowInEditor", "After loading the level in the editor, do you want to display it"),
			{0}
		};

		static const SOutputPortConfig outputPorts[] = {
			OutputPortConfig_Void("AfterShow", "while show ui"),
			OutputPortConfig_Void("AfterHide", "while hide ui"),
			{0}
		};

		config.pInputPorts = inputPorts;
		config.pOutputPorts = outputPorts;
		config.SetDescription("Crymium UI");
		config.SetCategory(EFLN_ADVANCED);
	}

	virtual void ProcessEvent(EFlowEvent event, SActivationInfo* pActInfo) override
	{
		if (event != IFlowNode::eFE_Activate)
		{
			return;
		}

		if (IsPortActive(pActInfo, eIP_Show))
		{
			string uiName = GetPortString(pActInfo, eIP_UIName);
			bool showUIInEditor = GetPortBool(pActInfo, eIP_ShowInEditor);
			mEnv->showUIOnLoadLevel = showUIInEditor;
			mEnv->showUIName = uiName;
			if (mEnv->pContainer)
			{
				mEnv->pContainer->GetUiActivator()->Activate(uiName);
			}
			ActivateOutput(pActInfo, eOP_AfterShow, true);
		}
		else if (IsPortActive(pActInfo, eIP_Hide))
		{
			if (mEnv->pContainer)
			{
				mEnv->pContainer->GetUiCloser()->Close();
			}
			ActivateOutput(pActInfo, eOP_AfterHide, true);
		}
	}

	virtual void GetMemoryUsage(ICrySizer* s) const override
	{
		s->Add(*this);
	}
};

REGISTER_FLOW_NODE("Crymium:CrymiumContailer", CFlowNode_CrymiumContailer)
