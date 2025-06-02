#pragma once
#include <functional>

class ParameterBase;
class Config;

using ConfigValidatorCallback = std::function<void(const ParameterBase* /*parameterChanged*/, Config* /*config*/)>;
