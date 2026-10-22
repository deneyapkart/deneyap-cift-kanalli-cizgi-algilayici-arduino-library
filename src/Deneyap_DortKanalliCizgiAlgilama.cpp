/*
*****************************************************************************
@file         Deneyap_DortKanalliCizgiAlgilama.cpp
@mainpage     Deneyap 4 Channel Line Follower GP2S700HCP Arduino library
              source file
@version      v1.1.0
@date         October 21, 2026
@brief        Includes functions to control Deneyap Line Follower with
              GP2S700HCP sensors (LineFollower4Channel)

Calibration and line position functions are adapted from Pololu
QTRSensors library (https://github.com/pololu/qtr-sensors-arduino),
Copyright (c) Pololu Corporation, MIT License.

Library includes:
--> Configuration functions
--> Data manipulation functions
--> I2C communication functions
*****************************************************************************
*/

#include "Deneyap_CiftKanalliCizgiAlgilama.h"

/* Device Status Functions ---------------------------------------------------*/

/**
 * @brief  Configures I2C connection with user defined address and port
 * @param  address: I2C address of the device, port: I2C port number (0 or 1)
 * @retval connection status (1 --> connected, 0 --> not connected)
 */
bool LineFollower4Channel::begin(uint8_t address, TwoWire &wirePort) {
    _address = address;
    _i2cPort = &wirePort;
    _dataPacket = {0};
    _timeout = LINEFOLLOWER_4CH_DEFAULT_TIMEOUT;
    _maxValue = LINEFOLLOWER_4CH_DEFAULT_TIMEOUT;
    _dimmingLevel = 100;

    _i2cPort->begin();
#if defined(ARDUINO_DYM)
    _i2cPort->setClock(100000);
#else
    _i2cPort->setClock(50000);
#endif

    if (!isConnected())
        return false;

    delay(10);
    SetDimmingLevel(_dimmingLevel);
    delay(10);
    SetTimeout(_timeout);

    return true;
}

/**
 * @brief  Checks whether I2C connection established
 * @param  None
 * @retval connection status (1 --> connected, 0 --> not connected)
 */
bool LineFollower4Channel::isConnected() {
    _i2cPort->beginTransmission(_address);

    if (_i2cPort->endTransmission() == 0)
        return true;
    return false;
}

/**
 * @brief  Requests firmware version of the device
 * @param  None
 * @retval Device firmware version (high byte --> major, low byte --> minor)
 */
uint16_t LineFollower4Channel::getFwVersion() {
    _dataPacket.command = LineFollower4Channel_REQUEST_FW_VERSION;
    _dataPacket.dataSize = 0;
    return I2C_ReadData16bit(&_dataPacket);
}

/**
 * @brief  Sets (changes) I2C address of the device
 * @param  address: I2C address to be set
 * @retval Transmission status (1 --> No error, Otherwise --> Transmission error)
 */
bool LineFollower4Channel::setI2Caddress(uint8_t newAddress) {
    _dataPacket.command = LineFollower4Channel_CHANGE_ADDR;
    _dataPacket.dataSize = 1;
    _dataPacket.data[0] = newAddress;

    bool status = I2C_SendDataPacket(&_dataPacket);

    if (status == true) {
        _address = newAddress;
        return true;
    }
    else {
        return false;
    }
}

/* I2C Data Manipulation Functions -------------------------------------------*/

/**
 * @brief  Sets the timeout for RC sensors.
 * @param  timeout: The length of time, in microseconds, beyond which you
 *         consider the sensor reading completely black.
 * @retval Transmission status (1 --> No error, Otherwise --> Transmission error)
 */
bool LineFollower4Channel::SetTimeout(uint16_t timeout) {
    if (timeout > LINEFOLLOWER_4CH_MAX_TIMEOUT)
        timeout = LINEFOLLOWER_4CH_MAX_TIMEOUT;
    _timeout = timeout;
    _maxValue = timeout;
    _dataPacket.command = (uint8_t)LineFollower4Channel_SET_TIMEOUT;
    _dataPacket.dataSize = 2;
    _dataPacket.data[0] = timeout & 0xFF;
    _dataPacket.data[1] = (timeout >> 8) & 0xFF;
    return I2C_SendDataPacket(&_dataPacket);
}

/**
 * @brief  Sets the dimming level of the IR emitters.
 * @param  dimmingLevel: The dimming level (0 to 100). A dimming level of 100
 *         corresponds to full current and brightness, with lower dimming levels
 *         meaning lower currents.
 * @retval Transmission status (1 --> No error, Otherwise --> Transmission error)
 */
