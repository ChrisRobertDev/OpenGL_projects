#version 430


out vec4 FragColor;

uniform vec3 color;


void main()
{
	//FragColor = vec4(1.0f,0.0f,0.0f,1.0f);
	//FragColor= texture(Image,UV);
	FragColor = vec4(color,1.0f);
	//if(FragColor.a<0.1f){
	//	discard;
	//}
	
	
}
