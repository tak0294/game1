uniform sampler2D texture;
uniform float pixel_threshold;
uniform float wave_phase;


void main()
{
    float factor = 1.0 / (pixel_threshold + 0.001);
	vec2 pos = floor(gl_TexCoord[0].xy * factor + 0.5) / factor;

	vec2 calcPos;
	calcPos.x = mod(1.0 + gl_TexCoord[0].x + 2*sin(gl_TexCoord[0].y * 12.0 + wave_phase * 0.05), 1.0);
	calcPos.y = gl_TexCoord[0].y;

	gl_FragColor = texture2D(texture, calcPos) * gl_Color;	
}