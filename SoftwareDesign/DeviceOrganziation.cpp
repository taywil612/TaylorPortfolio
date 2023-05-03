 v//CIS 476 - Software Architecture and Design patterns
//Project 1
//Author: Taylor Williams
//Date: 2/20/2023

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<algorithm>
using namespace std;

//Classes for the abstract products,create Battery, Display and Processor for the abstract factory
class createBattery {
public:
	virtual string product() = 0;

};

class createDisplay {
public:
	virtual string product() = 0;
};

class createProcessor {
public:
	virtual string product() = 0;
};

//All the classes for concrete products of the four concrete factories Tablet, laptop, Smartphone, and Smartwatch
//For Tablet
class tabletBattery : public createBattery {
public:
	string  product() {
		return "Tablet Battery";
	}
};

class tabletDisplay : public createDisplay {
public:
	string product() {
		return "Tablet Display";
	}
};

class tabletProcessor : public createProcessor {
public:
	string product() {
		return "Tablet Processor";
	}
};

//For Laptop
class laptopBattery : public createBattery {
public:
	string product() {
		return "Laptop Battery";
	}
};

class laptopDisplay : public createDisplay {
public:
	string product() {
		return "Laptop Display";
	}
};

class laptopProcessor : public createProcessor {
public:
	string product() {
		return "Laptop Processor";
	}
};


//For Smartphone
class smartphoneBattery : public createBattery {
public:
	string product() {
		return "Smartphone Battery";
	}
};

class smartphoneDisplay : public createDisplay {
public:
	string product() {
		return "Smartphone Display";
	}
};

class smartphoneProcessor : public createProcessor {
public:
	string product() {
		return "Smartphone Processor";
	}
};


//For Smartwatch
class watchBattery : public createBattery {
public:
	string product() {
		return "Smartwatch Battery";
	}
};

class watchDisplay : public createDisplay {
public:
	string product() {
		return "Smartwatch Display";
	}
};

class watchProcessor : public createProcessor {
public:
	string product() {
		return "Smartwatch Processor";
	}
};


//ABSTRACT FACTORY CLASS
class Abstract_Factory {
public:
	enum Device_Components {Tablet, Laptop, Smartphone, Smartwatch};
	virtual createBattery* getBattery() = 0;
	virtual createDisplay* getDisplay() = 0;
	virtual createProcessor* getProcessor() = 0;

	//prototype for class
	static Abstract_Factory* createFactory(Device_Components factory);

};


//CONCRETE FACTORY CLASSES

//concrete factory Tablet
class Tablet_factory : public Abstract_Factory {
public:
	createBattery* getBattery() {
		return new tabletBattery();
	}

	createDisplay* getDisplay() {
		return new tabletDisplay();
	}

	createProcessor* getProcessor() {
		return new tabletProcessor();
	}
};


//concrete factory Laptop
class Laptop_factory : public Abstract_Factory {
public:
	createBattery* getBattery() {
		return new laptopBattery();
	}

	createDisplay* getDisplay() {
		return new laptopDisplay();
	}

	createProcessor* getProcessor() {
		return new laptopProcessor();
	}
};


//concrete factory Smartphone
class Smartphone_factory : public Abstract_Factory {
public:
	createBattery* getBattery() {
		return new smartphoneBattery();
	}

	createDisplay* getDisplay() {
		return new smartphoneDisplay();
	}

	createProcessor* getProcessor() {
		return new smartphoneProcessor();
	}
};


//concrete factory Smartwatch
class Smartwatch_factory : public Abstract_Factory {
public:
	createBattery* getBattery() {
		return new watchBattery();
	}

	createDisplay* getDisplay() {
		return new watchDisplay();
	}

	createProcessor* getProcessor() {
		return new watchProcessor();
	}
};


//Function for abstract facatory
Abstract_Factory* Abstract_Factory::createFactory(Device_Components factory) {
	//for when the concrete factory is Tablet
	if (factory == Abstract_Factory::Tablet) {
		return new Tablet_factory();
	}

	//for when the concrete dactor is Laptop
	else if (factory == Abstract_Factory::Laptop) {
		return new Laptop_factory();
	}

	//for when the concrete factory is Smaprtphone
	else if (factory == Abstract_Factory::Smartphone) {
		return new Smartphone_factory();
	}

	//for when the concrete factory is Smartwatch
	else if (factory == Abstract_Factory::Smartwatch) {
		return new Smartwatch_factory();
	}
}


//Function to print out the concrete factories and their concrete products
void printFactory(Abstract_Factory* factory, string name) {
	//display concrete products
	cout << factory->getBattery()->product() << endl;
	cout << factory->getDisplay()->product() << endl;
	cout << factory->getProcessor()->product() << endl;
	cout << endl;

};

//Function to print error message
void printError(string name) {
	cout << name << " : MORE THAN TWO INSTANCES WERE CALLED!!" << endl;
	cout << endl;
};

//Main function to test and implement singleton pattern to make sure each instanc of the devices
//is only called up to 2 times
int main() {
	ifstream textFile;
	string getword;
	vector<string>all_Words_toRead;
	int tabletInstance = 0, laptopInstance = 0, smartphoneInstance = 0, smartwatchInstance = 0;
	int count = 0;
	//Open the text file for testing
	textFile.open("Test File.txt");

	if (!textFile) {
		cout << "Could not locate text file!" << endl;
		exit(1);
	}

	//read the content in the text file
	while (textFile.good()) {
		getline(textFile, getword);
		all_Words_toRead.push_back(getword);
	}
	textFile.close();

	//Processes the words in the text file, finding if there are repeated words or not
	for (unsigned int i = 0; i < all_Words_toRead.size(); i++) {
		//if the word found is Tablet
		if (all_Words_toRead[i] == "Tablet") {
			//if tablet is called more than 2x
			if (tabletInstance >= 2) {
				printError(all_Words_toRead[i]);
			}
			//If not print
			else {
				Abstract_Factory* factory = Abstract_Factory::createFactory(Abstract_Factory::Device_Components::Tablet);
				printFactory(factory, all_Words_toRead[i]);
				tabletInstance++;
			}
		}

		//if the word found is Laptop
		 else if (all_Words_toRead[i] == "Laptop") {
			//if laptop is called more than 2x
			if (laptopInstance >= 2) {
				printError(all_Words_toRead[i]);
			}
			//If not print
			else {
				Abstract_Factory* factory = Abstract_Factory::createFactory(Abstract_Factory::Device_Components::Laptop);
				printFactory(factory, all_Words_toRead[i]);
				laptopInstance++;
			}
		}

		//if the word found is Smartphone
		 else if (all_Words_toRead[i] == "Smartphone") {
			//if smartphone is called more than 2x
			if (smartphoneInstance >= 2) {
				printError(all_Words_toRead[i]);
			}
			//If not print
			else {
				Abstract_Factory* factory = Abstract_Factory::createFactory(Abstract_Factory::Device_Components::Smartphone);
				printFactory(factory, all_Words_toRead[i]);
				smartphoneInstance++;
			}
		}

		//if the word found is Smartwatch
		 else if (all_Words_toRead[i] == "Smartwatch") {
			//if smartwatch is called more 2x
			if (smartwatchInstance >= 2) {
				printError(all_Words_toRead[i]);
			}
			//If not print
			else {
				Abstract_Factory* factory = Abstract_Factory::createFactory(Abstract_Factory::Device_Components::Smartwatch);
				printFactory(factory, all_Words_toRead[i]);
			    smartwatchInstance++;
			}
		}
	}
	return 0;
}
