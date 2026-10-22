/*
*****************************************************************************
@file         Deneyap_CiftKanalliCizgiAlgilama.h
@mainpage     Deneyap Line Follower Arduino library header file
@version      v1.1.0
@date         October 21, 2026
@brief        This file contains all function prototypes and macros
              for Deneyap Line Follower Arduino library

Supported modules:
--> LineFollower2Channel : Deneyap Dual Channel Line Follower (TCRT5000)
--> LineFollower4Channel : Deneyap Line Follower with GP2S700HCP sensors
*****************************************************************************
*/

#ifndef DENEYAP_CIFTKANALLICIZGIALGILAMA_H
#define DENEYAP_CIFTKANALLICIZGIALGILAMA_H

#include <Wire.h>
#include <Arduino.h>

#define I2C_SLV_ADDR_DEFAULT (uint8_t)0x07 // default address
#define I2C_SLV_ADDR_ALT1 (uint8_t)0x08    // ADR1 pad shorted
#define I2C_SLV_ADDR_ALT2 (uint8_t)0x03    // ADR2 pad shorted
#define I2C_SLV_ADDR_ALT3 (uint8_t)0x04    // ADR1 and ADR2 pads shorted

#define DATA_BUFFER_SIZE 2 // in Byte (max data size)

typedef struct { // Data packet (protocol) created by master
                 // for I2C data exchange process
    uint8_t command : 3;
    uint8_t dataSize : 2;
    uint8_t data[DATA_BUFFER_SIZE];
} LineFollower_DataPacket_TypeDef;

/* 2 Channel Line Follower (TCRT5000) ----------------------------------------*/

enum LineFollower_packetCommands { // Commands in data packet (protocol)
    DIG_READ_SENSOR1 = (uint8_t)0x00,
    DIG_READ_SENSOR2,
    AN_READ_SENSOR1,
    AN_READ_SENSOR2,
    LineFollower_CHANGE_ADDR,
    LineFollower_REQUEST_FW_VERSION,
};

class LineFollower2Channel {
public:
    /* Check device status */
    bool begin(uint8_t address = I2C_SLV_ADDR_DEFAULT, TwoWire &port = Wire);
    bool isConnected();
    uint16_t getFwVersion();
    bool setI2Caddress(uint8_t newAddress);

    /* Functions for data manipulation */
    bool ReadLineFollowerDigital1();
    bool ReadLineFollowerDigital2();
    uint16_t ReadLineFollowerAnalog1();
    uint16_t ReadLineFollowerAnalog2();

private:
    TwoWire *_i2cPort;                           // Port selection (0 or 1)
    uint8_t _address;                            // Device I2C address
    LineFollower_DataPacket_TypeDef _dataPacket; // Struct to transfer data over I2C interface

    /* I2C data transaction functions */
    uint8_t I2C_ReadData8bit(LineFollower_DataPacket_TypeDef *dataPacket);
    uint16_t I2C_ReadData16bit(LineFollower_DataPacket_TypeDef *dataPacket);
    bool I2C_SendDataPacket(LineFollower_DataPacket_TypeDef *dataPacket);
};

typedef LineFollower2Channel LineFollower; // Kept for compatibility with v1.0.x sketches

/* 4 Channel Line Follower (GP2S700HCP) --------------------------------------*/

#define LINEFOLLOWER_4CH_SENSOR_COUNT 4
#define LINEFOLLOWER_4CH_DEFAULT_TIMEOUT (uint16_t)1500 // in microseconds
#define LINEFOLLOWER_4CH_MAX_TIMEOUT (uint16_t)32767    // in microseconds

#define EMITTER_ON 1
#define EMITTER_OFF 0

enum LineFollower4Channel_packetCommands { // Commands in data packet (protocol)
    LineFollower4Channel_SET_TIMEOUT = (uint8_t)0x01,
    LineFollower4Channel_SET_DIM_LEVEL,
    LineFollower4Channel_SET_EMITTER,
    LineFollower4Channel_READ_SENSOR_VALS,
    LineFollower4Channel_CHANGE_ADDR,
    LineFollower4Channel_REQUEST_FW_VERSION,
};

class LineFollower4Channel {
public:
    enum ReadMode { // Emitter behavior during a read
        OFF = (uint8_t)0x00,
        ON,
        ON_AND_OFF,
        MANUAL,
    };

    struct CalibrationData {
        bool initialized = false;
        uint16_t *minimum = nullptr;
        uint16_t *maximum = nullptr;
    };

    /* Check device status */
    bool begin(uint8_t address = I2C_SLV_ADDR_DEFAULT, TwoWire &port = Wire);
    bool isConnected();
    uint16_t getFwVersion();
    bool setI2Caddress(uint8_t newAddress);

    /* Functions for data manipulation */
    bool SetTimeout(uint16_t timeout);
    uint16_t GetTimeout() { return _timeout; }
    bool SetDimmingLevel(uint8_t dimmingLevel);
    uint8_t GetDimmingLevel() { return _dimmingLevel; }
    bool SetEmitter(uint8_t emitterState);
    bool ReadSensorValues(uint16_t *sensorValues);
    bool Read(uint16_t *sensorValues, ReadMode mode = MANUAL);
    void Calibrate(ReadMode mode = ON);
    void ResetCalibration();
    bool ReadCalibrated(uint16_t *sensorValues, ReadMode mode = ON);

    uint16_t ReadLineBlack(uint16_t *sensorValues, ReadMode mode = ON) {
        return ReadLinePrivate(sensorValues, mode, false);
    }

    uint16_t ReadLineWhite(uint16_t *sensorValues, ReadMode mode = ON) {
        return ReadLinePrivate(sensorValues, mode, true);
    }

    CalibrationData calibrationOn;  // Data from calibrating with emitters on
    CalibrationData calibrationOff; // Data from calibrating with emitters off

private:
    TwoWire *_i2cPort;                           // Port selection (0 or 1)
    uint8_t _address;                            // Device I2C address
    uint16_t _timeout;                           // RC sensors timeout
    uint16_t _maxValue;                          // Max value returned by ReadSensorValues()
    uint8_t _dimmingLevel;                       // IR emitters brightness level
    LineFollower_DataPacket_TypeDef _dataPacket; // Struct to transfer data over I2C interface
    uint16_t _lastPosition = 0;

    void CalibrateOnOrOff(CalibrationData &calibration, ReadMode mode);
    uint16_t ReadLinePrivate(uint16_t *sensorValues, ReadMode mode, bool invertReadings);

    /* I2C data transaction functions */
    uint16_t I2C_ReadData16bit(LineFollower_DataPacket_TypeDef *dataPacket);
    bool I2C_ReadSensorData(LineFollower_DataPacket_TypeDef *dataPacket, uint16_t *sensorValues);
    bool I2C_SendDataPacket(LineFollower_DataPacket_TypeDef *dataPacket);
};

#endif /* DENEYAP_CIFTKANALLICIZGIALGILAMA_H */
