#include "comm/read_data_impl.h"
#include "comm/serial_port.h"

string uart_name = "/dev/ttyACM0";

int main(int argc, char **argv)
{
    GenericPort *port = new SerialPort(uart_name, 57600);

    ReadDataImpl read_data(port);

    port->start();

    read_data.start();

    sleep(10);


    read_data.stop();

    port->stop();

    delete port;

    return 0;

}