bool LineFollower4Channel::SetDimmingLevel(uint8_t dimmingLevel) {
    if (dimmingLevel > 100)
        dimmingLevel = 100;
    _dimmingLevel = dimmingLevel;
    _dataPacket.command = (uint8_t)LineFollower4Channel_SET_DIM_LEVEL;
    _dataPacket.dataSize = 1;
    _dataPacket.data[0] = dimmingLevel;
    return I2C_SendDataPacket(&_dataPacket);
}

/**
 * @brief  Turns the IR emitters on or off.
 * @param  emitterState: EMITTER_ON or EMITTER_OFF
 * @retval Transmission status (1 --> No error, Otherwise --> Transmission error)
 */
bool LineFollower4Channel::SetEmitter(uint8_t emitterState) {
    _dataPacket.command = (uint8_t)LineFollower4Channel_SET_EMITTER;
    _dataPacket.dataSize = 1;
    _dataPacket.data[0] = emitterState;
    return I2C_SendDataPacket(&_dataPacket);
}

/**
 * @brief  Reads raw values of all sensors.
 * @param  sensorValues: An array of LINEFOLLOWER_4CH_SENSOR_COUNT elements
 *         in which to store the raw sensor readings (0 to timeout).
 * @retval Read status (1 --> No error, 0 --> I2C error, array is not changed)
 */
bool LineFollower4Channel::ReadSensorValues(uint16_t *sensorValues) {
    _dataPacket.command = (uint8_t)LineFollower4Channel_READ_SENSOR_VALS;
    _dataPacket.dataSize = 0;
    return I2C_ReadSensorData(&_dataPacket, sensorValues);
}

/**
 * @brief  Reads the raw sensor values into an array.
 * @param  sensorValues: An array in which to store the raw sensor readings.
 * @param  mode: The emitter behavior during the read.
 * @retval Read status (1 --> No error, 0 --> I2C error)
 */
bool LineFollower4Channel::Read(uint16_t *sensorValues, ReadMode mode) {
    switch (mode) {
    case OFF:
        SetEmitter(EMITTER_OFF);
        // fall through
    case MANUAL:
        return ReadSensorValues(sensorValues);

    case ON:
    case ON_AND_OFF:
        SetEmitter(EMITTER_ON);
        {
            bool status = ReadSensorValues(sensorValues);
            SetEmitter(EMITTER_OFF); // turn emitters off even if the read failed
            if (!status)
                return false;
        }
        break;

    default: // invalid - do nothing
        return false;
    }

    if (mode == ON_AND_OFF) {
        // Take a second set of readings and return the values (on + max - off).
        uint16_t offValues[LINEFOLLOWER_4CH_SENSOR_COUNT];
        if (!ReadSensorValues(offValues))
            return false;

        for (uint8_t i = 0; i < LINEFOLLOWER_4CH_SENSOR_COUNT; i++) {
            sensorValues[i] += _maxValue - offValues[i];
            if (sensorValues[i] > _maxValue) {
                // This usually doesn't happen, because the sensor reading should
                // go up when the emitters are turned off.
                sensorValues[i] = _maxValue;
            }
        }
    }
    return true;
}

/**
 * @brief  Handles the actual calibration, including (re)allocating and
 *         initializing the storage for the calibration values if necessary.
 * @param  calibration: Struct to store calibration data.
 * @param  mode: The emitter behavior during the read.
 * @retval None
 */
