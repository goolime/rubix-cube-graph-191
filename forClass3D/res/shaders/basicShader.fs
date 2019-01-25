#version 130

varying vec2 texCoord0;
varying vec3 normal0;
varying vec3 color0;

uniform vec3 lightDirection;
uniform vec3 lightColor;

void main()
{
	float border=0.035;
    //vec3 tmp = dot(-lightDirection, normal0) * color0 ;
	if ((texCoord0.y<border) || (texCoord0.x <border) || (texCoord0.y>(1-border)) || (texCoord0.x >(1-border))){ 
		gl_FragColor =  clamp(vec4(0,0,0,1.0), 0.0, 1.0);
	}
	else {
		vec3 tmp = dot(-lightDirection, normal0) * color0 ;
		gl_FragColor =  clamp(vec4(tmp,1.0), 0.0, 1.0);
		//gl_FragColor =  clamp(vec4(color0,1.0), 0.0, 1.0);
	}
}
