#include "a1.h"

using namespace std;
AsPath::AsPath()
{
	neighbors.resize(1);
}
int AsPath::getsize()
{	return (neighbors.size() -1);	}
void AsPath::AddNeighbor(int x)
{
	auto i = find(neighbors.begin(), neighbors.end(), x);
	if (i == neighbors.end())
	{
		neighbors[neighbors.size()-1] = x;
		neighbors.resize(neighbors.size()+1);
	}

}
void AsPath::Print()
{
	sort (neighbors.begin(), neighbors.end());
	for ( int i = 1; i < neighbors.size(); i++)
	{
		if (neighbors.size() < 3)
			cout << neighbors[i];
		else
			cout << neighbors[i] << '|';
	}
}
