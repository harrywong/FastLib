#pragma once

#include "stdafx.h"
#include <functional>


namespace step {

	typedef std::function<void(char*, int)> ReadCallbackFunc;

	void DeserializeFile(const char* path, const ReadCallbackFunc& cb);

}