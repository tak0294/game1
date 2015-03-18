uniform float wave_phase;
uniform vec2 wave_amplitude;
uniform float wave_height;
layout(binding=0, offset=0) uniform atomic_uint ac;

void main()
{
	uint counter = atomicCounterIncrement(ac);
	float step = 360/wave_height;
    vec4 vertex = gl_Vertex;
    float tmp = wave_phase + counter;
    
    //vertex.x += cos(gl_Vertex.y * 0.2 + wave_phase * 3.8) * wave_amplitude.x + sin(gl_Vertex.y * 0.02 + wave_phase) * wave_amplitude.x * 0.3;
	

	//vertex.x = gl_Vertex.x + (sin(3.14/180*((wave_phase*2+ (gl_Vertex.y*counter))*100)) * 50);
	//vertex.x = gl_Vertex.x + (sin(3.14/180*((wave_phase*2+ (gl_Vertex.y*counter))*100)) * 50);


    //vertex.y = gl_Vertex.y;

	gl_Position = gl_ModelViewProjectionMatrix * vertex;
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
	gl_FrontColor = gl_Color;
}