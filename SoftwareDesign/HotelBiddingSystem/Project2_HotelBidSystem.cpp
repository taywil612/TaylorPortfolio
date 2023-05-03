//CIS 476 Project 2
//Author: TaylorD. Williams
//Date: 03/21/23

//The bidding system must include a graphical user interface (GUI) that allows customers to enter their bid price and view the outcome of their bid request.
//Attach to "handler" class HotelRoom

#include <iostream>
#include <vector>
using namespace std;

//class for handler interface, declaring a method for building the chain for COR design pattern to be used
//declares method for executing a user's bid price given
class Room {
public:
	int numRoom = 0;
	//Room is the Handler in this case
	virtual Room *SetNext(Room *room) = 0;
	//HandleRequest is the Handle for user's bid request
	virtual int HandleRequest(int bidRequest) = 0;
	//handleRequest2 is the Handle for the amount of 
	
};

//Base Handler, class HotelRoom, represents a room that can be bid on. 
class HotelRoom : public Room {
private:
	Room *next_room;

public:
	
	HotelRoom(): next_room(nullptr){}

	//Returns a handler "room", will allow for linking handlers a.k.a. types of hotel rooms
	//such as order, Suite -> setNext(Deluxe) -> setNext(Standard)
	Room *SetNext(Room *room) override {
		this->next_room = room;
		return room;
	}

	//for when the client enters their bid request
	int HandleRequest(int bidRequest) override {
		if (this->next_room) {
			return this->next_room->HandleRequest(bidRequest);
		}
		return {};
	}

	void HandleRequest2(int numRooms) {
		//handle for amount of rooms per type of hotel room
	}

	//overrride above functions in extended classes by type of hotel room
};


class SuiteHandler : public HotelRoom {
public:
	//number of Suite rooms 
	//may change to numRoomSuite, same for all and possible store in vector
	int numRoom = 10;
	
		int HandleRequest(int bidRequest) override {
			//Checks if bid price is in range and if rooms are available
			if (bidRequest >= 280 && numRoom > 0 && numRoom <= 10) {
				cout << "Congrats! Your bid has been accepted for a Suite Room!" << endl;
				numRoom = numRoom - 1;
				//return numRoom;
			}

			//if rooms are still available
			else if (numRoom > 0 && numRoom <= 10) {
				cout << "Continue checking suite rooms...." << endl;
				return HotelRoom::HandleRequest(bidRequest);
			}

			//if the bid request does not meet any "Suite" requirements, passes request to the next handler
			//in the chain
			else {
				return HotelRoom::HandleRequest(bidRequest);
			}
		}

	
};

class DeluxeHandler : public HotelRoom {
public:

	//number of Deluxe rooms availble
	int numRoom = 15;

	int HandleRequest(int bidRequest) override {
		//Checks if bid price is in range and if rooms are available
		if (bidRequest >= 150 && bidRequest <= 280 && numRoom > 0  && numRoom <= 15) {
			cout << "Congrats! Your bid has been accepted for a Deluxe Room!" << endl;
			numRoom = numRoom - 1;
			//return  numRoom;
		}

		//if rooms are still available
		else if (numRoom > 0 && numRoom <= 15) {
			cout << "Continue checking deluxe rooms...." << endl;
			return HotelRoom::HandleRequest(bidRequest);
		}

		//if the bid request does not meet any "Deluxe" requirements, passes request to the next handler
		//in the chain
		else {
			return HotelRoom::HandleRequest(bidRequest);
		}
	}

};

//Class for a Standard Hotel Room
class StandardHandler : public HotelRoom {
public:
	//number of Standard rooms available
	int numRoom = 45;

	int HandleRequest(int bidRequest) override {
		//Checks if bid price is in range and if rooms are available
		if (bidRequest >= 80 && bidRequest <= 150 && numRoom > 0 && numRoom <= 45) {
			//if in price range and rooms are availble, bid is accepted
			cout << "Congrats! Your bid has been accepted for a Standard Room!" << endl;
			numRoom = numRoom - 1;
			//return numRoom;
		}

		//if rooms are still available
		else if (numRoom > 0 && numRoom <= 45) {
			cout << "Continue checking standard rooms...." << endl;
			return HotelRoom::HandleRequest(bidRequest);
		}

		//if the bid request does not meet any "Standards" requirements, passes request to the next handler
		//in the chain
		else {
			return HotelRoom::HandleRequest(bidRequest);
		}
	}

};

//function to process the user's inputted bid request
void processBid(Room &room) {
	int bidRequest;

	vector <int> bidAmounts = {0};

	cout << "Enter a bid price: " << endl;
	cin >> bidRequest;

	//inserts what the user enters into the empty vector
	bidAmounts.insert(bidAmounts.begin() + 1, bidRequest);

	//processes users value's
	for (auto &x : bidAmounts) {
		room.HandleRequest(x);
	}

	// when there are still rooms available but bid was denied by all room handlers
	//correct but only show if bid price
	if (bidRequest < 80 && processBid != NULL) {
		cout << "Sorry, your bidding request has been denied, please provide a new bid price!" << endl;
	}


}


//make separate function tied to Handler & handler in for loopand figure out GUI, first make it work before implementing GUI!
	

int main() {
	int numRoom = 0;
	int bidRequest;
	
	//Chain of responsibility
	SuiteHandler *suite = new SuiteHandler;
	DeluxeHandler *deluxe = new DeluxeHandler;
	StandardHandler *standard = new StandardHandler;

	suite->SetNext(deluxe)->SetNext(standard);

	while (numRoom == 0) {

		//calls processing bid request function staring with suite
		processBid(*suite);


		//might change to processBid
		//suite->SetNext(deluxe)->SetNext(standard) == NULL
		//If the chain from the bidrequest does not return any values (the chain would not fulfill bid request)
		if (processBid == NULL) {
			cout << "Sorry, your bidding request has been denied, all rooms are sold out!" << endl;
		}

		
	}

}