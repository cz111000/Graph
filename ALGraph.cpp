#include "ALGraph.h"
#include <iostream>
#include <string>
using namespace std;

template<class DataType>
ALGraph<DataType>::ALGraph()
{
	cin >> vertexCount >> edgeCount;
	for (int i = 0;i < vertexCount;i++)
		cin >> vertex[i].data;
	int x, y, weight;
	for (int i = 0;i < edgeCount;i++)
	{
		cin >> x >> y;
		cin >> weight;
		vertex[x].firstEdge = new Node(y, weight, vertex[x].firstEdge);
	}
}

template<class DataType>
ALGraph<DataType>::~ALGraph()
{
	Node *p = NULL;
	for (int i = 0;i < vertexCount;i++)
		while (vertex[i].firstEdge)
		{
			p = vertex[i].firstEdge;
			vertex[i].firstEdge = vertex[i].firstEdge->next;
			delete p;
		}
}

template<class DataType>
void ALGraph<DataType>::DFSTraverse(int index)
{
	bool visited[100] = { false };
	DFSTraverse(index, visited);
	cout << endl;
}

template<class DataType>
void ALGraph<DataType>::BFSTraverse(int index)
{
	bool visited[100] = { false };
	BFSTraverse(index, visited);
	cout << endl;
}

template<class DataType>
void ALGraph<DataType>::prim()
{
	int index = 0;
	bool visited[100] = { false };
	int stack[100];
	int top = -1;
	int maxFrom;
	Node *p = NULL;
	Node *maxIndex = NULL;
	while (top + 2 != vertexCount)
	{
		stack[++top] = index;
		maxIndex = NULL;
		for (int i = 0;i <= top;i++)
		{
			index = stack[i];
			p = vertex[index].firstEdge;
			while (p)
			{
				if (!maxIndex || p->weight < maxIndex->weight)
					if (!visited[p->index])
					{
						maxIndex = p;
						maxFrom = index;
					}
				p = p->next;
			}
		}
		cout << vertex[maxFrom].data << "<->" << vertex[maxIndex->index].data << endl;
		visited[maxFrom] = true;
		visited[maxIndex->index] = true;
		index = maxIndex->index;
	}
}

template<class DataType>
void ALGraph<DataType>::kruskal()
{
	struct Edge
	{
		DataType to, from;
		int weight;
	};
	Edge edge[1000];
	int edgeNum = 0;
	Node *p = NULL;
	bool flag;
	for (int i = 0;i < vertexCount;i++)
	{
		p = vertex[i].firstEdge;
		while (p)
		{
			flag = false;
			for (int j = 0;j < edgeNum;j++)
				if (edge[j].from == i && edge[j].to == p->index)
					flag = true;
			if (!flag)
			{
				edge[edgeNum].to = i;
				edge[edgeNum].from = p->index;
				edge[edgeNum++].weight = p->weight;
			}
			p = p->next;
		}
	}
	Edge temp;
	for (int i = 0;i < edgeNum - 1;i++)
		for (int j = 0;j < edgeNum - 1 - i;j++)
			if (edge[j].weight > edge[j + 1].weight)
			{
				temp = edge[j];
				edge[j] = edge[j + 1];
				edge[j + 1] = temp;
			}
	//edge¹¹½¨Íê±Ï
	int parent[1000];
	for (int i = 0;i < vertexCount;i++)
		parent[i] = -1;
	int num = 0;
	int ver1, ver2;
	for (int i = 0;i < edgeCount;i++)
	{
		ver1 = parent[edge[i].to];
		if (ver1 == -1)
			ver1 = edge[i].to;
		else
			while (parent[ver1] != -1)
				ver1 = parent[ver1];
		ver2 = parent[edge[i].from];
		if (ver2 == -1)
			ver2 = edge[i].from;
		else
			while (parent[ver2] != -1)
				ver2 = parent[ver2];
		if (ver1 != ver2)
		{
			cout << vertex[edge[i].to].data << "<->" << vertex[edge[i].from].data << endl;
			parent[ver2] = ver1;
			num++;
			if (num + 1 == vertexCount)
				return;
		}
	}
}

template<class DataType>
void ALGraph<DataType>::dijkstra(int index)
{
	int dist[1000] = { 0 };
	string path[1000];
	char temp[10];
	int visitedCount = 0;
	Node *p = NULL;
	int min;
	p = vertex[index].firstEdge;
	while (p)
	{
		dist[p->index] = p->weight;
		_itoa_s(index, temp, 10);
		path[p->index] = "v" + string(temp);
		_itoa_s(p->index, temp, 10);
		path[p->index] += " -> v" + string(temp);
		p = p->next;
	}
	dist[index] = -1;
	while (visitedCount + 1 != vertexCount)
	{
		min = -1;
		for (int i = 0;i < vertexCount;i++)
			if (dist[i] != 0 && dist[i] != -1)
				if (min == -1 || dist[i] < dist[min])
					min = i;
		cout << path[min] << " weight:" << dist[min] << endl;
		visitedCount++;
		index = min;
		p = vertex[index].firstEdge;
		while (p)
		{
			if (dist[p->index] == 0 || dist[p->index] > dist[index] + p->weight)
			{
				dist[p->index] = dist[index] + p->weight;
				path[p->index] = path[index];
				_itoa_s(p->index, temp, 10);
				path[p->index] += " -> v" + string(temp);
			}
			p = p->next;
		}
		dist[index] = -1;
	}
}

template<class DataType>
void ALGraph<DataType>::floyd(int from, int to)
{
	int dist[100][100] = { 0 };
	Node *p = NULL;
	string path[100][100];
	char temp[10];
	for (int i = 0;i < vertexCount;i++)
	{
		p = vertex[i].firstEdge;
		while (p)
		{
			dist[i][p->index] = p->weight;
			_itoa_s(i, temp, 10);
			path[i][p->index] = "v" + string(temp);
			_itoa_s(p->index, temp, 10);
			path[i][p->index] += " -> v" + string(temp);
			p = p->next;
		}
	}
	for (int k = 0;k < vertexCount;k++)
		for (int i = 0;i < vertexCount;i++)
			for (int j = 0;j < vertexCount;j++)
				if (i != j && dist[i][k] != 0 && dist[k][j] != 0)
					if (dist[i][j] == 0 || dist[i][j] > dist[i][k] + dist[k][j])
					{
						dist[i][j] = dist[i][k] + dist[k][j];
						path[i][j] = path[i][k] + " -> " + path[k][j];
					}
	cout << path[from][to] << " weight:" << dist[from][to] << endl;
}

template<class DataType>
void ALGraph<DataType>::DFSTraverse(int index, bool visited[])
{
	if (index >= vertexCount)
		return;
	cout << vertex[index].data << " ";
	visited[index] = true;
	Node *p = vertex[index].firstEdge;
	while (p)
	{
		if (!visited[p->index])
			DFSTraverse(p->index, visited);
		p = p->next;
	}
}

template<class DataType>
void ALGraph<DataType>::BFSTraverse(int index, bool visited[])
{
	int queue[100];
	int rear, front;
	rear = front = -1;
	queue[++rear] = index;
	cout << vertex[index].data << " ";
	visited[index] = true;
	Node *p = NULL;
	while (front != rear)
	{
		index = queue[++front];
		p = vertex[index].firstEdge;
		while (p)
		{
			if (!visited[p->index])
			{
				queue[++rear] = p->index;
				cout << vertex[p->index].data << " ";
				visited[p->index] = true;
			}
			p = p->next;
		}
	}
}
