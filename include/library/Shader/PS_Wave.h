#ifndef PS_WAVE_H
#define PS_WAVE_H

#include "library/Video.h"
#include "library/Shader/ShaderScript.h"

class PS_Wave : public ShaderScript {
public:
	void setShaderScript(){
	/////////////////////////////////////
	// Header.
	/////////////////////////////////////
	m_headerScript = "\
					uniform float wave_phase; \
				  ";

	/////////////////////////////////////
	// Main.
	/////////////////////////////////////		  
	m_mainScript = "\
					pos.x = mod(1.0f + pos.x + 0.05f*sin(pos.y * 30.0f + wave_phase * 0.95f), 1.0f); \
					";
	};
	

	void setShaderParams(sf::Shader &shader){
		shader.setParameter("wave_phase", Video::videoClock.getElapsedTime().asSeconds());
	};

};

#endif
