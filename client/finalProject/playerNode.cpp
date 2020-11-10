#include "stdafx.h"//�Ŵ����� ���⿡ �� ���������� �ʿ���
#include "playerNode.h"


#define WIDTH 560  //�̹��� ���α���
#define HEIGHT 320 //�̹��� ���α���


playerNode::playerNode()//�������� �������� �𸣴� �����ص�
{
	img = NULL;

	rc = { 0,0,0,0 };
	point = Point(0.f, 0.f);

	speed = 0.f;
	jumpPower = 0.2f;
	IFS = 0;
	IFF = 0;

	state = PS_IDLE;
	mode = PM_SMALL;

	frameX = 0;
	frameY = 0;
	frameCount = 0.2f;

	for (int i = 0; i < 2; ++i) {
		checkPos[i] = {0,0,0,0};
	}
}


playerNode::~playerNode()
{

}

HRESULT playerNode::init(image* IMG, Point p)
{			
	img = IMG;
	rc = RectMakeCenter(point.x, point.y, img->getFrameWidth(), img->getFrameHeight());
	foot = RectMakeCenter(point.x, rc.bottom, img->getFrameWidth()+10, 20);

	point = p;

	state = PS_JUMP;
	mode = PM_SMALL;

	speed = 0.f;
	jumpPower = 0.0f;
	frameX = 0;
	frameY = 0;
	frameCount = 0.2f;

	return S_OK;
}

void playerNode::update() 
{
	rc = RectMakeCenter(point.x, point.y, img->getFrameWidth(), img->getFrameHeight());
	foot = RectMakeCenter(point.x, rc.bottom, img->getFrameWidth() + 10, 20);
	time = TIMEMANAGER->getElapsedTime();
}

void playerNode::render() 
{
	img->frameRender(getMemDC(), rc.left, rc.top, frameX, frameY);

}
/*
void playerNode::keySet()
{
	//�̰� �÷��̾� ���� ���� ��
	switch (state)
	{
	case PS_IDLE:
		break;
	case PS_MOVE:
		break;
	case PS_BREAK:
		break;
	case PS_JUMP:
		break;
	case PS_SIT:
		break;
	}
}
*/