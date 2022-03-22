#pragma once
#include <string>
#include <vector>

#include "Color.h"
#include "Vec2.h"
#include "Node.h"




class Shape2D : public Node{
public:
	vector<Vec2> points; //y������Ϊ˳ʱ�룬��֮Ϊ��ʱ��
	//vector<Vec2> realpoints; //δ���仯��
		//Vec2 position;
	int point_num;
public:
	Shape2D(vector<Vec2> points = vector<Vec2>()) :points(points) ,point_num(points.size()) {};
	virtual string getShapeType() { return "Shape"; };
	virtual string getNodeType() { return "Shape"; };
	
};