#pragma once
#include "singletonBase.h"
#include "image.h"
#include <map>

class imageManager : public singletonBase<imageManager>
{
private:
	typedef map<string, image*> mapImageList;
	typedef map<string, image*>::iterator mapImageIter;

private:
	mapImageList _mImageList;
	
public:
	HRESULT init(void);
	void release(void);

	image* addImage(string strKey, int width, int height);
	image* addImage(string strKey, const char* fileName, int width, int height, bool trans, COLORREF transColor);
	image* addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool trans, COLORREF transColor);

	image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);
	image* addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);

	image* findImage(string strKey);

	BOOL deleteImage(string strKey);

	BOOL deleteAll(void);

	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//   ÇÁ·¹ÀÓ·»´õ   »Ñ¸±DC¿µ¿ª  ÁÂÇ¥ X   ÁÂÇ¥ Y (left Top)
	void frameRender(string strKey, HDC hdc, int destX, int destY);
	//   ÇÁ·¹ÀÓ ·»´õ  »Ñ¸±DC¿µ¿ª  ÁÂÇ¥ X    ÁÂÇ¥ Y (left, top) ÇÁ·¹ÀÓ ¹øÈ£ X  ÇÁ·¹ÀÓ¹øÈ£ Y
	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);

	void alphaFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	imageManager();
	~imageManager();
};

