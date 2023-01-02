#ifndef FUNCTIONS_H
#define FUNCTIONS_H

bool connected(char *addr, u_short port, int timeout);
bool is_in_range(int i1, int i2, int i3, int i4);
void worker_thread(int threadCount, int threadNum, u_short port, int timeout);

#endif