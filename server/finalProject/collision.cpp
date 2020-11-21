#include "stdafx.h"
#include "collision.h"

/*
bool isCollisionReaction(const RECT rcHold, const RECT rcMove)
{
	RECT rcInter;

	if (!IntersectRect(&rcInter, rcHold, rcMove)) return false;

	int interSectorW = rcInter.right - rcInter.left;
	int interSectorH = rcInter.bottom - rcInter.top;

	////수직으로 부딪혔다면
	//if (interSectorW > interSectorH)
	//{
	//	//위에서 박았으면
	//	if (rcInter.top == rcHold.top)
	//	{
	//		//그만큼 밀어내라
	//		OffsetRect(&rcMove, 0, -interSectorH);
	//	}
	//	else if (rcInter.bottom == rcHold.bottom)
	//	{
	//		OffsetRect(&rcMove, 0, interSectorH);
	//	}
	//}
	//else//수평으로 박았다면
	//{
	//	//위에서 박았으면
	//	if (rcInter.left == rcHold.left)
	//	{
	//		//그만큼 밀어내라
	//		OffsetRect(&rcMove, -interSectorW, 0);
	//	}
	//	else if (rcInter.right == rcHold.right)
	//	{
	//		OffsetRect(&rcMove, interSectorW, 0);
	//	}
	//}

	return true;
}
*/
bool HEXA_UTIL::isCollisionReaction(const RECT rcHold, const RECT rcMove)
{
	RECT rcInter;
	if (!IntersectRect(&rcInter, &rcHold, &rcMove)) return false;
	return true;
}
