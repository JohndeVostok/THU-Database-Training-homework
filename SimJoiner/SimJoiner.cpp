#include "SimJoiner.h"
#include <fstream>
#include <sstream>
#include <cstdio>

using namespace std;

SimJoiner::SimJoiner() {
}

SimJoiner::~SimJoiner() {
}

int loadData(vector <string> &res, const string &filename) {
	res.clear();
	ifstream fin(filename.c_str());
	char buf[2050];
	while (fin.getline(buf, 2048)) res.emplace_back(buf);
	return SUCCESS;
}

int SimJoiner::joinJaccard(const char *filename1, const char *filename2, double threshold, vector<JaccardJoinResult> &result) {
    result.clear();
    return SUCCESS;
}

int SimJoiner::joinED(const char *filename1, const char *filename2, unsigned threshold, vector<EDJoinResult> &result) {
    result.clear();
    vector <string> data1, data2;
    loadData(data1, filename1);
    loadData(data2, filename2);

	vector <vector <unordered_map <string, vector <unsigned>>>> filter;
	int len = 0, spc = threshold + 1;
	for (const auto &str : data2) {
		if (str.length() > len) len = str.length();
	}
	filter.resize(len + 1);
	for (auto &i : filter) {
		i.resize(spc);
	}

	vector <pair <unsigned, unsigned>> tmpRes;
	vector <unsigned> tmpFlag(data2.size(), 0);

	for (int i = 0; i < data2.size(); i++) {
		int len = data2[i].length();
		for (int j = 0; j < spc; j++)
		{
			int l = len / spc + (j + len % spc < num_spc ? 0 : 1);
			auto substr = data2[i].substr(pos, l);
			if (!filter[l][j].count(substr)) {
				filter[l][j][substr] = vector <unsigned>(1, i);
			}
			else filter[l][j][substr1].push_back(i);
			pos += l;
		}
	}

	
    
    return SUCCESS;
}
