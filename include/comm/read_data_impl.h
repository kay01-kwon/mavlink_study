#ifndef READ_DATA_IMPL_H
#define READ_DATA_IMPL_H


#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <mutex>
#include "generic_port.h"

#include "mavlink_messages.h"

class ReadDataImpl
{

    public:
    ReadDataImpl() = delete;

    ReadDataImpl(GenericPort *port);

    ~ReadDataImpl();

    void read_messages();

    void start();

    void stop();

    void read_thread();

    void handle_quit(int sig);

    MavlinkMessages messages_;

    private:

    bool reading_status_, time_to_exit_;

    int system_id_, comp_id_;

    GenericPort *port_;

    pthread_t read_thread_;

    void start_read_thread();

};


void *start_ReadDataImpl_read_thread(void *context);


#endif