/**
 * @file ARMAVLINK_MissionItemUtils.c
 * @brief ARMavlink library Utils about mission items
 * @date 14/05/2014
 * @author djavan.bertrand@parrot.com
 */
#include <stdlib.h>
#include "ARMAVLINK_MissionItemUtils.h"
#include <libARSAL/ARSAL_Print.h>

#define ARMAVLINK_MISSION_ITEM_UTILS_TAG    "ARMAVLINK_MissionItemUtil"

// default mission item values
#define ARMAVLINK_MISSION_ITEM_UTILS_EMPTY_PARAM                        0
#define ARMAVLINK_MISSION_ITEM_UTILS_DEFAULT_SEQ                        0
#define ARMAVLINK_MISSION_ITEM_UTILS_DEFAULT_CURRENT                    0
#define ARMAVLINK_MISSION_ITEM_UTILS_DEFAULT_TARGET_SYSTEM              1
#define ARMAVLINK_MISSION_ITEM_UTILS_DEFAULT_TARGET_COMPONENT           1
#define ARMAVLINK_MISSION_ITEM_UTILS_DEFAULT_AUTOCONTINUE               1
#define ARMAVLINK_MISSION_ITEM_UTILS_DEFAULT_POSITION_REFENTIAL MAV_FRAME_GLOBAL_RELATIVE_ALT // in common.h


// default MAV_CMD_NAV_WAYPOINT values
#define ARMAVLINK_MISSION_ITEM_UTILS_WAYPOINT_DEFAULT_RADIUS            0.0f    // in meters
#define ARMAVLINK_MISSION_ITEM_UTILS_WAYPOINT_DEFAULT_TIME              0.0f    // in ms
#define ARMAVLINK_MISSION_ITEM_UTILS_WAYPOINT_DEFAULT_ORBIT             0.0f

int ARMAVLINK_MissionItemUtils_MissionItemsAreEquals(const mavlink_mission_item_t *const missionItem1, const mavlink_mission_item_t *const missionItem2)
{
    int equal = 0;
    
    if ((missionItem1->param1 == missionItem2->param1) &&
        (missionItem1->param2 == missionItem2->param2) &&
        (missionItem1->param3 == missionItem2->param3) &&
        (missionItem1->param4 == missionItem2->param4) &&
        (missionItem1->x == missionItem2->x) &&
        (missionItem1->y == missionItem2->y) &&
        (missionItem1->z == missionItem2->z) &&
        (missionItem1->seq == missionItem2->seq) &&
        (missionItem1->command == missionItem2->command) &&
        (missionItem1->target_system == missionItem2->target_system) &&
        (missionItem1->target_component == missionItem2->target_component) &&
        (missionItem1->frame == missionItem2->frame) &&
        (missionItem1->current == missionItem2->current) &&
        (missionItem1->autocontinue == missionItem2->autocontinue))
    {
        equal = 1;
    }
    
    return equal;
    
}

eARMAVLINK_ERROR ARMAVLINK_MissionItemUtils_CopyMavlinkMissionItem(mavlink_mission_item_t * missionItemCpy, const mavlink_mission_item_t *const missionItem)
{
    eARMAVLINK_ERROR error = ARMAVLINK_OK;
    
    if ((missionItem == NULL) || (missionItemCpy == NULL))
    {
        error = ARMAVLINK_ERROR_BAD_PARAMETER;
    }
    
    if (error == ARMAVLINK_OK)
    {
        memcpy(missionItemCpy, missionItem, sizeof(mavlink_mission_item_t));
    }
    
    return error;
}

eARMAVLINK_ERROR ARMAVLINK_MissionItemUtils_CreateMavlinkMissionItemWithAllParams(mavlink_mission_item_t* missionItem, float param1, float param2, float param3, float param4, float latitude, float longitude, float altitude, int command, int seq, int frame, int current, int autocontinue)
{
    eARMAVLINK_ERROR error = ARMAVLINK_OK;
    
    if (missionItem != NULL)
    {
        missionItem->param1            = param1;
        missionItem->param2            = param2;
        missionItem->param3            = param3;
        missionItem->param4            = param4;
        missionItem->x                 = latitude;
        missionItem->y                 = longitude;
        missionItem->z                 = altitude;
        missionItem->seq               = seq;
        missionItem->command           = command;
        missionItem->target_system     = ARMAVLINK_MISSION_ITEM_UTILS_DEFAULT_TARGET_SYSTEM,
        missionItem->target_component  = ARMAVLINK_MISSION_ITEM_UTILS_DEFAULT_TARGET_COMPONENT;
        missionItem->frame             = frame;
        missionItem->current           = current;
        missionItem->autocontinue      = autocontinue;
    }
    else
    {
        error = ARMAVLINK_ERROR_BAD_PARAMETER;
    }
    
    return error;
}

/* ******************* Specific commands ***************** */

/* MAV_CMD_NAV_WAYPOINT */
eARMAVLINK_ERROR ARMAVLINK_MissionItemUtils_CreateMavlinkNavWaypointMissionItem(mavlink_mission_item_t* missionItem, float latitude, float longitude, float altitude, float yaw)
{
    return ARMAVLINK_MissionItemUtils_CreateMavlinkMissionItemWithAllParams(
                                                                            missionItem,
                                                                            ARMAVLINK_MISSION_ITEM_UTILS_WAYPOINT_DEFAULT_RADIUS,
                                                                            ARMAVLINK_MISSION_ITEM_UTILS_WAYPOINT_DEFAULT_TIME,
                                                                            ARMAVLINK_MISSION_ITEM_UTILS_WAYPOINT_DEFAULT_ORBIT,
                                                                            yaw,
                                                                            latitude,
                                                                            longitude,
                                                                            altitude,
                                                                            MAV_CMD_NAV_WAYPOINT,
                                                                            ARMAVLINK_MISSION_ITEM_UTILS_DEFAULT_SEQ,
                                                                            ARMAVLINK_MISSION_ITEM_UTILS_DEFAULT_POSITION_REFENTIAL,
                                                                            ARMAVLINK_MISSION_ITEM_UTILS_DEFAULT_CURRENT,
                                                                            ARMAVLINK_MISSION_ITEM_UTILS_DEFAULT_AUTOCONTINUE
                                                                            );
}

