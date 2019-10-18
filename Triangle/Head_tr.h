#pragma once
//My algorithm names as Sutherland–Hodgman Algorithm:
//The edge(of clipping area) is extended infinitely to create
//a boundary and all the vertices are clipped using this boundary.
//The new list of vertices generated is passed to the next edge of
//the clip polygon in clockwise fashion until all the edges have been used.

namespace Geometry {
	float x_intersect();
	float y_intersect();
	void clip();
	void suthHodgClip();
	float calcul();
	float intersection_area();
	void clock_ord();
};









