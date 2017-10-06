#include "a1.h"
using namespace std;



string extractb(string x);
void extractd(string x);
unordered_map <int, AsPath*> asmap;
multimap <int, int> asmap2;
int main()
{
	//initialize opening variables
	vector<string> aspath(1);
	string parser, temp;
	while (getline(cin, parser) != NULL) //pull first line
	{
		int position = 0;
		int count = parser.find('|');
		for (int i = 0; i < 7; i++) //loop to extract aspath
		{
			temp = parser.substr((position+1), (count-1));
			position += count;
			count = parser.find('|', (position+1))-position;
		}
		aspath[aspath.size()-1] = temp;
		aspath.resize(aspath.size()+1);
	}
	//now that we have info we need, must first remove ASSETS and duplicates.
	for (int i = 0; i < aspath.size(); i++)
	{
		//extract brackets, duplicates, add all elements to a map
		aspath[i] = extractb(aspath[i]);
		extractd(aspath[i]);
	}
		
	//make multimap
	for (auto it = asmap.begin(); it != asmap.end(); ++it)
		asmap2.insert(pair<int, int>(it->second ->getsize(), it-> first));


	//print
	for (auto it = asmap2.rbegin(); it != asmap2.rend(); ++it) 
	{
		auto i = asmap.find(it->second);
		cout << it -> second << " " << it -> first << " ";
		i->second->Print();
		cout << endl;
		cout << endl;
	}
	asmap2.clear();
	asmap.clear();
	return 0;
}

//function to extract ASSETs if any

string extractb(string x)
{
	int count = x.find('[');
	string temp = x.substr(0, (count-1));
	return temp;
}

void extractd(string x)
{
	vector<string> temp(1);
	vector<int> temp2(1);
	int count = x.find(' ');
	int position = 0;
	while (position < x.size())
	{
		//to eliminate a whitespace character being added to the string array
		if (position == 0)
			temp[temp.size()-1] = x.substr(position, count);
		else 
			temp[temp.size()-1] = x.substr(position+1, count-1);
			
		position +=count;
		count = x.find(' ', (position+1)) -position;
		temp.resize(temp.size()+1);
	}
	//this loop actually deletes duplicates if it finds any
	//
	for (auto i = temp.begin() + 1; i < temp.end() - 1; i++)
	{	
		if (*(i-1) == *i)
		{
			i--;
			temp.erase(i+1);
		}
	}
	// now that the temp string array is clean, convert to int array
	for (int i = 0; i < temp.size(); i++)
	{
		try
		{
			temp2[i] = stoi(temp[i]);
			temp2.resize(temp2.size()+1);
		}
		catch (const invalid_argument& e)
		{
			continue;
		}
		catch (const out_of_range& e)
		{	
			continue;
		}
	}
	//add every element to a map with its corresponding object being the key
	for (int i = 0; i < temp2.size()-1; i++)
	{
		auto it = asmap.find(temp2[i]);
		if (it == asmap.end())
			asmap[temp2[i]] = new AsPath();
		if (i == 0)
			asmap.find(temp2[i]) -> second -> AddNeighbor(temp2[i+1]);
		if (i != 0 && i < temp2.size()-2)
		{
			asmap.find(temp2[i]) -> second -> AddNeighbor(temp2[i-1]);
			asmap.find(temp2[i]) -> second -> AddNeighbor(temp2[i+1]);
		}
		if (i != 0 && i == (temp2.size()-2))
			asmap.find(temp2[i]) -> second -> AddNeighbor(temp2[i-1]);
	}
}



