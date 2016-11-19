#pragma once

class Node
{
public:
	Node(int index, int weight, Node*next) :index(index), weight(weight), next(next) {}
	~Node() {}
	int index;
	int weight;
	Node *next;
};