void LineFollower4Channel::CalibrateOnOrOff(CalibrationData &calibration, ReadMode mode) {
    uint16_t sensorValues[LINEFOLLOWER_4CH_SENSOR_COUNT];
    uint16_t maxSensorValues[LINEFOLLOWER_4CH_SENSOR_COUNT];
    uint16_t minSensorValues[LINEFOLLOWER_4CH_SENSOR_COUNT];

    // (Re)allocate and initialize the arrays if necessary.
    if (!calibration.initialized) {
        uint16_t *oldMaximum = calibration.maximum;
        calibration.maximum = (uint16_t *)realloc(calibration.maximum,
                                                  sizeof(uint16_t) * LINEFOLLOWER_4CH_SENSOR_COUNT);
        if (calibration.maximum == nullptr) {
            // Memory allocation failed; don't continue.
            free(oldMaximum); // deallocate any memory used by old array
            return;
        }

        uint16_t *oldMinimum = calibration.minimum;
        calibration.minimum = (uint16_t *)realloc(calibration.minimum,
                                                  sizeof(uint16_t) * LINEFOLLOWER_4CH_SENSOR_COUNT);
        if (calibration.minimum == nullptr) {
            // Memory allocation failed; don't continue.
            free(oldMinimum); // deallocate any memory used by old array
            return;
        }

        // Initialize the max and min calibrated values to values that
        // will cause the first reading to update them.
        for (uint8_t i = 0; i < LINEFOLLOWER_4CH_SENSOR_COUNT; i++) {
            calibration.maximum[i] = 0;
            calibration.minimum[i] = _maxValue;
        }

        calibration.initialized = true;
    }

    uint8_t validReads = 0;
    for (uint8_t j = 0; j < 10; j++) {
        if (!Read(sensorValues, mode))
            continue; // skip readings with I2C error

        for (uint8_t i = 0; i < LINEFOLLOWER_4CH_SENSOR_COUNT; i++) {
            // set the max we found THIS time
            if ((validReads == 0) || (sensorValues[i] > maxSensorValues[i]))
                maxSensorValues[i] = sensorValues[i];

            // set the min we found THIS time
            if ((validReads == 0) || (sensorValues[i] < minSensorValues[i]))
                minSensorValues[i] = sensorValues[i];
        }
        validReads++;
    }

    if (validReads == 0)
        return;

    // record the min and max calibration values
    for (uint8_t i = 0; i < LINEFOLLOWER_4CH_SENSOR_COUNT; i++) {
        // Update maximum only if the min of 10 readings was still higher than it
        // (we got 10 readings in a row higher than the existing maximum).
        if (minSensorValues[i] > calibration.maximum[i])
            calibration.maximum[i] = minSensorValues[i];

        // Update minimum only if the max of 10 readings was still lower than it
        // (we got 10 readings in a row lower than the existing minimum).
        if (maxSensorValues[i] < calibration.minimum[i])
            calibration.minimum[i] = maxSensorValues[i];
    }
}

/**
 * @brief  Reads the sensors for calibration.
 * @param  mode: The emitter behavior during the read (MANUAL is not supported).
 * @retval None
 */
void LineFollower4Channel::Calibrate(ReadMode mode) {
    // manual emitter control is not supported
    if (mode == MANUAL)
        return;

    if (mode == ON || mode == ON_AND_OFF)
        CalibrateOnOrOff(calibrationOn, ON);

    if (mode == ON_AND_OFF || mode == OFF)
        CalibrateOnOrOff(calibrationOff, OFF);
}

/**
 * @brief  Resets all calibration that has been done.
 * @param  None
 * @retval None
 */
void LineFollower4Channel::ResetCalibration() {
    for (uint8_t i = 0; i < LINEFOLLOWER_4CH_SENSOR_COUNT; i++) {
        if (calibrationOn.maximum)
            calibrationOn.maximum[i] = 0;
        if (calibrationOff.maximum)
            calibrationOff.maximum[i] = 0;
        if (calibrationOn.minimum)
            calibrationOn.minimum[i] = _maxValue;
        if (calibrationOff.minimum)
            calibrationOff.minimum[i] = _maxValue;
    }
}

/**
 * @brief  Reads the sensors and provides calibrated values between 0 and 1000.
 *         (0 --> maximum reflectance (white), 1000 --> minimum reflectance (black))
 * @param  sensorValues: An array in which to store the calibrated sensor readings.
 * @param  mode: The emitter behavior during the read (MANUAL is not supported).
 * @retval Read status (1 --> No error, 0 --> not calibrated, MANUAL mode or I2C error,
 *         array is not changed)
 */
bool LineFollower4Channel::ReadCalibrated(uint16_t *sensorValues, ReadMode mode) {
    // manual emitter control is not supported
    if (mode == MANUAL)
        return false;

    // if not calibrated, do nothing
    if (mode == ON || mode == ON_AND_OFF) {
        if (!calibrationOn.initialized)
            return false;
    }

    if (mode == OFF || mode == ON_AND_OFF) {
        if (!calibrationOff.initialized)
            return false;
    }

    // read the needed values
    if (!Read(sensorValues, mode))
        return false;

    for (uint8_t i = 0; i < LINEFOLLOWER_4CH_SENSOR_COUNT; i++) {
        uint16_t calmin, calmax;

        // find the correct calibration
        if (mode == ON) {
            calmax = calibrationOn.maximum[i];
            calmin = calibrationOn.minimum[i];
        }
        else if (mode == OFF) {
            calmax = calibrationOff.maximum[i];
            calmin = calibrationOff.minimum[i];
        }
        else { // ON_AND_OFF
            if (calibrationOff.minimum[i] < calibrationOn.minimum[i]) {
                // no meaningful signal
                calmin = _maxValue;
            }
            else {
                // this won't go past _maxValue
                calmin = calibrationOn.minimum[i] + _maxValue - calibrationOff.minimum[i];
            }

            if (calibrationOff.maximum[i] < calibrationOn.maximum[i]) {
                // no meaningful signal
                calmax = _maxValue;
            }
            else {
                // this won't go past _maxValue
                calmax = calibrationOn.maximum[i] + _maxValue - calibrationOff.maximum[i];
            }
        }

        uint16_t denominator = calmax - calmin;
        int32_t value = 0;

        if (denominator != 0)
            value = (((int32_t)sensorValues[i]) - calmin) * 1000 / denominator;

        if (value < 0)
            value = 0;
        else if (value > 1000)
            value = 1000;

        sensorValues[i] = value;
    }
    return true;
}

