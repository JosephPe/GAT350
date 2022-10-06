#include "ResourceManager.h"
#pragma once

namespace anthemum
{

	void ResourceManager::Initialize()
	{
	}

	void ResourceManager::Shutdown()
	{
		m_resources.clear();
	}

}