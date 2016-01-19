/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#include <cmath>
#include "quberaid.hpp"
#include "utils/inputmanager.hpp"
#include "utils/mousepointer.hpp"

using namespace irr;


static void drawImage(video::IVideoDriver* driver, const video::ITexture* texture,
					  core::rect<s32> sourceRect, core::rect<s32> destRect, core::vector2d<s32> rotationCenter,
					  f32 rotation, video::SColor color = 0xffffffff)
{
	video::SMaterial material;// = driver->getMaterial2D();

	// Store and clear the projection matrix
	core::matrix4 oldProjMat = driver->getTransform(video::ETS_PROJECTION);
	driver->setTransform(video::ETS_PROJECTION, core::matrix4());

	// Store and clear the view matrix
	core::matrix4 oldViewMat = driver->getTransform(video::ETS_VIEW);
	driver->setTransform(video::ETS_VIEW, core::matrix4());

	// Find the positions of corners
	core::vector2di corner[4];
	corner[0] = core::vector2di(destRect.UpperLeftCorner.X, destRect.UpperLeftCorner.Y);
	corner[1] = core::vector2di(destRect.LowerRightCorner.X, destRect.UpperLeftCorner.Y);
	corner[2] = core::vector2di(destRect.UpperLeftCorner.X, destRect.LowerRightCorner.Y);
	corner[3] = core::vector2di(destRect.LowerRightCorner.X, destRect.LowerRightCorner.Y);;

	// Rotate corners
	if (rotation != 0.0f)
	{
		rotationCenter += destRect.UpperLeftCorner;
		for (int x = 0; x < 4; x++)
			corner[x].rotateBy(rotation, rotationCenter);
	}

	// Find the uv coordinates of the sourceRect
	core::vector2df invTexSize(1.f / texture->getSize().Width, 1.f / texture->getSize().Height);
	core::vector2df uvCorner[4];
	uvCorner[0] = core::vector2df((f32)sourceRect.UpperLeftCorner.X,  (f32)sourceRect.UpperLeftCorner.Y) * invTexSize;
	uvCorner[1] = core::vector2df((f32)sourceRect.LowerRightCorner.X, (f32)sourceRect.UpperLeftCorner.Y) * invTexSize;
	uvCorner[2] = core::vector2df((f32)sourceRect.UpperLeftCorner.X,  (f32)sourceRect.LowerRightCorner.Y) * invTexSize;
	uvCorner[3] = core::vector2df((f32)sourceRect.LowerRightCorner.X, (f32)sourceRect.LowerRightCorner.Y) * invTexSize;

	// Vertices for the image
	video::S3DVertex vertices[4];
	u16 indices[6] = { 0, 1, 2, 3 ,2 ,1 };

	// Convert pixels to world coordinates
	float screenWidth = (f32)driver->getScreenSize().Width;
	float screenHeight = (f32)driver->getScreenSize().Height;
	for (int x = 0; x < 4; x++)
	{
		float screenPosX = ((corner[x].X / screenWidth) - 0.5f) * 2.0f;
		float screenPosY = ((corner[x].Y / screenHeight) - 0.5f) * -2.0f;
		vertices[x].Pos = core::vector3df(screenPosX, screenPosY, 1);
		vertices[x].TCoords = uvCorner[x];
		vertices[x].Color = color;
	}
	material.Lighting = false;
	material.ZWriteEnable = false;
	material.ZBuffer = false;
	material.TextureLayer[0].Texture = const_cast<video::ITexture*>(texture);
	material.MaterialType = video::EMT_ONETEXTURE_BLEND; // video::EMT_TRANSPARENT_ALPHA_CHANNEL; // video::EMT_SOLID;
	material.MaterialTypeParam =
		video::pack_textureBlendFunc(irr::video::EBF_SRC_ALPHA, irr::video::EBF_ONE_MINUS_SRC_ALPHA,
			irr::video::EMFN_MODULATE_1X, irr::video::EAS_TEXTURE | irr::video::EAS_VERTEX_COLOR);
	//material.TextureLayer[0].TextureWrapU = video::ETC_CLAMP;
	//material.TextureLayer[0].TextureWrapV = video::ETC_CLAMP;

	driver->setMaterial(material);
	driver->drawIndexedTriangleList(&vertices[0], 4, &indices[0], 2);

	// Restore projection and view matrices
	driver->setTransform(video::ETS_PROJECTION, oldProjMat);
	driver->setTransform(video::ETS_VIEW, oldViewMat);
}


MousePointer::MousePointer(QubeRaid* app) :
	m_app(app),
	m_texture(app->getDriver()->getTexture("../assets/mouse.png"))
{
}

MousePointer::~MousePointer()
{
}

void MousePointer::render()
{
	core::vector2di mouse_pos = m_app->getInputManager()->getMousePosition();
	float angle = (float)std::atan2(mouse_pos.X - m_mouse_back_pos.X, -mouse_pos.Y + m_mouse_back_pos.Y);

	drawImage(m_app->getDriver(), m_texture, core::recti{ {0, 0}, {32, 32} }, core::recti{ mouse_pos, mouse_pos + core::vector2di{32, 32} }, { 0, 0 }, core::radToDeg(angle) + 45);

	m_mouse_back_pos = mouse_pos;
	m_mouse_back_pos.X -= (s32)(std::sin(angle) * 32.f);
	m_mouse_back_pos.Y += (s32)(std::cos(angle) * 32.f);
}
