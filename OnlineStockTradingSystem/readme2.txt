In this networking project, you will be required to create an online stock trading application
that allows for multiple clients to connect to the server simultaneously.

The client and server components of this application will communicate with each other using TCP sockets and
must adhere to the protocol specifications provided.

To ensure the efficient handling of multiple client connections, you are required to
implement a multithreaded server using either Pthread, Java threads, or Python Threads.
Additionally, the client component of the application should be designed to monitor both
the server's message and user input concurrently using select() statement and threads.

To efficiently manage numerous clients, the server can create a thread pool with a
maximum number of concurrent connections, such as 10, and accept multiple connections
using the select() API. 

It will then create a new thread to manage each connection.
In addition to the commands previously handled by the client in PA1, namely BUY, SELL,
LIST, BALANCE, QUIT, and SHUTDOWN, the server must also manage several
additional commands, such as LOGIN, LOGOUT, DEPOSIT, WHO, and LOOKUP.
Slight modifications will be made to the LIST and SHUTDOWN commands in this
assignment.
