#include<iostream>
#include<vector>
#include<list>
#include<map>

#include"storage.h"

template<typename Cont, typename Item>
class DataExtractor_Base {
protected:
	Storage<Item> m_sto;

public:
	DataExtractor_Base() {}

	void extractData(const Cont& co) {
		for (auto i : co) {
			m_sto.add(i);
		}
	}

	size_t size() const {
		return m_sto.size();
	}
	
	void listData() {
		for (typename Storage<Item>::Marker m = m_sto.createMarker(); m.isValid(); m.next()) {
			std::cout << m.getValue() << ' ';
		}
		std::cout << std::endl;
	}

};

template<typename Cont, typename Item>
class DataExtractor:public DataExtractor_Base<Cont,Item> {
public:
	DataExtractor() {}
};

template<typename Key, typename Item>
class DataExtractor<std::map<Key, Item>, Item>: public DataExtractor_Base<std::map<Key, Item>, Item> {
public:
	DataExtractor() {}

	void extractData(const std::map<Key, Item>& m) {
		for (auto i : m) {
			this->m_sto.add(i.second);
		}
	}

};

template<typename Cont, typename Item>
class DataExtractor<Cont, Item*> : public DataExtractor_Base<Cont, Item> {
public:
	void extractData(const Cont& co) {
		for (auto i : co) {
			this->m_sto.add(*i);
		}
	}

};

bool testDataExtr() {

	std::vector<double> vd{ 1,2,3,4,5 };
	DataExtractor<std::vector<double>, double> sample1;
	sample1.extractData(vd);
	sample1.listData();
	if (sample1.size() != 5) return false;
	
	std::map<double, int> mp{ {1.1,1}, {2.2,2}, {3.3,3} };
	DataExtractor<std::map<double, int>, int> sample2;
	sample2.extractData(mp);
	sample2.listData();
	if (sample2.size() != 3) return false;
	
	std::vector<int*> vp;
	for (int k = 1; k < 6; k++) {
		int* p = new int;
		*p = k;
		vp.push_back(p);
	}
	DataExtractor<std::vector<int*>, int*> sample3;
	sample3.extractData(vp);
	sample3.listData();
	if (sample3.size() != 5) {
		for (auto i : vp) {
			delete i;
		}
		return false;
	}
	for (auto i : vp) {
		delete i;
	}
	
	return true;
}


int main() {

	std::cout << (testDataExtr() ? "passed" : "failed") << std::endl;

	return 0;
}