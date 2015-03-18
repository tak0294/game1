#ifndef SHADER_SCRIPT_H
#define SHADER_SCRIPT_H

#include <SFML/Graphics.hpp>
#include <string>

class ShaderScript{

public:
	ShaderScript();

protected:
	std::string m_mainScript;
	std::string m_headerScript;
	void setScript();
};

#endif