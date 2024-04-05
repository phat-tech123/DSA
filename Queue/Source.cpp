#include <iostream>
#include<queue>

int main() {
	int n; std::cin >> n;
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
			//return tmp + num.front();
			break;
		}
		else {
			num.push(tmp + num.front());
			num.pop();
		}
		//second time
		++cnt;
		if (cnt == n) {
			//return tmp + num.front();
			break;
		}
		else {
			num.push(tmp + num.front());
		}
	}
	std::cout << tmp + num.front();
}