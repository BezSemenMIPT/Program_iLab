#include<iostream>
#include<vector>
#include "Header.h"
using namespace std;
using namespace Geometry;

template <typename T> struct Point { T x, y; };
template <typename U> struct Triangle {
	Point<U> pts[3];
};

float x_intersect(Point<float> p1, Point<float> p2, Point<float> p3, Point<float> p4) {
	float num = (p1.x * p2.y - p1.y * p2.x) * (p3.x - p4.x) - (p1.x - p2.x) * (p3.x * p4.y - p3.y * p4.x);
	float den = (p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x);
	return num / den;
}

float y_intersect(Point<float> p1, Point<float> p2, Point<float> p3, Point<float> p4) {
	float num = (p1.x * p2.y - p1.y * p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x * p4.y - p3.y * p4.x);
	float den = (p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x);
	return num / den;
}

void clip(vector<Point<float>> &lhs, Point<float> p1_cl, Point<float> p2_cl) {
	vector<Point<float>> temp(6);
	int new_poly_size = 0;
	for (int i = 0; i < lhs.size(); i++)
	{
		int k = (i + 1) % lhs.size();
		float i_pos = (p2_cl.x - p1_cl.x) * (lhs[i].y - p1_cl.y) - (p2_cl.y - p1_cl.y) * (lhs[i].x - p1_cl.x);
		float k_pos = (p2_cl.x - p1_cl.x) * (lhs[k].y - p1_cl.y) - (p2_cl.y - p1_cl.y) * (lhs[k].x - p1_cl.x);
		if (i_pos > 0 && k_pos > 0) continue;
		if (i_pos < 0 && k_pos < 0)
		{
			temp[new_poly_size].x = lhs[k].x;
			temp[new_poly_size].y = lhs[k].y;
			new_poly_size++;
		}
		else if (k_pos == 0) {
			temp[new_poly_size].x = lhs[k].x;
			temp[new_poly_size].y = lhs[k].y;
			new_poly_size++;
		}
	    else if (k_pos < 0)
		{
			if (i_pos != 0) {
				temp[new_poly_size].x = x_intersect(p1_cl, p2_cl, lhs[i], lhs[k]);
				temp[new_poly_size].y = y_intersect(p1_cl, p2_cl, lhs[i], lhs[k]);
				new_poly_size++;
				temp[new_poly_size].x = lhs[k].x;
				temp[new_poly_size].y = lhs[k].y;
				new_poly_size++;
			}
			else {
				temp[new_poly_size].x = lhs[k].x;
				temp[new_poly_size].y = lhs[k].y;
				new_poly_size++;
			}
		}
		else if (k_pos > 0)
		{
			if (i_pos == 0) {
				temp[new_poly_size].x = lhs[i].x;
				temp[new_poly_size].y = lhs[i].y;
				new_poly_size++;
			}
			else {
				temp[new_poly_size].x = x_intersect(p1_cl, p2_cl, lhs[i], lhs[k]);
				temp[new_poly_size].y = y_intersect(p1_cl, p2_cl, lhs[i], lhs[k]);
				new_poly_size++;
			}
		}
	}
	if (lhs.size() < new_poly_size) lhs.resize(new_poly_size);
	for (int i = 0; i < new_poly_size; i++)
	{
		lhs[i].x = temp[i].x;
		lhs[i].y = temp[i].y;
		//cout << '(' << lhs[i].x << ", " << lhs[i].y << ") ";
	}
	//cout << endl;
}

void suthHodgClip(vector<Point<float>> &lhs, const Triangle<float> &rhs) {
	for (int i = 0; i < 3; i++) {
		int k = (i + 1) % 3;
		clip(lhs, rhs.pts[i], rhs.pts[k]);
	}
	// Printing vertices of clipped polygon 
#if 0
	for (int i = 0; i < lhs.size(); i++)
		cout << '(' << lhs[i].x << ", " << lhs[i].y << ") ";
#endif
}

