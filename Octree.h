/*Octree - oct = eight*/
/**/
/**/
/**/

#pragma once
#include <vector>
#include <iostream>
#include <glm\glm.hpp>
template <class T>
class Node {
	Node(glm::vec3 position, T data) { this->position = position; this->data = &data; }
	~Node() {}
	T* data;
	glm::vec3 position;
};

template <class T>
class Cube {
public:
	Cube(int width, glm::vec3& center, std::vector<T>& data) { 
		this->iWidth = width; 
		iSize = width * width * width; 
		vCenter = center;
		this->data = data;
	}
	~Cube() {}
	void subdivide(int minTriangles);
	int getWidth() { return iWidth; }
private:
	glm::vec3 calculateNewCubeCenter(float width, int nodeID);
	
	int iWidth;
	glm::vec3 vCenter;
	std::vector<Node<T>> data;
	int iSize;
	bool bHasChildren = false;
	Cube children[8];

};




enum CubeID {
	TOP_LEFT_FRONT = 0, TOP_LEFT_BACK,
	TOP_RIGHT_FRONT, TOP_RIGHT_BACK,
	BOTTOM_LEFT_FRONT, BOTTOM_LEFT_BACK,
	BOTTOM_RIGHT_FRONT, BOTTOM_RIGHT_BACK
};

template <class T>
class Octree
{
public:

	Octree();
	Octree(int width, glm::vec3 position);
	~Octree();
	void erase();
	void del(T data, glm::vec3 pos);
	void insert(T* data, glm::vec3 pos);
	void move(glm::vec3 from, glm::vec3 to);

private:

	void recalculateBranch(glm::vec3 from, glm::vec3 to);
	Cube cRootCube; /* World Cube surrounds the whole world */
	const int iMinTriangles = 100;
	std::vector<Node<T>> data;


};


