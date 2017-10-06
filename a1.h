#include <iostream> 
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>
#include <unordered_map>
using namespace std;

class AsPath
{
public:
	AsPath();
	int getsize();
	void AddNeighbor(int x);
	void Print();
private:
	int as;
	vector<int> neighbors;
};
