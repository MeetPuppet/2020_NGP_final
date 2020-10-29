#pragma once
//======================================
// ## 2017. 10. 25 ## - image Class - ##
//======================================

class image
{
public:
	//이미지 불러오는 종류
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE,		//리소스로부터
		LOAD_FILE,			//이미지 파일로부터
		LOAD_EMPTY,			//빈 비트맵 파일
		LOAD_END			
	};

	typedef struct tagImageInfo
	{
		DWORD resID;			//리소스 불러올때 사용되는 변수지만 안쓸꺼야 아마 ㅋ _ㅋ
		HDC hMemDC;				//메모리 DC
		HBITMAP hBit;			//비트맵
		HBITMAP hOBit;			//올드 비트맵
		float x;
		float y;
		int width;				//가로 크기 (이미지)
		int height;				//세로 크기 (이미지)
		int currentFrameX;		//현재 프레임 번호X
		int currentFrameY;		//현재 프레임 번호Y
		int maxFrameX;			//최대 프레임 번호
		int maxFrameY;
		int frameWidth;			//이미지 한 장당 크기
		int frameHeight;
		BYTE loadType;			//이미지 크기와는 무관

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			
			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;		//이미지 정보 담을 구조체
	CHAR*			_fileName;		//파일 이름
	BOOL			_trans;			//트랜스컬러 처리 유/무
	COLORREF		_transColor;	//어떤 컬러를 뺄꺼냐

	BLENDFUNCTION	_blendFunc;		//알파블렌드를 사용하기위한 구조체
	LPIMAGE_INFO	_blendImage;	//알파블렌드를 먹이기위한 이미지 정보

public:
	image();
	~image();

	//빈 비트맵 이미지를 등록할때
	HRESULT init(int width, int height);
	HRESULT init(const char* fileName, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE);
	HRESULT init(const char* fileName, float x, float y, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE);

	HRESULT init(const char* fileName, float x, float y, int width, int height,
		int frameX, int frameY, BOOL trans, COLORREF transColor);

	HRESULT init(const char* fileName, int width, int height,
		int frameX, int frameY, BOOL trans, COLORREF transColor);

	void release(void);

	//트랜스 컬러 셋팅 함수
	void setTransColor(BOOL trans, COLORREF transColor);


	void render(HDC hdc);
	//        뿌릴 DC영역  X좌표(LEFT), Y좌표(TOP)
	void render(HDC hdc, int destX, int destY);
	//        뿌릴 DC영역, 뿌려줄 X,Y좌표        가져올 X, Y(Left, Top) 가져올 가로, 세로 크기  
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//   프레임렌더   뿌릴DC영역  좌표 X   좌표 Y (left Top)
	void frameRender(HDC hdc, int destX, int destY);
	//   프레임 렌더  뿌릴DC영역  좌표 X    좌표 Y (left, top) 프레임 번호 X  프레임번호 Y
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);

	void alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);


	inline HDC getMemDC() { return _imageInfo->hMemDC; }

	//====================================================
	// 이미지 조작 편안하게 해줄께
	//====================================================

	inline void setX(float x) { _imageInfo->x = x; }
	inline float getX(void) { return _imageInfo->x; }

	inline void setY(float y) { _imageInfo->y = y; }
	inline float getY(void) { return _imageInfo->y; }

	//가운데 좌표로 보정
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	inline float getCenterX()
	{
		return _imageInfo->maxFrameX <= 0 ? _imageInfo->x + (_imageInfo->width / 2) :
				_imageInfo->x + (_imageInfo->frameWidth / 2);
	}

	inline float getCenterY()
	{
		return _imageInfo->maxFrameY <= 0 ? _imageInfo->y + (_imageInfo->height / 2) :
			_imageInfo->y + (_imageInfo->frameHeight / 2);
	}

	inline void setFrameX(int frameX)
	{
		if (frameX < 0) _imageInfo->currentFrameX = 0;
		else _imageInfo->currentFrameX = frameX;
		if (_imageInfo->maxFrameX < frameX) _imageInfo->maxFrameX = frameX;
	}

	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (_imageInfo->maxFrameY < frameY) _imageInfo->maxFrameY = frameY;
	}

	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }

	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }

	inline int getWidth(void) { return _imageInfo->width; }
	inline int getHeight(void) { return _imageInfo->height; }

	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

};


