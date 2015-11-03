#pragma once

class RawModel
{
public:
	RawModel(int vaoID, int vertexCount);
	RawModel();
	~RawModel();
	int getVaoID(){
		return vaoID;
	}
	int getVertexCount(){
		return vertexCount;
	}
private:
	int vaoID;
	int vertexCount;
};

