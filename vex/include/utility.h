function int is_ilegal(int primNum; int oppositePoint){
	/*
	Check if edge is ilegal.
	*/

	//define circumscribed circle.
	int points[] = primpoints(0, primNum);
	vector pos1 = point(0, "P", points[0]);
	vector pos2 = point(0, "P", points[1]);
	vector pos3 = point(0, "P", points[2]);

	float c = 2.0 * ((pos2.x - pos1.x) * (pos3.z - pos1.z) - (pos2.z - pos1.z) * (pos3.x - pos1.x));
	float x = ((pos3.z - pos1.z) * (pos2.x * pos2.x - pos1.x * pos1.x + pos2.z * pos2.z - pos1.z * pos1.z)
					+ (pos1.z - pos2.z) * (pos3.x * pos3.x - pos1.x * pos1.x + pos3.z * pos3.z - pos1.z * pos1.z))/c;
	float y = ((pos1.x - pos3.x) * (pos2.x * pos2.x - pos1.x * pos1.x + pos2.z * pos2.z - pos1.z * pos1.z)
					+ (pos2.x - pos1.x) * (pos3.x * pos3.x - pos1.x * pos1.x + pos3.z * pos3.z - pos1.z * pos1.z))/c;

	vector centerPos = set(x, 0, y);
	float radius = distance(centerPos, pos1);

	//Is the point inside the circumcircle?
	int nearpoint = nearpoint(0, "__tmp_checkPoint", centerPos, radius);
	int ilegal_flg = nearpoint == -1 ? 0 : 1;

	//for the test
	setdetailattrib(0, "centerPos", centerPos, "set");
	setdetailattrib(0, "radius", radius, "set");
	setdetailattrib(0, "nearpoint", nearpoint, "set");

	return ilegal_flg;
}


function int findOppositePoint(int primNum; EDGE e){
	/*
	Find points that are included in the prim "primNum" but not included in the edge "e".
	*/
	int points[] = primpoints(0, primNum);
	int oppositePoint = points[0] + points[1] + points[2] - e->first() - e->second();
	return oppositePoint;
}


function int findOppositePrim(int primNum; EDGE e){
	/*
	Find prims that share edge "e" included in the prim "primNum".
	*/
	int hedge = pointhedge(0, e->first(), e->second());
	hedge = hedge_prim(0, hedge) == primNum ? hedge_nextequiv(0, hedge) : hedge;
	int oppositePrim = hedge_prim(0, hedge);

	return oppositePrim;
}


function EDGE findFlipEdge(int primNum, targetPoint){
	/*
	Find an edge to flip,
	In other words, Find an edge that is included in prim "primNum" but does not include point "targetPoint"
	*/
	int hedge = primhedge(0, primNum);
	int srcPoint = hedge_srcpoint(0, hedge);
	int dstPoint = hedge_dstpoint(0, hedge);

	for(int i = 0; i < 2; i++){
		if(srcPoint == targetPoint || dstPoint == targetPoint){
			hedge = hedge_next(0, hedge);
		}else{
			break;
		}
	}
	srcPoint = hedge_srcpoint(0, hedge);
	dstPoint = hedge_dstpoint(0, hedge);

	EDGE edge;
	edge.first = srcPoint;
	edge.second = dstPoint;

	return edge;
}
