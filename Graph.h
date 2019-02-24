#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <list>

class Graph{
public:
	// default constructor
	Graph() : num_vertex(0) { ; }

	// constructor with input: number of vertex
	Graph(int N) : num_vertex(N) {
		//調整vector size
		AdjList.resize(num_vertex);
	}
	void AddEdgeList(int, int);
	void BFS(int);
	void DFS(int);
	void DFSVisit(int , int &);
	~Graph();

private:
	typedef enum { white, gray, black } TraceRecord;
	// 宣告number of vertex
	int num_vertex; 
	//宣告adjacent list
	std::vector<std::list<int>> AdjList;
	//color 用來記錄node的狀態(可以用enum)
	// 0:white, 1:gray, 2:black
	TraceRecord* color;
	// 用來記錄該節點的predecessor, 
	// -1:沒有predecessor, 用來表示起點vertex
	int *predecessor;
	int *discover;
	int *finish;
	// 用來記錄vertext間的距離長度
	// 0:起點, 無限大:從起點走不到目標vertex
	int *distance;	
};
#endif