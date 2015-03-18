#ifndef SHADER_H
#define SHADER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "library/Shader/ShaderScript.h"

class Shader{
	sf::Shader::Type m_type;
	std::vector<ShaderScript> m_shaderScripts;
public:
	Shader();
};

#endif