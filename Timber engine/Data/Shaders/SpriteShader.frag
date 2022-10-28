#version 430

in vec2 UV;

out vec4 FragColor;

uniform sampler2D Image;


void main()
{
	//FragColor = vec4(0.0f,1.0f,0.0f,1.0f);
	FragColor= texture(Image,UV);
	if(FragColor.a<0.1f){
		discard;
	}
	
	
}
