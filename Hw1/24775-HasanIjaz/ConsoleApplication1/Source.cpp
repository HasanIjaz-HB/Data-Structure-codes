#include <iostream>
#include<string>
#include<fstream>
#include<stdlib.h>
#include <sstream>
#include "LinkedList.h"


using namespace std;
class Rectangle {
	friend class Tree;
public:
	Rectangle() { Top = INT_MIN; Left = INT_MIN; Bottom = INT_MIN; Right = INT_MIN; }
	Rectangle(int T,  int B, int L, int R)
	{
		Top = T;  Bottom = B; Left = L; Right = R;
	}

	Rectangle Horizontaldivide() //Dividing the Rectangle with horizontal line  to find intersection 
	{
		return Rectangle((Top + Bottom) / 2, (Top + Bottom) / 2, Left, Right);
	}
	Rectangle Verticaldivide() //Dividing the Rectangle with vertical line  to find intersection 
	{
		return Rectangle(Top, Bottom, (Left + Right) / 2, (Left + Right) / 2);
	}
	int Verticalline() //calculating vertical line
	{
		return ((Left + Right)/2);
	}
	int Horizontalline()  //calculating horizontal line
	{
		return ((Top + Bottom)/ 2);
	}
	bool intersect(const Rectangle &rhs)
	{
		if (Top > rhs.Bottom || Bottom < rhs.Top || Left > rhs.Right || Right < rhs.Left)
			return false;
		return true;
	}
	bool operator == (Rectangle &rhs)
	{
		return(Top == rhs.Top && Bottom == rhs.Bottom && Left == rhs.Left && Right == rhs.Right);
	}
	friend  ostream& operator << (ostream & out, Rectangle &rhs)
	{
		out << rhs.Top << " " << rhs.Left << " " << rhs.Bottom << " " << rhs.Right;
		return out;
	}
	int getLeft() { return Left; }
	int getRight() { return Right; }
	int getBottom() { return Bottom; }
	int getTop() { return Top; }
private:
	int Top; int Left; int Bottom; int Right;
};

