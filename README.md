# RPi-Projs
Stuff done on Raspberry Pi

--Compiling & Executing the Program--

To start the program, you first need to make the executable file. Initiate this by typing ‘make’ in the prompt whilst in the Labs/Lab2/ directory. To execute the server, type in ‘./server’ and to execute the client, type in ‘./client raspberrypi’. Once a client has connected to the server, it can send any messages to the server and get a response from the server that the message was received.

--Description of the Program--

* Server.c

Once the server has been started it will sit and listen for incoming connection requests from clients. If a connection is detected, the server will try to open a socket and start a session with the client. Additionally, a function has been added that can detect a specific IP-address and deny this address from connecting to the server. Once a client has connected, the server prints out a message with the clients IP-address and the port number being used for the session. This message will also be broadcast to any clients already connected to the server. 

* Client.c

When the client has started, it will connect to the server by a socket and use this for any further communication. With the help of pthreads, the client is able to simultaneously listen and send messages to the server.
