

#include"ResourceManager.h"

using namespace std;


vector<Resource> ResourceManager::createVector(ifstream& ResrcFile){
	
	vector<Resource> tempVec;
	Resource tempRsrc;
	char line[100];
	string tempStr;
	int lineCount = 1;
	int i;
	
	while(ResrcFile.getline(line, 100)){
		
		int barCount = 0;
		int count, countA, countB, countC;
		
		count = 0;
		countA = 0;
		countB = 0;
		countC = 0;
		
		for(i = 0; i < 100; ++i){
			
			++count;
			
			if(line[i] == '|'){
				
				++barCount;
				
				if(barCount == 1){
					
					tempStr = line;
					tempStr.erase(count - 1);
					tempRsrc.SetID(tempStr);
					countA = count;
				}
				else if(barCount == 2){
					
					tempStr = line;
					tempStr.erase(0, countA);
					
					if((lineCount < 5) || (lineCount == 16)){
						tempStr.erase(14);
					}
					else if((lineCount >= 5) && (lineCount < 9) || (lineCount == 17)){
						tempStr.erase(9);
					}
					else if((lineCount == 9) || (lineCount == 10) || (lineCount == 14) || (lineCount == 18)){
						tempStr.erase(13);
					}
					else if((lineCount == 11) || (lineCount == 19)){
						tempStr.erase(10);
					}
					else if(lineCount == 12){
						tempStr.erase(12);
					}
					else if((lineCount == 13) || (lineCount == 15)){
						tempStr.erase(11);
					}
					else if(lineCount == 20){
						tempStr.erase(16);
					}
					
					tempRsrc.SetName(tempStr);
					countB = count;
				}
				else if(barCount == 3){
					tempStr = line;
					tempStr.erase(0, countB);
					
					if((lineCount < 5) || (lineCount == 16) || (lineCount == 9) || (lineCount == 10) || (lineCount == 18)){
						tempStr.erase(10);
					}
					else if((lineCount >= 5) && (lineCount < 9) || (lineCount == 17)){
						tempStr.erase(6);
					}
					else if((lineCount == 11) || (lineCount == 12) || (lineCount == 13) || (lineCount == 19)){
						tempStr.erase(13);
					}
					else if((lineCount == 14) || (lineCount == 15) || (lineCount == 20)){
						tempStr.erase(20);
					}
					
					tempRsrc.SetType(tempStr);
					countC = count;
					
					tempStr = line;
					tempStr.erase(0,countC);
					tempRsrc.SetStatus(tempStr);
				}
			}
			else if(line[i] != '|'){
				
				continue;
			}
			
		}
		
		tempVec.push_back(tempRsrc);
		
		++lineCount;
		
	}
	
	
	
	return tempVec;
	
}

void ResourceManager::Print(vector<Resource> prntVec){
	
	int i;
	
	cout << endl;
	cout << "+----------------------------------------------------------------------------+" << endl;
	cout << "|Resource ID |  Resource Name  |    Resource Type    | Resource Availability |" << endl;
	cout << "|----------------------------------------------------------------------------|" << endl;
	
	for(i = 0; i < 20; ++i){
	
		cout << left << "|" << setw(12) << prntVec[i].GetID() << "|";
		cout << setw(17) << prntVec[i].GetName() << "|";
		cout << setw(21) << prntVec[i].GetType() << "|";
		cout << setw(23) << prntVec[i].GetStatus() << "|" << endl;
		
	}
	
	cout << "+----------------------------------------------------------------------------+" << endl << endl;
	
}


Resource ResourceManager::SearchByID(vector<Resource> srchVect, string targetID){
	
	Resource srchResrc;
	
	int left = 0;
	int right = 19;
	
	while (left <= right) {
		
		int mid = left + (right - left) / 2;

        if (srchVect[mid].GetID() == targetID){
			
			srchResrc = srchVect[mid];
			break;
			
		}
        else if (srchVect[mid].GetID() < targetID){
			
			left = mid + 1;
			
		}
        else{
			
           right = mid - 1;
		   
		}
    }
	
	
	return srchResrc;
}


void ResourceManager::sort(string choice, vector<Resource>& sortVect, int left, int right){
	
	if (left >= right){
		
		return;
		
	}

    int mid = left + (right - left) / 2;

    sort(choice, sortVect, left, mid);

    sort(choice, sortVect, mid + 1, right);

    merge(choice, sortVect, left, mid, right);
	
}


void ResourceManager::merge(string choice, vector<Resource>& sortVect, int left, int mid, int right){

    int n1 = mid - left + 1;

    int n2 = right - mid;
	
	int i, j;

    vector<Resource> leftVect(n1);

    vector<Resource> rightVect(n2);


    for(i = 0; i < n1; ++i){

        leftVect[i] = sortVect[left + i];
		
	}

    for(j = 0; j < n2; ++j){

        rightVect[j] = sortVect[mid + 1 + j];
		
	}


    i = 0;
	j = 0;
	int k = left;

	if((choice == "I") || (choice == "i")){
	
		while(i < n1 && j < n2){

			if(leftVect[i].GetID() <= rightVect[j].GetID()){ 
		
				sortVect[k] = leftVect[i];
				++i;
				
			}
			else{
			
				sortVect[k] = rightVect[j];
				++j; 
				
			}
	
			++k;
		}

		while(i < n1){
	
			sortVect[k] = leftVect[i]; 
			++i; 
			++k; 
			
		}

		while(j < n2){ 
	
			sortVect[k] = rightVect[j];
			++j;
			++k;
			
		}
		
	}
	else if((choice == "N") || (choice == "n")){
		
		while(i < n1 && j < n2){

			if(leftVect[i].GetName() <= rightVect[j].GetName()){ 
		
				sortVect[k] = leftVect[i];
				++i;
				
			}
			else{
			
				sortVect[k] = rightVect[j];
				++j; 
				
			}

			++k;
		}

		while(i < n1){
	
			sortVect[k] = leftVect[i]; 
			++i; 
			++k; 
			
		}

		while(j < n2){ 
	
			sortVect[k] = rightVect[j];
			++j;
			++k;
			
		}
		
	}
	else if((choice == "T") || (choice == "t")){
		
		while(i < n1 && j < n2){

			if(leftVect[i].GetType() <= rightVect[j].GetType()){ 
		
				sortVect[k] = leftVect[i]; 
				++i;
				
			}
			else{
				
				sortVect[k] = rightVect[j];
				++j; 
				
			}

			++k;
		}

		while(i < n1){
	
			sortVect[k] = leftVect[i]; 
			++i; 
			++k; 
			
		}

		while(j < n2){ 
	
			sortVect[k] = rightVect[j];
			++j;
			++k;
			
		}
		
	}
	else if((choice == "A") || (choice == "a")){
		
		while(i < n1 && j < n2){

			if(leftVect[i].GetStatus() <= rightVect[j].GetStatus()){ 
		
				sortVect[k] = leftVect[i];
				++i;
				
			}
			else{
				
				sortVect[k] = rightVect[j];
				++j; 
				
			}
			
			++k;
			
		}

		while(i < n1){
	
			sortVect[k] = leftVect[i]; 
			++i; 
			++k; 
			
		}

		while(j < n2){ 
		
			sortVect[k] = rightVect[j];
			++j;
			++k;
			
		}
		
	}

}