float calcul(Point<float> p1, Point<float> p2) {
	return (p1.x + p2.x) * (p1.y - p2.y);
}

float intersection_area(const Triangle<float> &lhs, const Triangle<float> &rhs) {
	vector<Point<float>> tmp(3);
	for (int i = 0; i < 3; i++) {
		tmp[i].x = lhs.pts[i].x;
		tmp[i].y = lhs.pts[i].y;
	}
	suthHodgClip(tmp, rhs);
	float ans = 0.0;
	for (int i = 0; i < (int)tmp.size(); i++) {
		ans += calcul(tmp[i], tmp[(i + 1) % tmp.size()]);
	}
	return (ans >= 0) ? ans / 2 : (-1 * ans) / 2;
}

//order clipper in clockwise
void clock_ord(Triangle<float> &rhs) {
	Point<float> temp;
	if (rhs.pts[0].x >= rhs.pts[2].x && rhs.pts[0].x >= rhs.pts[1].x &&
	rhs.pts[1].x >= rhs.pts[2].x && rhs.pts[1].y >= rhs.pts[2].y &&
	rhs.pts[0].y <= rhs.pts[1].y) {
		temp = rhs.pts[1];
		rhs.pts[1] = rhs.pts[2];
		rhs.pts[2] = temp;
	}
	else if (rhs.pts[2].x >= rhs.pts[1].x && rhs.pts[2].x >= rhs.pts[0].x &&
		rhs.pts[0].x >= rhs.pts[1].x && rhs.pts[0].y >= rhs.pts[1].y &&
		rhs.pts[2].y <= rhs.pts[0].y) {
		temp = rhs.pts[0];
		rhs.pts[0] = rhs.pts[2];
		rhs.pts[2] = temp;
	}
	else if (rhs.pts[2].x >= rhs.pts[0].x && rhs.pts[2].x >= rhs.pts[1].x &&
		rhs.pts[1].x >= rhs.pts[0].x && rhs.pts[1].y >= rhs.pts[0].y &&
		rhs.pts[2].y <= rhs.pts[1].y) {
		temp = rhs.pts[0];
		rhs.pts[0] = rhs.pts[2];
		rhs.pts[2] = temp;
		temp = rhs.pts[1];
		rhs.pts[1] = rhs.pts[2];
		rhs.pts[2] = temp;
	}
	else if (rhs.pts[1].x >= rhs.pts[2].x && rhs.pts[1].x >= rhs.pts[0].x &&
		rhs.pts[2].x >= rhs.pts[0].x && rhs.pts[2].y >= rhs.pts[0].y &&
		rhs.pts[1].y <= rhs.pts[2].y) {
		temp = rhs.pts[0];
		rhs.pts[0] = rhs.pts[1];
		rhs.pts[1] = temp;
	}
	else if (rhs.pts[1].x >= rhs.pts[2].x && rhs.pts[1].x >= rhs.pts[0].x &&
		rhs.pts[0].x >= rhs.pts[2].x && rhs.pts[0].y >= rhs.pts[2].y &&
		rhs.pts[1].y <= rhs.pts[0].y) {
		temp = rhs.pts[0];
		rhs.pts[0] = rhs.pts[1];
		rhs.pts[1] = temp;
		temp = rhs.pts[1];
		rhs.pts[1] = rhs.pts[2];
		rhs.pts[2] = temp;
	}
}




int main() {
	Triangle<float> rhs;
	cin >> rhs.pts[0].x >> rhs.pts[0].y;
	cin >> rhs.pts[1].x >> rhs.pts[1].y;
	cin >> rhs.pts[2].x >> rhs.pts[2].y;
	Triangle<float> lhs;
	cin >> lhs.pts[0].x >> lhs.pts[0].y;
	cin >> lhs.pts[1].x >> lhs.pts[1].y;
	cin >> lhs.pts[2].x >> lhs.pts[2].y;
	clock_ord(rhs);
	float ans = intersection_area(lhs, rhs);
	cout << "Answer: " << ans << endl;
}
