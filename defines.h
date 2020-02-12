#ifndef bzero
    #define bzero(d, n) memset((d), 0, (n))
#endif

#define ADDR_LEN            9  // as bytes
#define MSG_LEN           121
#define MASTER_IP "127.0.0.1"