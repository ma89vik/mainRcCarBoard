#include "gps_handler.h"
#include "board.h"
#include "linear_buffer.h"
#include "log.h"
#include "serial_device.h"
#include <stdio.h>
#include <string.h>
/**
 * @brief Initializes the GPS sensor and the underlying uart driver
 *
 */

#define GPS_MSG_MAX_LEN 82
#define LOC_STR_MAX_LEN 15
#define DELIMITER 0x0A

static enum MsgType { LOC = 1 };
static enum MsgParseResult {
    SUCCESS,
    IN_PROGRESS,
    INVALID_FORMAT,
    NO_DELIMITER,
    UNPARSED_TYPE
};
static enum fieldGPRMC {
    TIME = 1,
    STATUS,
    LATITUDE,
    N_OR_S,
    LONGITUDE,
    E_OR_W,
    SPEED,
    COURSE,
    DATE,
    W_OR_E,
    CHECKSUM
};

static LinearBuffer_t msg_buf;
static uint8_t buf[GPS_MSG_MAX_LEN];

typedef struct GpsLocations
{
    // Locations as integers for use in calculations
    uint16_t latDeg;
    uint16_t northMin;
    uint16_t northSec;
    uint16_t longDeg;
    uint16_t westMin;
    uint16_t westSec;

    // Location as strings
    char latitude[LOC_STR_MAX_LEN];
    char longitude[LOC_STR_MAX_LEN];

    bool valid;

} GpsLocation;

static GpsLocation currentLocation;
static enum MsgParseResult parseMsg();
static enum MsgParseResult parse_NMEA();

void gps_init()
{

    msg_buf = linear_buf_init(buf, GPS_MSG_MAX_LEN);

    serial_init(&deviceGps);
}

void gps_update()
{
    // Check if we have received a full GPS msg
    if (parseMsg())
    {
        // Handle message
    }
}

static enum MsgParseResult parseMsg()
{
    uint8_t byte;

    // char *test =
    // "$GPRMC,220516,A,5133.82,N,00042.24,W,173.8,231.8,130694,004.2,W*70\x0A";
    // int16_t bytesToRead = strlen(test)+1;

    while (serial_read_byte(&deviceGps, &byte))
    {
        // Check if end of msg
        if (byte == DELIMITER)
        {
            // linear buffer contains a full message
            // Add checks for CRC etc here
            parse_NMEA();
            linear_buf_clear(&msg_buf);
            return SUCCESS;
        }
        else
        {
            // Keep appending to linear buffer until a delimiter is found
            if (!linear_buf_push(&msg_buf, byte))
            {
                // Buffer full, but no delimiter found. Assume corrupted message
                // and reset buffer
                linear_buf_clear(&msg_buf);
                LOG_WARN("GPS: Msg w no delim\n");
                return NO_DELIMITER;
            }
        }
    }
    return IN_PROGRESS;
}

static void decode_GPRMC(char *payload, uint16_t len)
{
    char *msgField;
    enum fieldGPRMC index = 1;

    while ((msgField = strsep(&payload, ",")) != NULL)
    {
        switch (index)
        {
        case TIME:
            break;

        case STATUS:
            if (msgField[0] == 'V')
            {
                // navigation receiver warning, dont update location
                return;
            }
            break;

        case LATITUDE:
            strncpy(currentLocation.latitude, msgField, LOC_STR_MAX_LEN);
            break;

        case LONGITUDE:
            strncpy(currentLocation.longitude, msgField, LOC_STR_MAX_LEN);
            break;

        default:
            break;
        }
        index++;
    }
}

static enum MsgParseResult parse_NMEA()
{
    // Buffer contains a full message
    int16_t i = 0;
    int16_t msgLen = msg_buf.bytesWritten;

    char type[6];

    if (msg_buf.buffer[i++] != '$')
    {
        return INVALID_FORMAT;
    }

    memcpy(type, &msg_buf.buffer[i], 5);
    i += 6;

    if (!strncmp(type, "GPRMC", 5))
    {
        LOG_DEBUG("found GPRMC");
        // Strip away type and decde payload
        decode_GPRMC(&(msg_buf.buffer[i]), msgLen - i);
    }
    else
    {
        // Only care about GPRMC messages
        return UNPARSED_TYPE;
    }
}
