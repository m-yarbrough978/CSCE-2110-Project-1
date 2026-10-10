

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include"Resource.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>

using namespace std;

class ResourceManager{
	public:
		vector<Resource> createVector(ifstream& ResrcFile);
		void Print(vector<Resource> prntVec);
	
	private:
		

};




#endif
