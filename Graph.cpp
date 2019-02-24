#include "Graph.h"
#include <vector>
#include <list>
#include <cstring>
#include <queue>
#include <iostream>

void Graph::AddEdgeList(int from, int to) {
	//AdjList的型態是vector
	AdjList[from].push_back(to);
}

void Graph::BFS(int _Start) {
		
	std::cout << "declare variable" << std::endl;
	// color is used to record whether we have walked through the node or not
	color = new TraceRecord[num_vertex];

	predecessor = new int[num_vertex];
	
	distance = new int[num_vertex];
	
	std::cout << "initialization begins" << std::endl;
	for (int i = 0; i < num_vertex; i++) {  // 初始化，如圖二(b)
		color[i] = white;                       // 0:白色;
		predecessor[i] = -1;                // -1表示沒有predecessor
		distance[i] = num_vertex + 1;         // num_vertex個vertex, 
	}                                       // 最長距離 distance = num_vertex -1條edge
	std::cout << "initialization ends" << std::endl;

	// queue is used to record whether the node has been passed
	std::queue<int> q;
	int i = _Start;

	std::cout << "search start" << std::endl;
	// j從0數到num_vertex-1, 因此j會走過graph中所有vertex
	// 因為我們不能保證圖一定是connected graph, 
	// 所以要全部都trace過
	for (int j = 0; j < num_vertex; j++) {	
		if (color[i] == white) {
			// 第一次i會是起點vertex, 所以塗成grey
			color[i] = gray;
			// 每一個connected component的起點之距離設成0
			distance[i] = 0;
			// 每一個connected component的起點沒有predecessor
			predecessor[i] = -1;
			//把起始點放到queue之中
			q.push(i);
			while (!q.empty()) {
				// u為新的搜尋起點
				int u = q.front();
				std::cout << "the search start point is " << (char)(u+65) << std::endl;
				int itrCount = 0;
				// 開始對connected component 做BFS
				for (std::list<int>::iterator itr = AdjList[u].begin();itr != AdjList[u].end(); itr++) {
					// 若被「找到」的vertex是白色
					if (color[*itr] == white) {
						// 塗成灰色, 表示已經被「找到」
						color[*itr] = gray;
						std::cout << "the searched element is " << (char)(*itr+65)  << ", the state is "<< color[*itr] << std::endl;
						// 距離是predecessor之距離加1
						distance[*itr] = distance[u] + 1;
						// 更新被「找到」的vertex的predecessor
						predecessor[*itr] = u;
						// 把vertex推進queue
						q.push(*itr);
					}
					itrCount++;
				}
				// 把u移出queue
				q.pop();
				color[u] = black;
			}
		}
		// 若一次回圈沒有把所有vertex走過, 表示graph有多個connected component
	   // 就把i另成j, 繼續檢查graph中的其他vertex是否仍是白色, 若是, 重複while loop
		i = j;
	}
	std::cout << "search ends" << std::endl;
}
Graph::~Graph(){}

void Graph::DFS(int _Start){
	color = new TraceRecord[num_vertex];           // 配置記憶體位置
    discover = new int[num_vertex];
    finish = new int[num_vertex];
    predecessor = new int[num_vertex];

	/********initialize parameter***********/
	int time = 0;
	for (int i = 0; i < num_vertex; i++) { 
        color[i] = white;
        discover[i] = 0;
        finish[i] = 0;
        predecessor[i] = -1;
    }
	int i = _Start;


	/********start traverse********/
	// this for loop is to check all point since the graph may have multiple components
	for (int j = 0; j < num_vertex; j++) { // 檢查所有Graph中的vertex都要被搜尋到
        if (color[i] == white) {               // 若vertex不是白色, 則進行以該vertex作為起點之搜尋
            DFSVisit(i, time);
        }
        i = j;                             // j會把AdjList完整走過一遍, 確保所有vertex都被搜尋過
    }
	/******************************/
}
void Graph::DFSVisit(int vertex, int &time){
	color[vertex] = gray;
	discover[vertex] = ++time;
	for (std::list<int>::iterator itr = AdjList[vertex].begin(); itr != AdjList[vertex].end(); itr++) 
	{
		if (color[*itr] == white) {                // 若搜尋到白色的vertex
            predecessor[*itr] = vertex;        // 更新其predecessor
			// Recursive call
            DFSVisit(*itr, time);              // 立刻以其作為新的搜尋起點, 進入新的DFSVisit()
        }
	}
	color[vertex] = black;                         // 當vertex已經搜尋過所有與之相連的vertex後, 將其塗黑
    finish[vertex] = ++time;                   // 並更新finish時間
}