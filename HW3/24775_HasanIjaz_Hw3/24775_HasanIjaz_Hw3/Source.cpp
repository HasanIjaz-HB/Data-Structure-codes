#include <iostream>
#include <fstream>
#include <vector>
#include "MPQ.h"

using namespace std;


struct buildingdetail
{
	int label, xvalue, yvalue;
	string xside;
};

void assign(vector<buildingdetail> & array, int  i, int  child);
bool lesss(buildingdetail & x, buildingdetail  y);
void percolateDown(vector<buildingdetail> & array, int i, int  currentSize);

void heapsort(vector<buildingdetail> & x)
{
	for (int i = x.size() / 2; i >= 0; i--)
		percolateDown(x,i,x.size());

	for (int i = x.size() - 1; i > 0; i--)
	{
		//swapping max to last element
		buildingdetail temp;
		temp.label = x[0].label;
		temp.xvalue = x[0].xvalue;
		temp.xside = x[0].xside;
		temp.yvalue = x[0].yvalue;

		assign(x, 0, i);

		x[i].label = temp.label;
		x[i].xvalue = temp.xvalue;
		x[i].xside = temp.xside;
		x[i].yvalue = temp.yvalue;

		// reforming the heap
		percolateDown(x, 0, i);
	}
}


void percolateDown(vector<buildingdetail> & array, int i, int  currentSize)
{//copied from slides and edited as required
	int child;
	buildingdetail tmp;

	tmp.label = array[i].label;
	tmp.xvalue = array[i].xvalue;
	tmp.xside = array[i].xside;
	tmp.yvalue = array[i].yvalue;


	for (; i * 2 < currentSize; i = child)
	{
		child = i * 2;
		if (child != currentSize - 1 && lesss(array[child], array[child + 1])) //a[child]<a[child+1]
			child++; 
		if (lesss(tmp, array[child]))
			assign(array, i, child); // a[i] = a[child]
		else
			break;
	}
	// assigning a[i] = tmp 
	array[i].xside = tmp.xside;
	array[i].xvalue = tmp.xvalue;
	array[i].label = tmp.label;
	array[i].yvalue = tmp.yvalue;
}

void assign(vector<buildingdetail> & array, int  i, int  child) {
	array[i].xside = array[child].xside;
	array[i].yvalue = array[child].yvalue;
	array[i].label = array[child].label;
	array[i].xvalue = array[child].xvalue;
}

bool lesss(buildingdetail & x, buildingdetail  y) {
	if ((x.xvalue < y.xvalue) || (x.xvalue == y.xvalue && x.xside < y.xside) || (x.xvalue == y.xvalue && x.xside == y.xside && x.xside == "left" && x.yvalue > y.yvalue) || (x.xvalue == y.xvalue && x.xside == y.xside && x.xside == "right" && x.yvalue < y.yvalue))
		return true;
	return false;
}
	

int main()
{
	ifstream in;
	string fname = "input.txt";
	in.open(fname.c_str());//opening file
	int numbuilding;
	in >> numbuilding;//reading num total num of buildings from first line of file
	vector<buildingdetail> buildingdeets(numbuilding * 2); //creating a vector of double size of building to store left and right side details
	int x1value, height, x2value;
	int i = 0;
	for (int buildno = 1; buildno <= numbuilding;buildno++)
	{
		in >> x1value >> height >> x2value;// reading values from file
		buildingdeets[i].label = buildno;
		buildingdeets[i].xside = "left";
		buildingdeets[i].xvalue = x1value;
		buildingdeets[i].yvalue = height;//assigning values respectively
		i++;// incrementing index of vector to store the right side
		buildingdeets[i].label = buildno;
		buildingdeets[i].xside = "right";
		buildingdeets[i].xvalue = x2value;
		buildingdeets[i].yvalue = height;
		i++;//incrementing again to store the next buildings left side details
	}

	heapsort(buildingdeets);//sorting the heap 


	BinaryHeap heapmax(numbuilding);

	int max = -10;

	if (buildingdeets[0].xvalue > 0) // the first building is located at any other x except 0 so we print at x =0 y =0 as required in the output format
		cout << 0 << " " << 0 << endl;;
	for (int i = 0; i < buildingdeets.size(); i++)
	{
		if (buildingdeets[i].xside == "left")
		{
			heapmax.insert(buildingdeets[i].yvalue, buildingdeets[i].label); //if the side if left it means the building is starting so we add the height and label to heap
		}
		else
		{
			heapmax.remove(buildingdeets[i].label); //if the side is right we remove the entry from the heap bcz the building has now ended
		}
		if (heapmax.GetMax() != max)
		{
			max = heapmax.GetMax();
			cout << buildingdeets[i].xvalue << " " << max <<endl;
		}
	}


	in.close();
	cin.get();
	cin.ignore();
	
	return 0;
}