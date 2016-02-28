#pragma once

#include "stdafx.h"
#include <functional>
#include <re2/re2.h>


namespace step {

	typedef std::function<void(std::string&, int)> ReadCallbackFunc;

	void DeserializeFile(const char* path, const ReadCallbackFunc& cb);
	void Deserialize(const char* content, re2::StringPiece&, int);

}