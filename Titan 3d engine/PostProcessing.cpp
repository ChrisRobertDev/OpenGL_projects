#include "PostProcessing.h"

int PostProcessing::width_ = 0;
int PostProcessing::height_ = 0;
FrameBuffer PostProcessing::frame1_;
FrameBuffer PostProcessing::frame2_;

//Provide a framebuffer with 2 textures, a shader that blures an image and the amount of blur to implement
GLuint PostProcessing::Bloom(FrameBuffer* frame, Shader* blurShader, GLuint amount)
{
	GLboolean firstIteration = true;
	GLboolean horizontal = true;
	blurShader->Use();
	for (GLuint i = 0; i < amount; i++) {
		if (horizontal) {
			frame1_.Bind();
			blurShader->SetInteger("horizontal", horizontal);
			if (firstIteration) {
				frame->Render(blurShader, 1);
				firstIteration = false;
				horizontal = !horizontal;
				frame1_.unBind();
			}
			else
			{
				frame2_.Render(blurShader);
				horizontal = !horizontal;
				frame1_.unBind();
			}
		}
		else
		{
			frame2_.Bind();
			blurShader->SetInteger("horizontal", horizontal);
			frame1_.Render(blurShader);
			horizontal = !horizontal;
			frame2_.unBind();
		}
	}
	frame2_.unBind();

	GLuint texture;
	if (amount % 2 == 0)
		texture = frame2_.getTextureID();
	else
		texture = frame1_.getTextureID();

	return texture;
}

void PostProcessing::Initialize(int width, int height) {
	width_ = width;
	height_ = height;
	frame1_ = FrameBuffer(GL_RGBA16F, width_, height_);
	frame2_ = FrameBuffer(GL_RGBA16F, width_, height_);
}