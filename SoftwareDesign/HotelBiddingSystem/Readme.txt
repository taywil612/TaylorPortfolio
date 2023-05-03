This project involves implementing a hotel room bidding system that utilizes the chain of responsibility (COR) design pattern. The system allows customers to bid on 
available hotel rooms, and the COR pattern is used to handle the bid requests.

The hotel room bidding system has a class called HotelRoom that represents a room that can be bid on. There are three handlers available in the system, one for each 
room type: Standard, Deluxe, and Suite. When customers make bid requests for rooms, the bid request is processed by a chain of handlers in a specific order: 
Suite -> Deluxe -> Standard. Each handler is responsible for two factors when determining whether a bid request can be accepted: the bid price and the number of rooms 
available. 

1.	Bid price
a.	Standard room accepts price ranges $80 - $150
b.	Deluxe room accepts price ranges $150 - $280
c.	Suite accepts price ranges $280 and above
2.	Numbers of rooms available
a.	45 standard rooms available
b.	15 Deluxe rooms available
c.	10 Suite available
d.	The numbers of rooms available for corresponding room type are reduced by one after each successful bid.

If a handler is unable to accept a bid request, it passes the request to the next handler in the chain. If all handlers in the chain are unable to accept the bid request 
and there are still available rooms, the request is rejected and the customer is asked to provide a new bid price. If all rooms are booked out, display a sold out 
message.



