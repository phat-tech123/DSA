#include"Queue.h"

void interleaveQueue(std::queue<int>& q) {
	int halfsize = q.size() / 2;
	std::queue<int> firstHalf,seconHalf;
	for (int i = 0; i < halfsize; i++) {
		firstHalf.push(q.front());
		q.pop();
	}
	for (int i = 0; i < halfsize; i++) {
		seconHalf.push(q.front());
		q.pop();
	}
	for (int i = 0; i < halfsize; i++) {
		q.push(firstHalf.front());
		firstHalf.pop();
		q.push(seconHalf.front());
		seconHalf.pop();
	}
}

bool isBipartite(std::vector<std::vector<int>> graph){}

long long nthNiceNumber(int n) {
	if (n == 1) return 2;
	if (n == 2) return 5;
	std::queue<long long> num;
	num.push(2);
	num.push(5);
	int cnt = 2;
	long long tmp;
	while (cnt < n) {
		tmp = num.front() * 10;
		//first time
		++cnt;
		if (cnt == n) {
			tmp += 2;
			break;
		}
		else {
			num.push(tmp + 2);
			num.pop();
		}
		//second time
		++cnt;
		if (cnt == n) {
			tmp += 5;
			break;
		}
		else {
			num.push(tmp + 5);
		}
	}
	return tmp;
}

void bfs(std::vector<std::vector<int>> graph, int start) {
	std::vector<int> result;
	std::queue<std::pair<int, int>> q;
	for (int i = 0; i < graph.size(); i++) {
		for (int j = 0; j < graph.size(); j++) {
			
		}
	}

}
