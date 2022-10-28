#pragma once

#include "FrameBuffer.h"
#include "Shader.h"

class PostProcessing
{
public:
	static void Initialize(int width, int height);
	static GLuint Bloom(FrameBuffer* frame,Shader* blurShader,GLuint amount = 10);

private:
	static int width_;
	static int height_;
	static FrameBuffer frame1_;
	static FrameBuffer frame2_;
};

