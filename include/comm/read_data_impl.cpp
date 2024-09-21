#include "read_data_impl.h"
ReadDataImpl::ReadDataImpl(GenericPort *port)
: port_(port), reading_status_(0), 
system_id_(0), comp_id_(0),
time_to_exit_(false)
{
    messages_.sys_id = system_id_;
    messages_.comp_id = comp_id_;
}

ReadDataImpl::~ReadDataImpl()
{
}

void ReadDataImpl::read_messages()
{
    bool success = false;

    while(!time_to_exit_)
    {
        mavlink_message_t message;
        success = port_->read_message(message);

        if(success)
        {
            messages_.sys_id = message.sysid;
            messages_.comp_id = message.compid;

            switch(message.msgid)
            {
                case MAVLINK_MSG_ID_HEARTBEAT:
                    mavlink_msg_heartbeat_decode(&message, &(messages_.heartbeat));
                    break;
                case MAVLINK_MSG_ID_SYS_STATUS:
                    mavlink_msg_sys_status_decode(&message, &(messages_.sys_status));
                    break;
                case MAVLINK_MSG_ID_BATTERY_STATUS:
                    mavlink_msg_battery_status_decode(&message, &(messages_.battery_status));
                    break;
                case MAVLINK_MSG_ID_HIGHRES_IMU:
                    mavlink_msg_highres_imu_decode(&message, &(messages_.highres));
                    printf("IMU: %f %f %f\n", messages_.highres.xacc, messages_.highres.yacc, messages_.highres.zacc);
                    break;
                case MAVLINK_MSG_ID_ATTITUDE:
                    mavlink_msg_attitude_decode(&message, &(messages_.attitude));
                    break;
                default:
                    break;
            }
        }
    }

}

void ReadDataImpl::start()
{
    if(!port_->is_running())
    {
        cout << "Error: Port is not opened" <<endl;
        return;
    }

    int result;

    result = pthread_create(&read_thread_, NULL, 
    start_ReadDataImpl_read_thread, this);

    if(result)
    {
        cout << "Error: Unable to create read thread" << endl;
        return;
    }

    while(!messages_.sys_id)
    {
        if(time_to_exit_)
        {
            cout << "Error: System ID not received" << endl;
            return;
            usleep(100000);
        }
    }

    cout << "Found" << endl;

    if(!system_id_)
    {
        cout << "Got system ID: " << system_id_ << endl;
    }

    if(!comp_id_)
    {
        cout << "Got component ID: " << comp_id_ << endl;
    }


}

void ReadDataImpl::stop()
{
    pthread_join(read_thread_, NULL);
}

void ReadDataImpl::read_thread()
{
    reading_status_ = true;

    // cout << "Read thread started" << endl;

        // cout << "Reading messages" << endl;
    read_messages();
    usleep(20000);

    reading_status_ = false;

}

void ReadDataImpl::handle_quit(int sig)
{
}

void ReadDataImpl::start_read_thread()
{
    if(reading_status_ == true)
    {
        cout << "Error: Read thread already running" << endl;
        return;
    }
    else
    {
        read_thread();
    }
}

void *start_ReadDataImpl_read_thread(void *context)
{
    ReadDataImpl *read_data = (ReadDataImpl *)context;
    read_data->read_thread();
    return NULL;
}