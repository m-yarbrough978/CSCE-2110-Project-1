

#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

using namespace std;

class Resource{
	public:
		Resource(); //default constructor
		void SetID(string idX); //Mutator for id
		string GetID() const; // Accessor for id
		void SetName(string nameX); //Mutator for name
		string GetName() const; // Accessor for name
		void SetType(string typeX); //Mutator for type
		string GetType() const; // Accessor for type
		void SetStatus(string statusX); //Mutator for status
		string GetStatus() const; // Accessor for status
	
	private:
		string id, name, type, status;

};




#endif
