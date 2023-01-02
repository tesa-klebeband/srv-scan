#include "includes.h"
#include "functions.h"

bool connected(char *addr, u_short port, int timeout)
{
    struct sockaddr_in address;
    short int sock = -1;
    fd_set fdset;
    struct timeval tv;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(addr);
    address.sin_port = htons(port);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    fcntl(sock, F_SETFL, O_NONBLOCK);

    connect(sock, (struct sockaddr *)&address, sizeof(address));

    FD_ZERO(&fdset);
    FD_SET(sock, &fdset);
    tv.tv_sec = 0;
    tv.tv_usec = timeout * 1000;

    if (select(sock + 1, NULL, &fdset, NULL, &tv) == 1)
    {
        int so_error;
        socklen_t len = sizeof so_error;

        getsockopt(sock, SOL_SOCKET, SO_ERROR, &so_error, &len);

        if (so_error == 0)
        {
            close(sock);
            return true;
        }
    }

    close(sock);
    return false;
}

bool is_in_range(int i1, int i2, int i3, int i4)
{
    if (i1 == 0)
        return false;
    if (i1 == 10)
        return false;
    if (i1 == 100 && i2 >= 64 && i2 <= 127)
        return false;
    if (i1 == 127)
        return false;
    if (i1 == 169 && i2 == 254)
        return false;
    if (i1 == 172 && i2 >= 16 && i2 <= 31)
        return false;
    if (i1 == 192 && i2 == 0 && i3 == 0)
        return false;
    if (i1 == 192 && i2 == 0 && i3 == 2)
        return false;
    if (i1 == 192 && i2 == 31 && i3 == 196)
        return false;
    if (i1 == 192 && i2 == 53 && i3 == 193)
        return false;
    if (i1 == 192 && i2 == 88 && i3 == 99)
        return false;
    if (i1 == 192 && i2 == 168)
        return false;
    if (i1 == 192 && i2 == 175 && i3 == 48)
        return false;
    if (i1 == 198 && i2 >= 18 && i2 <= 19)
        return false;
    if (i1 == 198 && i2 == 51 && i3 == 100)
        return false;
    if (i1 >= 224 && i1 <= 239)
        return false;
    if (i1 >= 240 && i1 <= 255)
        return false;
    return true;
}

void worker_thread(int threadCount, int threadNum, u_short port, int timeout)
{
    char addr[32] = {0};
    int threadStart = 256 / threadCount * threadNum;
    int threadRange = 256 / threadCount;
    for (int i1 = 0; i1 < 255; i1++)
    {
        for (int i2 = 0; i2 < 255; i2++)
        {
            for (int i3 = threadStart; i3 - threadStart < threadRange; i3++)
            {
                for (int i4 = 0; i4 < 255; i4++)
                {
                    if (is_in_range(i4, i3, i2, i1))
                    {
                        sprintf(addr, "%d.%d.%d.%d", i4, i3, i2, i1);
                        if (connected(addr, port, timeout))
                        {
                            printf("%s:%u\n", addr, port);
                        }
                    }
                }
            }
        }
    }
}