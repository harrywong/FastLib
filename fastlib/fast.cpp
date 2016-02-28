#include "fast.h"

#include <fstream>

#include <Codecs/XMLTemplateParser.h>
#include <Codecs/TemplateRegistry.h>
#include <Codecs/Template.h>
#include <Codecs/FieldInstruction.h>
#include <Codecs/DataSourceStream.h>
#include <Codecs/Decoder.h>
#include <Codecs/SingleMessageConsumer.h>
#include <Codecs/GenericMessageBuilder.h>

using namespace QuickFAST;

namespace {
	Codecs::TemplateRegistryPtr G_TEMPLATE;
}

void fast::GlobalInit()
{
	Codecs::XMLTemplateParser parser;
	std::ifstream ifs;
	ifs.open("template.2.08.xml", std::ifstream::in);
	G_TEMPLATE = parser.parse(ifs);
	ifs.close();

	assert(G_TEMPLATE);
}

void fast::Deserialize(const char * buffer, int size)
{
	
	

}
