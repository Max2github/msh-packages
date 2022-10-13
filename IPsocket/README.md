# IPsocket package (BETA, UNIX)
This package enables simple TCP/IP communication.

## commands

### listen-IPsocket

    <server> = listen-IPsocket() <port>

Listens on the given port (opens a server) and returns a server socket handle (you can see it like an id)<br>
In C: Does binding and listening and returns the server socket file descriptor.

### accept-IPsocket

    <client> = accept-IPsocket() <server>

Accepts a new connection with the given server socket handle and returns a new client socket handle.<br>
In C: Takes the server socket file descriptor and returns a new client socket file descriptor.

### receive-IPsocket

    <data> = receive-IPsocket() <client | server>

Waits for and returns the data send given socket handle.

### send-IPsocket

    send-IPsocket() <data> TO <client | server>

Sends the given data to the given socket handle.

### connect-IPsocket (SOON)



Connects to a server socket handle.