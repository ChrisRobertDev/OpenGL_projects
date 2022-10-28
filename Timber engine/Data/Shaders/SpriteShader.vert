#version 430

layout(location = 0) in vec4 Position;

out vec2 UV;

uniform mat4 projection;
uniform mat4 model;

uniform vec4 texUvoffset;
uniform float isMirrored;

void main()
{
	gl_Position = projection * model * vec4(Position.xy,0.0f,1.0f);

	UV = vec2 (Position.z,1.0f-Position.w);
	//UV = vec2 (Position.z,Position.w);

	if(isMirrored == 1.0)
		if(UV.x == 0.0f)
			UV.x = 1.0f;
		else
			UV.x = 0.0f; 

	if(UV.x == 0.0f && UV.y == 0.0f){
	UV.x = UV.x + texUvoffset.x;
	UV.y = UV.y + texUvoffset.y;
	}
	if(UV.x == 1.0f && UV.y == 1.0f){
	UV.x = texUvoffset.x + texUvoffset.z;
	UV.y = texUvoffset.y + texUvoffset.w;
	}
	if(UV.x == 1.0f && UV.y == 0.0f){
	UV.x = texUvoffset.x + texUvoffset.z;
	UV.y = UV.y + texUvoffset.y;
	}
	if(UV.x == 0.0f && UV.y == 1.0f){
	UV.x = UV.x + texUvoffset.x;
	UV.y = texUvoffset.y + texUvoffset.w;
	}
	

}