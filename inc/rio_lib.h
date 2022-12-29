/*
 * Contains the types and methods for robust IO.
 */

struct {

} rio_t;

void rio_readinitb(rio_t* rio, int fd);
void rio_writen(int fd, char* buf, size_t bufsize);
void rio_readlineb(rio_t* rio, char* buf, size_t bufsize);
