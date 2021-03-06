#include "SimJoiner.h"
#include <cstdio>

using namespace std;

int main(int argc, char **argv) {
    SimJoiner joiner;

    vector<EDJoinResult> resultED;
    vector<JaccardJoinResult> resultJaccard;

    unsigned edThreshold = 2;
    double jaccardThreshold = 0.5;

    joiner.joinJaccard(argv[1], argv[2], jaccardThreshold, resultJaccard);
    joiner.joinED(argv[1], argv[2], edThreshold, resultED);

	for (const auto &i : resultED) {
		printf("%d %d %d\n", i.id1, i.id2, i.s);
	}

    return 0;
}
