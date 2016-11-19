#pragma once
#include "Node.h"

template<class DataType>
class Vertex
{
public:
	Vertex() { firstEdge = NULL; }
	~Vertex() {}
	DataType data;
	Node *firstEdge;
};

