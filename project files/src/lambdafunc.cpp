#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <functional>
#include <algorithm>

//отсортировать по удалённости от точки другие точки с помощью лямбда-функции
int main() {
	std::vector<std::pair<double, double>> vd{ {3,3}, {1,1}, {2,2} }; 
	std::pair<double, double> point{0,0};

	std::function<bool(std::pair<double, double>, std::pair<double, double>)> f;
	f = [&point](std::pair<double, double> p1, std::pair<double, double> p2) {
		return pow(p1.first - point.first, 2) + pow(p1.second - point.second, 2) < pow(p2.first - point.first, 2) + pow(p2.second - point.second, 2);
	};

	std::sort(vd.begin(), vd.end(), f);

	for (auto i : vd) {
		std::cout << i.first << ' ' << i.second << std::endl;
	}
}