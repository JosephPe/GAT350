#pragma once
#include <string>

namespace anthemum
{
	class Resource
	{
	public : 
		virtual bool Create(std::string name, ...) = 0;
	};
}