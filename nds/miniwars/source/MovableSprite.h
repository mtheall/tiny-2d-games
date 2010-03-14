// Copyright 2008-2010 Steve Schnepp <steve.schnepp@pwkf.org>
#ifndef __MOVABLE_SPRITE_H__
#define __MOVABLE_SPRITE_H__

#include <nds.h>

class MovableSprite {

public:
	int frame;
	float x, y;
	
	int dest_frame;
	float dest_x, dest_y;

	bool is_shown;
	u16* gfx;
	int idx_sprite;
	SpriteSize size;

	int getSizeX() const;
	int getSizeY() const;

	MovableSprite(SpriteSize size);

	void setDestination(float x, float y, int current_frame, int dest_frame);
	int getScreenX(int current_frame) const;
	int getScreenY(int current_frame) const;
	int getFramesLeft(int current_frame) const;
};

#endif // __MOVABLE_SPRITE_H__
