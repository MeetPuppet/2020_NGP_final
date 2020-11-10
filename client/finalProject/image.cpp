#include "stdafx.h"
#include "image.h"

//컴파일러 지시기
#pragma comment(lib, "msimg32.lib")

//멤버 이니셜라이즈 == const 속성을 초기화 해주기 위해 고안된 방식(원래는)
//너무나 편해서 다른 의미로 많이 활용 중
image::image()
	: _imageInfo(NULL),
	_fileName(NULL),
	_trans(false),
	_transColor(RGB(0, 0, 0))
{
}


image::~image()
{
}

//빈 비트맵 이미지를 등록할때
HRESULT image::init(int width, int height)
{
	//이미지 정보가 뭔가 남아있다면? -> 해제시켜라
	if (_imageInfo != NULL) release();

	//DC영역을 가져온다
	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;											//이미지는 동적할당
	_imageInfo->loadType = LOAD_EMPTY;										//타입은 빈 비트맵 타입
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);							//빈 DC영역을 생성
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);	//빈 비트맵 이미지 생성
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = NULL;

	_trans = FALSE;
	_transColor = RGB(0, 0, 0);

	//알파블렌드 셋팅
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP) CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP) SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//비트맵이 생성이 안되었다면
	if (_imageInfo->hBit == NULL)
	{
		//해제시키고
		release();
		//실패했다고 알려라
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char* fileName, int width, int height,
	BOOL trans, COLORREF transColor)
{
	//이미지 정보가 뭔가 남아있다면? -> 해제시켜라
	if (_imageInfo != NULL) release();

	//DC영역을 가져온다
	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;											//이미지는 동적할당
	_imageInfo->loadType = LOAD_FILE;										//타입은 빈 비트맵 타입
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);							//빈 DC영역을 생성
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	//알파블렌드 셋팅
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP) CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP) SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//비트맵이 생성이 안되었다면
	if (_imageInfo->hBit == NULL)
	{
		//해제시키고
		release();
		//실패했다고 알려라
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char* fileName, float x, float y, int width, int height,
	BOOL trans, COLORREF transColor)
{
	//이미지 정보가 뭔가 남아있다면? -> 해제시켜라
	if (_imageInfo != NULL) release();

	//DC영역을 가져온다
	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;											//이미지는 동적할당
	_imageInfo->loadType = LOAD_FILE;										//타입은 빈 비트맵 타입
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);							//빈 DC영역을 생성
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;

	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	//알파블렌드 셋팅
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP) CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP) SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//비트맵이 생성이 안되었다면
	if (_imageInfo->hBit == NULL)
	{
		//해제시키고
		release();
		//실패했다고 알려라
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char* fileName, float x, float y, int width, int height,
	int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	//이미지 정보가 뭔가 남아있다면? -> 해제시켜라
	if (_imageInfo != NULL) release();

	//DC영역을 가져온다
	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;											//이미지는 동적할당
	_imageInfo->loadType = LOAD_FILE;										//타입은 빈 비트맵 타입
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);							//빈 DC영역을 생성
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;


	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	//알파블렌드 셋팅
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP) CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP) SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//비트맵이 생성이 안되었다면
	if (_imageInfo->hBit == NULL)
	{
		//해제시키고
		release();
		//실패했다고 알려라
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char* fileName, int width, int height,
	int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	//이미지 정보가 뭔가 남아있다면? -> 해제시켜라
	if (_imageInfo != NULL) release();

	//DC영역을 가져온다
	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;											//이미지는 동적할당
	_imageInfo->loadType = LOAD_FILE;										//타입은 빈 비트맵 타입
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);							//빈 DC영역을 생성
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;


	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	//알파블렌드 셋팅
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP) CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP) SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//비트맵이 생성이 안되었다면
	if (_imageInfo->hBit == NULL)
	{
		//해제시키고
		release();
		//실패했다고 알려라
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);


	return S_OK;
}

void image::release(void)
{
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);	//올드 비트맵삭제
		DeleteObject(_imageInfo->hBit);							//비트맵 삭제
		DeleteDC(_imageInfo->hMemDC);							//DC영역 삭제

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);

		_trans = false;
		_transColor = RGB(0, 0, 0);
	}
}