class Tree {

public:
	Tree(Rectangle &x)
	{
		Root = new TwoDimTreeNode(x);
	}
	void add(Rectangle & a)
	{
		Root->addtotree(a);
	}
	LinkedList<Rectangle> find(Rectangle & in)
	{
		LinkedList<Rectangle> out;
		Root->find(in, out);
		return out;
	}
private:
	class TwoDimTreeNode {
	public:
		TwoDimTreeNode(Rectangle &E)
		{
			Extent = E;
			TopLeft = NULL;
			TopRight = NULL;
			BottomLeft = NULL;
			BottomRight = NULL;
		}
		void find(Rectangle & in, LinkedList<Rectangle> & out)
		{
			out.addtolist(LLFind(in, Vertical));
			out.addtolist(LLFind(in, Horizontal));
			 //find the input in horizontal and vertical intersection list
			if (in.Horizontalline() == Extent.Horizontalline() || in.Verticalline() == Extent.Verticalline()) //if the horizontal and vertical lines are same return after searching lists ; there's no need to search more
			{
				return;
			}
			if (in.Horizontalline() > Extent.Horizontalline()) // find the next quadrant to search in and loop this if necessary
			{
				if (BottomRight != NULL && in.Verticalline() > Extent.Verticalline())
				{
						BottomRight->find(in, out);
				}
				else
				{
					if (BottomLeft != NULL)
					{
						BottomLeft->find(in, out);
					}
				}
			}
			else
			{
				if (TopRight != NULL && in.Verticalline() > Extent.Verticalline())
				{
						TopRight->find(in, out);
				}
				else
				{
					if (TopLeft != NULL)
						TopLeft->find(in, out);
				}
			}

		}
		void addtotree(Rectangle & node)
		{
			if (node.intersect(Extent.Horizontaldivide())) //checking if the particular rectangle intersects with horizontally dividing line
			{
				this->Horizontal.addtolist(node);
			}
			else if (node.intersect(Extent.Verticaldivide()))//checking if the particular rectangle intersects with vertically dividing line
			{
				this->Vertical.addtolist(node);
			}
			else if (node.Horizontalline() > Extent.Horizontalline()) //checking if the rectangle goes to bottom
			{
				if (node.Verticalline() > Extent.Verticalline())// checking if rectangle goes to bottom and right
				{
					if (this->BottomRight == NULL) // rectangle goes to bottomright
					{
						BottomRight = new TwoDimTreeNode(Rectangle(Extent.Horizontalline(), Extent.Bottom, Extent.Verticalline(), Extent.Right));
					}
					BottomRight->addtotree(node);
				}
				else if (this->BottomLeft == NULL) // rectangle goes to bottomleft
				{
					BottomLeft = new TwoDimTreeNode(Rectangle(Extent.Horizontalline(), Extent.Bottom, Extent.Left, Extent.Verticalline()));
					BottomLeft->addtotree(node);
				}
					
			}
			else if (node.Verticalline() > Extent.Verticalline())  //we know rectangle goes to top now checking if it goes to right
			{
				if (this->TopRight == NULL) // rectangle goes to Topright
				{
					TopRight = new TwoDimTreeNode(Rectangle(Extent.Top, Extent.Horizontalline(), Extent.Verticalline(), Extent.Right));
				}
				TopRight->addtotree(node);
			}
			else //top and left
			{
				if (this->TopLeft == NULL) // rectangle goes to Topleft
				{
					TopLeft = new TwoDimTreeNode(Rectangle(Extent.Top, Extent.Horizontalline(), Extent.Left, Extent.Verticalline()));
				}
				TopLeft->addtotree(node);
			}
		}
		LinkedList<Rectangle> LLFind(Rectangle & in, LinkedList<Rectangle> & rhs)
		{
			LinkedList<Rectangle> s(rhs), out;
			while (s.getSize() != 0) {
				Rectangle compare(s.removeFirst());
				if (compare.intersect(in))
					out.addtolist(compare);
			}
			return out;
		}
	private:
		Rectangle Extent;
		LinkedList <Rectangle> Vertical, Horizontal;
		TwoDimTreeNode *TopLeft, *TopRight, *BottomLeft, *BottomRight;
	};
	TwoDimTreeNode *Root;
};

struct inputdata {
	int l, m;
	LinkedList<Rectangle> data;
	inputdata(int r, int s, LinkedList<Rectangle> & t) : l(r), m(s), data(t) {}
	inputdata() :l(INT_MIN), m(INT_MIN) {}
	inputdata(inputdata & rhs) :l(rhs.l), m(rhs.m), data(rhs.data) {}
};

ostream& operator << (ostream & out, inputdata & in) {
	out << in.l << " " << in.m
		<< "\n" << in.data.getSize() << "\n";
	in.data.print(out);
	return out;
}


int main()
{
	string fname = "rectdb.txt";
	ifstream in;
	in.open(fname.c_str());//opening file
	
	int Top, Bottom, Left, Right;//reading top bottom left right for initial extent
	in >> Top >> Left >> Bottom >> Right; //this line has been moidified
	Tree tree(Rectangle(Top, Bottom, Left, Right)); //Creating the tree

	int top, bottom, right, left;
	in >> top;
	while (top >= 0) {
		in >> left >> bottom >> right;
		tree.add(Rectangle(top, bottom, left, right));
		in >> top;
	}

	LinkedList <inputdata> indata;
	int t, b;
	cin >> t;
	while (t >= 0)
	{
		cin >> b;
		indata.addtolist(inputdata(t, b, LinkedList<Rectangle>(tree.find(Rectangle(b, b, t, t)))));
		cin >> t;
	}
	indata.printReverse(cout);
	cin.get();
	cin.ignore();
	return 0;
}