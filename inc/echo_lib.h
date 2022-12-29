// The maximum line length for a hostname.
#define MAXLINE 8192

// Establishes connection to the server with the given hostname and port.
int open_clientfd(char* hostname, char* port);

// Creates a listening descriptor that is ready to receive connect requests on a given port.
int open_listenfd(char* port);
