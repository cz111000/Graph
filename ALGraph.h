#pragma once
#include "Vertex.h"

template<class DataType>
class ALGraph
{
public:
	ALGraph();
	~ALGraph();
	void DFSTraverse(int index);
	void BFSTraverse(int index);
	void prim();
	void kruskal();
	void dijkstra(int index);
	void floyd(int from, int to);
private:
	Vertex<DataType> vertex[100];
	int vertexCount, edgeCount;
	void DFSTraverse(int index, bool visited[]);
	void BFSTraverse(int index, bool visited[]);
};