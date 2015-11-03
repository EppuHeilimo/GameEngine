#include "Octree.h"


template <class T>
Octree<T>::Octree()
{

}

template<class T>
Octree<T>::Octree(int width, glm::vec3 position)
{
	cRootCube = Cube(width, position, this->data);
	cRootCube.subdivide(this->iMinTriangles, this->data);
}

template <class T>
Octree<T>::~Octree()
{

}

template<class T>
void Octree<T>::erase()
{
}

template<class T>
void Octree<T>::del(T data, glm::vec3 pos)
{
}

template<class T>
void Octree<T>::insert(T* data, glm::vec3 pos)
{
	this->data.push_back(Node(pos, data));
}

template<class T>
void Octree<T>::del()
{

}

template<class T>
void Octree<T>::insert()
{
	
}

template<class T>
void Octree<T>::move(glm::vec3 from, glm::vec3 to)
{
}

template<class T>
void Octree<T>::recalculateBranch(glm::vec3 from, glm::vec3 to)
{
}


/* CLASS CUBE FUNCTION DEFINITIONS */

template <class T>
glm::vec3 Cube<T>::Cube::calculateNewCubeCenter(float width, int nodeID)
{
	glm::vec3 vCubeCenter(0, 0, 0);
	switch (nodeID)
	{
	case TOP_LEFT_FRONT:
		// Calculate the center of this new node
		vCubeCenter = glm::vec3(this->vCenter.x - width / 4, this->vCenter.y + width / 4, this->vCenter.z + width / 4);
		break;

	case TOP_LEFT_BACK:
		// Calculate the center of this new node
		vCubeCenter = glm::vec3(this->vCenter.x - width / 4, this->vCenter.y + width / 4, this->vCenter.z - width / 4);
		break;

	case TOP_RIGHT_BACK:
		// Calculate the center of this new node
		vCubeCenter = glm::vec3(this->vCenter.x + width / 4, this->vCenter.y + width / 4, this->vCenter.z - width / 4);
		break;

	case TOP_RIGHT_FRONT:
		// Calculate the center of this new node
		vCubeCenter = glm::vec3(this->vCenter.x + width / 4, this->vCenter.y + width / 4, this->vCenter.z + width / 4);
		break;

	case BOTTOM_LEFT_FRONT:
		// Calculate the center of this new node
		vCubeCenter = glm::vec3(this->vCenter.x - width / 4, this->vCenter.y - width / 4, this->vCenter.z + width / 4);
		break;

	case BOTTOM_LEFT_BACK:
		// Calculate the center of this new node
		vCubeCenter = glm::vec3(this->vCenter.x - width / 4, this->vCenter.y - width / 4, this->vCenter.z - width / 4);
		break;

	case BOTTOM_RIGHT_BACK:
		// Calculate the center of this new node
		vCubeCenter = glm::vec3(this->vCenter.x + width / 4, this->vCenter.y - width / 4, this->vCenter.z - width / 4);
		break;

	case BOTTOM_RIGHT_FRONT:
		// Calculate the center of this new node
		vCubeCenter = glm::vec3(this->vCenter.x + width / 4, this->vCenter.y - width / 4, this->vCenter.z + width / 4);
		break;
	}
	return vCubeCenter;
}

template<class T>
void Cube<T>::subdivide(int minTriangles)
{
	if (data.size() < 1)
		return;

	for (int i = 0; i < 8; i++) {
		glm::vec3 center = calculateNewCubeCenter(this->iWidth, i);
		children[i] = Cube(iWidth / 2, center);
		children[i].subdivide(minTriangles);
	}
	
}
