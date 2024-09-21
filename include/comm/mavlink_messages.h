#ifndef MAVLINK_MESSAGES_H
#define MAVLINK_MESSAGES_H

#include "c_library_v2/common/mavlink.h"

struct TimeStamps
{
    TimeStamps()
    {
        reset_timestamps();
    }
    uint64_t heartbeat;
    uint64_t sys_status;
    uint64_t battery_status;
    uint64_t highres_imu;
    uint64_t attitude;

    void reset_timestamps()
    {
        heartbeat = 0;
        sys_status = 0;
        battery_status = 0;
        highres_imu = 0;
        attitude = 0;
    }
};

struct MavlinkMessages
{
    int sys_id;
    int comp_id;

    mavlink_heartbeat_t heartbeat;
    mavlink_sys_status_t sys_status;
    mavlink_battery_status_t battery_status;
    mavlink_highres_imu_t highres;
    mavlink_attitude_t attitude;

    TimeStamps time_stamps;

    void reset_timestamps()
    {
        time_stamps.reset_timestamps();
    }
};

#endif