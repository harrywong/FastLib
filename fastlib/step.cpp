#include "step.h"
#include <stdio.h>

#define BUFFER_LENGTH 1024000

using namespace re2;

void step::DeserializeFile(const char * path, const ReadCallbackFunc & cb)
{
	auto fd = fopen(path, "rb");
	re2::RE2 pattern("95=(\\d+)\\x0196=(.*?)\\x01");
	assert(pattern.ok());

	char buffer[BUFFER_LENGTH];
	StringPiece sp(buffer, BUFFER_LENGTH);

	int r = 0, offset = 0;
	while (!feof(fd)) {
		r = fread(buffer + offset, sizeof(char), BUFFER_LENGTH - offset, fd);
		
		int length = 0;
		std::string buf;
		while (RE2::FindAndConsume(&sp, "95=(\\d+)\\x0196=(.*?)\\x01", &length)) {
			cb(buf, length);
		}
		
	}
}
