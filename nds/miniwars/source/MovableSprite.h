// (c) LGPL 2008-2010 Steve Schnepp <steve.schnepp@pwkf.org>
#ifndef __MOVABLE_SPRITE_H__
#define __MOVABLE_SPRITE_H__

#include <nds.h>

class MovableSprite {

protected:
	unsigned int frame;
	float x, y;
	
	unsigned int dest_frame;
	float dest_x, dest_y;

	bool is_shown;
	u16* gfx;
	int idx_sprite;
	int sizeX;
	int sizeY;
	unsigned short int color;
	
	int getFramesLeft() const;

public:

	virtual int getSizeX() const;
	virtual int getSizeY() const;

	MovableSprite(SpriteSize size);

	void setPosition(float x, float y);
	void setDestination(float x, float y, unsigned int dest_frame);
	void setDestination(float x, float y, float speed);
	
	void moveTo(float dx, float dy, float speed);
	float getScreenX() const;
	float getScreenY() const;

	virtual bool draw() const;

	bool isShown() const;
	bool setShown(bool is_shown);
	virtual bool isExpired() const;
};

#endif // __MOVABLE_SPRITE_H__
