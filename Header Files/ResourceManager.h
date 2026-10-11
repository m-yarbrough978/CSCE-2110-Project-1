

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
		Resource SearchByID(vector<Resource> srchVect, string targetID);
		void sort(string choice, vector<Resource>& sortVectI, int left, int right);
		void merge(string choice, vector<Resource>& sortVectI, int left, int mid, int right);
		

};




#endif
