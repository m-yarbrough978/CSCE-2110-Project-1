

#include "Resource.h"
#include <iostream>
#include <string>

using namespace std;

Resource::Resource(){
	id = "R000";
	name = "None";
	type = "None";
	status = "Unkown";
}

void Resource::SetID(string idX){
	id = idX;
}

string Resource::GetID() const{
	return id;
}

void Resource::SetName(string nameX){
	name = nameX;
}

string Resource::GetName() const{
	return name;
}

void Resource::SetType(string typeX){
	type = typeX;
}

string Resource::GetType() const{
	return type;
}

void Resource::SetStatus(string statusX){
	status = statusX;
}

string Resource::GetStatus() const{
	return status;
}
