#version 430

layout(location = 0) in vec2 Position;


uniform mat4 projection;
uniform mat4 model;

void main()
{
	//gl_PointSize = 10.0f;
	gl_Position = projection * model * vec4(Position.xy,0.0f,1.0f);
	
	//UV = vec2 (Position.z,1.0f-Position.w);
	//UV = vec2 (Position.z,Position.w);
	

}