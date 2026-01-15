#include "JavaScriptFunctionCallBuilder.h"

std::string JavaScriptFunctionCallBuilder::Build(const char* functionNameIn, const std::vector<std::string>& parameters)
{
	std::string functionName = functionNameIn;
	auto javaScriptString = functionName + "(";

	auto parameterCount = parameters.size();

	auto parameterMaxIndex = parameterCount - 1;

	for (auto parameterIndex = 0; parameterIndex < parameterCount; parameterIndex++)
	{
		auto parameter = parameters[parameterIndex];

		auto parameterString = parameter;

		javaScriptString += parameterString;

		if (parameterIndex < parameterMaxIndex)
		{
			javaScriptString += ",";
		}
	}

	javaScriptString += ");";

	return javaScriptString;
}
