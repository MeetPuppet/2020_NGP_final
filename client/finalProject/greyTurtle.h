#pragma once
#include "enemyNode.h"
class greyTurtle :
	public enemyNode
{
public:
	greyTurtle();
	~greyTurtle();

	// ���� ���� ��ġ
	HRESULT init(POINT point);
	void release();
	void update();
	void render();
	void FrameSeter() override;

	//�÷��̾� �Ҵ��� ������ ��� ������ ���� ��
	void AI(POINT* playerPoint = NULL);

	POINT* getTarget() { return enemyNode::getTarget(); }
	void LinkToTarget(POINT* playerPoint = NULL) {
		targetPoint = playerPoint;
	}
};

