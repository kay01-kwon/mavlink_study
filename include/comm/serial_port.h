#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H

#include <stdio.h>      // standard input / output functions
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <termios.h>   // POSIX terminal control definitions
#include <pthread.h>    // POSIX threads
#include <signal.h>     // POSIX signals

#include "generic_port.h"


class SerialPort : public GenericPort
{
    public:

    SerialPort();

    SerialPort(const string &port_name, int baudrate);

    virtual ~SerialPort();

    int read_message(mavlink_message_t &message) override;

    int write_message(const mavlink_message_t &message) override;

    bool is_running() override;

    void start() override;

    void stop() override;

    private:

    int fd_;
    mavlink_status_t last_status_;
    bool is_open_;
    pthread_mutex_t lock_;

    bool debug_;
    string port_name_;
    int baudrate_;

    void initialize_defaults();

    int open_port(const string &port);
    
    bool setup_port(int baud, int data_bits, 
    int stop_bits, bool parity, 
    bool hardware_control);

    int read_port(uint8_t &cp);

    int write_port(char *buf, unsigned len);

};


#endif