/* MAV_CMD_NAV_LAND */
eARMAVLINK_ERROR ARMAVLINK_MissionItemUtils_CreateMavlinkLandMissionItem(mavlink_mission_item_t* missionItem, float latitude, float longitude, float altitude, float yaw)
{
    // TODO: remove this message
    ARSAL_PRINT (ARSAL_PRINT_ERROR, ARMAVLINK_MISSION_ITEM_UTILS_TAG, "Watch out, the MAV_CMD_NAV_LAND item creation has not been tested yet");
    return ARMAVLINK_MissionItemUtils_CreateMavlinkMissionItemWithAllParams(
                                                                            missionItem,
                                                                            ARMAVLINK_MISSION_ITEM_UTILS_EMPTY_PARAM,
                                                                            ARMAVLINK_MISSION_ITEM_UTILS_EMPTY_PARAM,
                                                                            ARMAVLINK_MISSION_ITEM_UTILS_EMPTY_PARAM,
                                                                            yaw,
                                                                            latitude,
                                                                            longitude,
                                                                            altitude,
                                                                            MAV_CMD_NAV_LAND,
                                                                            ARMAVLINK_MISSION_ITEM_UTILS_DEFAULT_SEQ,
                                                                            ARMAVLINK_MISSION_ITEM_UTILS_DEFAULT_POSITION_REFENTIAL,
                                                                            ARMAVLINK_MISSION_ITEM_UTILS_DEFAULT_CURRENT,
                                                                            ARMAVLINK_MISSION_ITEM_UTILS_DEFAULT_AUTOCONTINUE
                                                                            );
}

/* MAV_CMD_NAV_TAKEOFF */
eARMAVLINK_ERROR ARMAVLINK_MissionItemUtils_CreateMavlinkTakeoffMissionItem(mavlink_mission_item_t* missionItem, float latitude, float longitude, float altitude, float yaw, float pitch)
{
    // TODO: remove this message
    ARSAL_PRINT (ARSAL_PRINT_ERROR, ARMAVLINK_MISSION_ITEM_UTILS_TAG, "Watch out, the MAV_CMD_NAV_TAKEOFF item creation has not been tested yet");
    return ARMAVLINK_MissionItemUtils_CreateMavlinkMissionItemWithAllParams(
                                                                            missionItem,
                                                                            pitch,
                                                                            ARMAVLINK_MISSION_ITEM_UTILS_EMPTY_PARAM,
                                                                            ARMAVLINK_MISSION_ITEM_UTILS_EMPTY_PARAM,
                                                                            yaw,
                                                                            latitude,
                                                                            longitude,
                                                                            altitude,
                                                                            MAV_CMD_NAV_TAKEOFF,
                                                                            ARMAVLINK_MISSION_ITEM_UTILS_DEFAULT_SEQ,
                                                                            ARMAVLINK_MISSION_ITEM_UTILS_DEFAULT_POSITION_REFENTIAL,
                                                                            ARMAVLINK_MISSION_ITEM_UTILS_DEFAULT_CURRENT,
                                                                            ARMAVLINK_MISSION_ITEM_UTILS_DEFAULT_AUTOCONTINUE
                                                                            );
}

/* MAV_CMD_NAV_DO_CHANGE_SPEED */
eARMAVLINK_ERROR ARMAVLINK_MissionItemUtils_CreateMavlinkChangeSpeedMissionItem(mavlink_mission_item_t* missionItem, int groundSpeed, float speed, float throttle)
{
    // TODO: remove this message
    ARSAL_PRINT (ARSAL_PRINT_ERROR, ARMAVLINK_MISSION_ITEM_UTILS_TAG, "Watch out, the MAV_CMD_NAV_DO_CHANGE_SPEED item creation has not been tested yet");
    eARMAVLINK_ERROR error = ARMAVLINK_OK;
    if ((groundSpeed != 0) && (groundSpeed != 1))
    {
        error = ARMAVLINK_ERROR_BAD_PARAMETER;
    }
    
    if (error == ARMAVLINK_OK)
    {
        error = ARMAVLINK_MissionItemUtils_CreateMavlinkMissionItemWithAllParams(
                                                                                 missionItem,
                                                                                 groundSpeed,
                                                                                 speed,
                                                                                 throttle,
                                                                                 ARMAVLINK_MISSION_ITEM_UTILS_EMPTY_PARAM,
                                                                                 ARMAVLINK_MISSION_ITEM_UTILS_EMPTY_PARAM,
                                                                                 ARMAVLINK_MISSION_ITEM_UTILS_EMPTY_PARAM,
                                                                                 ARMAVLINK_MISSION_ITEM_UTILS_EMPTY_PARAM,
                                                                                 MAV_CMD_DO_CHANGE_SPEED,
                                                                                 ARMAVLINK_MISSION_ITEM_UTILS_DEFAULT_SEQ,
                                                                                 ARMAVLINK_MISSION_ITEM_UTILS_DEFAULT_POSITION_REFENTIAL,
                                                                                 ARMAVLINK_MISSION_ITEM_UTILS_DEFAULT_CURRENT,
                                                                                 ARMAVLINK_MISSION_ITEM_UTILS_DEFAULT_AUTOCONTINUE
                                                                                 );
    }
    
    return error;
}