//트랜스 컬러 셋팅 함수
void image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}

void image::render(HDC hdc)
{
	//특정 컬러를 빼줘야되느냐?
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//복사될 영역의 DC
			_imageInfo->x,			//복사될 좌표 X
			_imageInfo->y,			//복사될 좌표 Y
			_imageInfo->width,		//복사될 가로크기
			_imageInfo->height,		//복사될 세로크기
			_imageInfo->hMemDC,		//복사할 DC
			0, 0,					//복사해올 좌표
			_imageInfo->width,		//복사해올 크기
			_imageInfo->height,
			_transColor);			//제외할 컬러값
	}
	else
	{
		//백버퍼에 영역을 HDC영역으로 고속복사 해준다
		BitBlt(hdc, _imageInfo->x, _imageInfo->y,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			SRCCOPY);
	}
}

//        뿌릴 DC영역  X좌표(LEFT), Y좌표(TOP)
void image::render(HDC hdc, int destX, int destY)
{
	//특정 컬러를 빼줘야되느냐?
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//복사될 영역의 DC
			destX,					//복사될 좌표 X
			destY,					//복사될 좌표 Y
			_imageInfo->width,		//복사될 가로크기
			_imageInfo->height,		//복사될 세로크기
			_imageInfo->hMemDC,		//복사할 DC
			0, 0,					//복사해올 좌표
			_imageInfo->width,		//복사해올 크기
			_imageInfo->height,
			_transColor);			//제외할 컬러값
	}
	else
	{
		//백버퍼에 영역을 HDC영역으로 고속복사 해준다
		BitBlt(hdc, destX, destY,
			_imageInfo->width, 
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0, 
			SRCCOPY);
	}

}

//				뿌릴 DC영역, 뿌려줄 X,Y좌표        가져올 X, Y(Left, Top) 가져올 가로, 세로 크기  
void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	//특정 컬러를 빼줘야되느냐?
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//복사될 영역의 DC
			destX,					//복사될 좌표 X
			destY,					//복사될 좌표 Y
			sourWidth,				//복사될 가로크기
			sourHeight,				//복사될 세로크기
			_imageInfo->hMemDC,		//복사할 DC
			sourX, sourY,			//복사해올 좌표
			sourWidth,				//복사해올 크기
			sourHeight,
			_transColor);			//제외할 컬러값
	}
	else
	{
		//백버퍼에 영역을 HDC영역으로 고속복사 해준다
		BitBlt(hdc, destX, destY,
			sourWidth,
			sourHeight,
			_imageInfo->hMemDC,
			sourX, sourY,
			SRCCOPY);
	}
}

//   프레임렌더   뿌릴DC영역  좌표 X   좌표 Y (left Top)
void image::frameRender(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(hdc,
			destX,
			destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor);
	}
	else
	{
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}

}

//   프레임 렌더  뿌릴DC영역  좌표 X    좌표 Y (left, top) 프레임 번호 X  프레임번호 Y
void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_trans)
	{
		GdiTransparentBlt(hdc,
			destX,
			destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor);
	}
	else
	{
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}

void image::alphaRender(HDC hdc, BYTE alpha)
{
	//알파를 적용할 수치를 받는다
	_blendFunc.SourceConstantAlpha = alpha;

	if ( _trans )
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, _imageInfo->x, _imageInfo->y, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);

		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width,
			_imageInfo->height, _blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width,
			_imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}

}

void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	//알파를 적용할 수치를 받는다
	_blendFunc.SourceConstantAlpha = alpha;

	if ( _trans )
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);

		AlphaBlend(hdc, destX, destY, _imageInfo->width,
			_imageInfo->height, _blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY, _imageInfo->width,
			_imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void image::alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{

	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 
			0, 0, 
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			hdc, 
			destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC,
			0,
			0,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor);

		AlphaBlend(hdc, destX, destY, _imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_blendImage->hMemDC, 
			0, 0, 
			_imageInfo->frameWidth, _imageInfo->frameHeight,
			_blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY, _imageInfo->width,
			_imageInfo->height, _blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}

}
