/*
*****************************************************************************
@file         Deneyap_CiftKanalliCizgiAlgilama.h
@mainpage     Deneyap Dual Channel Line Follower TCRT5000 Arduino library header file
@version      v1.0.0
@date         June 23, 2022
@brief        This file contains all function prototypes and macros
              for Deneyap Dual Channel Line Follower TCRT5000 Arduino library
*****************************************************************************
*/

#ifndef __Deneyap_CiftKanalliCizgiAlgilama_H
#define __Deneyap_CiftKanalliCizgiAlgilama_H

#include <Wire.h>
#include <Arduino.h>

#define I2C_SLV_ADDR_DEFAULT (uint8_t)0x07
#define I2C_SLV_ADDR_ALT1 (uint8_t)(I2C_SLV_ADDR_DEFAULT + 1)
#define I2C_SLV_ADDR_ALT2 (uint8_t)(I2C_SLV_ADDR_DEFAULT + 2)
#define I2C_SLV_ADDR_ALT3 (uint8_t)(I2C_SLV_ADDR_DEFAULT + 3)

#define DATA_BUFFER_SIZE 2 // in Byte (max data size)

typedef struct { // Data packet (protocol) created by master
                 // for I2C data exchange process
    uint8_t command : 3;
    uint8_t dataSize : 2;
    uint8_t data[DATA_BUFFER_SIZE];
} LineFollower_DataPacket_TypeDef;

enum LineFollower_packetCommands { // Commands in data packet (protocol)
    DIG_READ_SENSOR1 = (uint8_t)0x00,
    DIG_READ_SENSOR2,
    AN_READ_SENSOR1,
    AN_READ_SENSOR2,
    LineFollower_CHANGE_ADDR,
    LineFollower_REQUEST_FW_VERSION,
};

class LineFollower {
public:
    /* Check device status */
    bool begin(uint8_t address, TwoWire &port = Wire);
    bool isConnected();
    uint16_t getFwVersion();
    bool setI2Caddress(uint8_t newAddress);

    /* Functions for data manipulation */
    bool ReadLineFollowerDigital1();
    bool ReadLineFollowerDigital2();
    uint16_t ReadLineFollowerAnalog1();
    uint16_t ReadLineFollowerAnalog2();

    uint8_t i2cData2;
    uint8_t i2cData1;

private:
    TwoWire *_i2cPort;                           // Port selection (0 or 1)
    uint8_t _address;                            // Device I2C address
    LineFollower_DataPacket_TypeDef _dataPacket; // Struct to transfer data over I2C interface

    /* I2C data transaction functions */
    uint8_t I2C_ReadData8bit(LineFollower_DataPacket_TypeDef *dataPacket);
    uint16_t I2C_ReadData16bit(LineFollower_DataPacket_TypeDef *dataPacket);
    uint16_t I2C_ReadFirmwareData16bit(LineFollower_DataPacket_TypeDef *dataPacket);
    bool I2C_SendDataPacket(LineFollower_DataPacket_TypeDef *dataPacket);
};

#endif /* __Deneyap_CiftKanalliCizgiAlgilama_H */