/**
 * @brief  Reads calibrated sensors and estimates the line position.
 * @param  sensorValues: An array in which to store the calibrated sensor readings.
 * @param  mode: The emitter behavior during the read (MANUAL is not supported).
 * @param  invertReadings: false --> black line, true --> white line
 * @retval Line position (0 --> under sensor 1, 1000 --> under sensor 2, ...)
 *         Last known position if the sensors could not be read (not calibrated,
 *         MANUAL mode or I2C error)
 */
uint16_t LineFollower4Channel::ReadLinePrivate(uint16_t *sensorValues, ReadMode mode,
                                               bool invertReadings) {
    bool onLine = false;
    uint32_t avg = 0; // this is for the weighted total
    uint16_t sum = 0; // this is for the denominator, which is <= 64000

    // do not estimate the position from stale or uninitialized values
    if (!ReadCalibrated(sensorValues, mode))
        return _lastPosition;

    for (uint8_t i = 0; i < LINEFOLLOWER_4CH_SENSOR_COUNT; i++) {
        uint16_t value = sensorValues[i];
        if (invertReadings)
            value = 1000 - value;

        // keep track of whether we see the line at all
        if (value > 200)
            onLine = true;

        // only average in values that are above a noise threshold
        if (value > 50) {
            avg += (uint32_t)value * (i * 1000);
            sum += value;
        }
    }

    if (!onLine) {
        // If it last read to the left of center, return 0.
        if (_lastPosition < (LINEFOLLOWER_4CH_SENSOR_COUNT - 1) * 1000 / 2)
            return 0;
        // If it last read to the right of center, return the max.
        else
            return (LINEFOLLOWER_4CH_SENSOR_COUNT - 1) * 1000;
    }

    _lastPosition = avg / sum;
    return _lastPosition;
}

/* I2C Data Transaction Functions --------------------------------------------*/

/**
 * @brief  Reads 16bit data from I2C interface (low byte first)
 * @param  dataPacket: includes protocol to request data
 * @retval I2C 16bit data
 */
uint16_t LineFollower4Channel::I2C_ReadData16bit(LineFollower_DataPacket_TypeDef *dataPacket) {
    _i2cPort->beginTransmission(_address);
    _i2cPort->write(dataPacket->command);
    _i2cPort->endTransmission();

    if (_i2cPort->requestFrom(_address, static_cast<uint8_t>(2)) == 2) {
        uint16_t i2cData = _i2cPort->read();
        i2cData |= (_i2cPort->read() << 8);
        return i2cData;
    }
    return 0;
}

/**
 * @brief  Reads all sensor values from I2C interface (high byte first)
 * @param  dataPacket: includes protocol to request data
 * @param  sensorValues: An array in which to store the sensor readings.
 * @retval Read status (1 --> No error, 0 --> I2C error)
 */
bool LineFollower4Channel::I2C_ReadSensorData(LineFollower_DataPacket_TypeDef *dataPacket,
                                              uint16_t *sensorValues) {
    const uint8_t byteCount = LINEFOLLOWER_4CH_SENSOR_COUNT * 2;

    _i2cPort->beginTransmission(_address);
    _i2cPort->write(dataPacket->command);
    _i2cPort->endTransmission();

    if (_i2cPort->requestFrom(_address, byteCount) != byteCount) {
        while (_i2cPort->available())
            _i2cPort->read(); // discard incomplete data
        return false;
    }

    for (uint8_t i = 0; i < LINEFOLLOWER_4CH_SENSOR_COUNT; i++) {
        uint16_t i2cData = _i2cPort->read() << 8;
        i2cData |= _i2cPort->read();
        sensorValues[i] = i2cData;
    }
    return true;
}

/**
 * @brief  Sends data packet based on a custom defined protocol
 * @param  dataPacket: includes all related data
 * @retval Transmission status (1 --> No error, Otherwise --> Transmission error)
 */
bool LineFollower4Channel::I2C_SendDataPacket(LineFollower_DataPacket_TypeDef *dataPacket) {
    _i2cPort->beginTransmission(_address);
    _i2cPort->write(dataPacket->command);
    _i2cPort->write(dataPacket->dataSize);

    for (uint8_t i = 0; i < dataPacket->dataSize; i++)
        _i2cPort->write(dataPacket->data[i]);

    if (_i2cPort->endTransmission() == 0)
        return true;
    return false;
}
