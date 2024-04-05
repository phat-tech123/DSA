#ifndef QUEUE
#define QUEUE_H

#include <iostream>
#include<queue>
#include<vector>


void interleaveQueue(std::queue<int>& q);

bool isBipartite(std::vector<std::vector<int>> graph);

long long nthNiceNumber(int n);

void bfs(std::vector<std::vector<int>> graph, int start);
#endif //QUEUE_H