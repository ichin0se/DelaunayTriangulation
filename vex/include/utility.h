/*
 * Produced by:
 *	Keito Kurata
 *	22AU0139
 *	Graduate School of Computer Graphics
 *	Japan Electronics College
 *
 * NAME:	utility.h ( VEX Library Functions / VEX )
 *
 * COMMENTS:	Utility functions for Delaunay Triangulation.
 *
 */



 //	Verify if edge is illegal.
function int is_illegal(EDGE e; int pivotPoint, checkPoint) {

	//	Define circumscribed circle.
	int hedge = pointhedge(0, e.first, e.second);
	int prim = hedge_prim(0, hedge);
	int points[] = primpoints(0, prim);
	//*/
	if(find(points, pivotPoint) < 0) {
		hedge = hedge_nextequiv(0, hedge);
		prim = hedge_prim(0, hedge);
		points = primpoints(0, prim);
	}
//*/
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

	//	Check if the point is inside the circumscribed circle.
	string condition = "@ptnum == " + itoa(checkPoint);
	int nearpoint = nearpoint(0, condition, centerPos, radius);
	int ilegal_flg = nearpoint == -1 ? 0 : 1;

	//	For visualize.
	setdetailattrib(0, "centerPos", centerPos, "set");
	setdetailattrib(0, "radius", radius, "set");
	//setdetailattrib(0, "nearpoint", nearpoint, "set");

	return ilegal_flg;

}


//	Search for points contained in primitives that are not contained in edges.
function int findOppositePoint(int primNum; EDGE e) {

	int points[] = primpoints(0, primNum);
	int oppositePoint = points[0] + points[1] + points[2] - e.first - e.second;
	return oppositePoint;

}


//	Search for primitives that share edges with primitives.
function int findOppositePrim(int primNum; EDGE e) {

	int hedge = pointhedge(0, e.first, e.second);
	hedge = hedge_prim(0, hedge) == primNum ? hedge_nextequiv(0, hedge) : hedge;
	int oppositePrim = hedge_prim(0, hedge);

	return oppositePrim;

}


//	Flip edges shared by two primitives.
function void flipEdge(EDGE e; int pointA, pointB) {

	int hedge = pointhedge(0, e->first(), e->second());
	int prim = hedge_prim(0, hedge);
	removeprim(0, prim, 0);
	hedge = hedge_nextequiv(0, hedge);
	prim = hedge_prim(0, hedge);
	removeprim(0, prim, 0);

	int prim1 = addprim(0, "poly", pointA, e->first(), pointB);
	int prim2 = addprim(0, "poly", pointB, e->second(), pointA);
	setprimattrib(0, "Cd", prim1, {1, 1, 0}, "set");
	setprimattrib(0, "Cd", prim2, {1, 1, 0}, "set");

}
