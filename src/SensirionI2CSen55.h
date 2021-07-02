/*
 * THIS FILE IS AUTOMATICALLY GENERATED
 *
 * I2C-Generator: 0.2.0
 * Yaml Version: 0.5.1
 * Template Version: 0.7.0-8-gbdfd7a4
 */
/*
 * Copyright (c) 2021, Sensirion AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Sensirion AG nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SENSIRIONI2CSEN55_H
#define SENSIRIONI2CSEN55_H

#include <Wire.h>

#include <SensirionCore.h>

class SensirionI2CSen55 {

  public:
    SensirionI2CSen55();
    /**
     * begin() - Initializes the SensirionI2CSen55 class.
     *
     * @param serial Arduino stream object to be communicated with.
     *
     */
    void begin(TwoWire& i2cBus);

    /**
     * startMeasurement() - Starts a continuous measurement.
     *
     * @note After starting the measurement, it takes some time (~1s) until the
     * first measurement results are available. You could poll with the command
     * 0x0202 \"Read Data Ready\" to check when the results are ready to read.
     *
     * @return 0 on success, an error code otherwise
     */
    uint16_t startMeasurement(void);

    /**
     * stopMeasurement() - Stops the measurement and returns to idle mode.
     *
     * @return 0 on success, an error code otherwise
     */
    uint16_t stopMeasurement(void);

    /**
     * readDataReady() - This command can be used to check if new measurement
     * results are ready to read. The data ready flag is automatically reset
     * after reading the measurement values with the 0x03.. \"Read Measured
     * Values\" commands.
     *
     * @param padding Padding byte, always 0x00.
     *
     * @param dataReady True (0x01) if data is ready, False (0x00) if not.
     *
     * @return 0 on success, an error code otherwise
     */
    uint16_t readDataReady(bool& dataReady);

    /**
     * readMeasuredPmValuesFloat() - Returns the measured particulate matter
     * values as floating point numbers. The command 0x0202 \"Read Data Ready\"
     * can be used to check if new data is available since the last read
     * operation. If no new data is available, the previous values will be
     * returned again. If no data is available at all (e.g. measurement not
     * running for at least one Second), NaN is returned for all values.
     *
     * @param massConcentrationPm1p0 Value is returned in the unit µg/m³.
     *
     * @param massConcentrationPm2p5 Value is returned in the unit µg/m³.
     *
     * @param massConcentrationPm4p0 Value is returned in the unit µg/m³.
     *
     * @param massConcentrationPm10p0 Value is returned in the unit µg/m³.
     *
     * @param numberConcentrationPm0p5 Value is returned in the unit #/cm³.
     *
     * @param numberConcentrationPm1p0 Value is returned in the unit #/cm³.
     *
     * @param numberConcentrationPm2p5 Value is returned in the unit #/cm³.
     *
     * @param numberConcentrationPm4p0 Value is returned in the unit #/cm³.
     *
     * @param numberConcentrationPm10p0 Value is returned in the unit #/cm³.
     *
     * @param typicalParticleSize Value is returned in the unit µm.
     *
     * @return 0 on success, an error code otherwise
     */
    uint16_t readMeasuredPmValuesFloat(
        float& massConcentrationPm1p0, float& massConcentrationPm2p5,
        float& massConcentrationPm4p0, float& massConcentrationPm10p0,
        float& numberConcentrationPm0p5, float& numberConcentrationPm1p0,
        float& numberConcentrationPm2p5, float& numberConcentrationPm4p0,
        float& numberConcentrationPm10p0, float& typicalParticleSize);

    /**
     * readMeasuredValues() - Returns the measured values. The command 0x0202
    \"Read Data Ready\" can be used to check if new data is available since the
    last read operation. If no new data is available, the previous values will
    be returned again. If no data is available at all (e.g. measurement not
    running for at least one Second), all values will be at their upper limit
    (0xFFFF for `uint16`, 0x7FFF for `int16`).
     *
     * @param massConcentrationPm1p0 Value is scaled with factor 10: PM1.0
    [µg/m³] = value / 10

    *Note: If this value is unknown, 0xFFFF is returned.*
     *
     * @param massConcentrationPm2p5 Value is scaled with factor 10: PM2.5
    [µg/m³] = value / 10

    *Note: If this value is unknown, 0xFFFF is returned.*
     *
     * @param massConcentrationPm4p0 Value is scaled with factor 10: PM4.0
    [µg/m³] = value / 10

    *Note: If this value is unknown, 0xFFFF is returned.*
     *
     * @param massConcentrationPm10p0 Value is scaled with factor 10: PM10.0
    [µg/m³] = value / 10

    *Note: If this value is unknown, 0xFFFF is returned.*
     *
     * @param ambientHumidity Value is scaled with factor 100: RH [%] = value /
    100

    *Note: If this value is unknown, 0x7FFF is returned.*
     *
     * @param ambientTemperature Value is scaled with factor 200: T [°C] = value
    / 200

    *Note: If this value is unknown, 0x7FFF is returned.*
     *
     * @param vocIndex Value is scaled with factor 10: VOC Index = value / 10

    *Note: If this value is unknown, 0x7FFF is returned.*

    **Attention: This feature is not available yet, thus currently the
    value 0x7FFF is returned.**
     *
     * @param noxIndex Value is scaled with factor 10: NOx Index = value / 10

    *Note: If this value is unknown, 0x7FFF is returned.*

    **Attention: This feature is not available yet, thus currently the
    value 0x7FFF is returned.**
     *
     * @return 0 on success, an error code otherwise
     */
    uint16_t readMeasuredValues(uint16_t& massConcentrationPm1p0,
                                uint16_t& massConcentrationPm2p5,
                                uint16_t& massConcentrationPm4p0,
                                uint16_t& massConcentrationPm10p0,
                                int16_t& ambientHumidity,
                                int16_t& ambientTemperature, int16_t& vocIndex,
                                int16_t& noxIndex);

    /**
     * readMeasuredRawValues() - Returns the measured raw values. The command
    0x0202 \"Read Data Ready\" can be used to check if new data is available
    since the last read operation. If no new data is available, the previous
    values will be returned again. If no data is available at all (e.g.
    measurement not running for at least one Second), all values will be at
    their upper limit (0xFFFF for `uint16`, 0x7FFF for `int16`).
     *
     * @param rawHumidity Value is scaled with factor 100: RH [%] = value / 100

    *Note: If this value is unknown, 0x7FFF is returned.*
     *
     * @param rawTemperature Value is scaled with factor 200: T [°C] = value /
    200

    *Note: If this value is unknown, 0x7FFF is returned.*
     *
     * @param rawVoc Raw measured VOC ticks without scale factor.

    *Note: If this value is unknown, 0xFFFF is returned.*

    **Attention: Currently this value is not humidity compensated. The
    compensation will be implemented in a later firmware release.**
     *
     * @param rawNox Raw measured NOx ticks without scale factor.

    *Note: If this value is unknown, 0xFFFF is returned.*

    **Attention: Currently this value is not humidity compensated. The
    compensation will be implemented in a later firmware release.**
     *
     * @return 0 on success, an error code otherwise
     */
    uint16_t readMeasuredRawValues(int16_t& rawHumidity,
                                   int16_t& rawTemperature, uint16_t& rawVoc,
                                   uint16_t& rawNox);

    /**
     * startFanCleaning() - Starts the fan cleaning manually. During the next
    few Seconds, no new measurement results will be available (old values will
    be returned, and the \"data ready\"-flag will not be set).

    **Attention: This feature is not implemented yet, it is just a dummy
    command with no effect.**
     *
     * @note The cleaning will be started only if the device is in measure mode.
    In idle mode, this command does nothing.
     *
     * @return 0 on success, an error code otherwise
     */
    uint16_t startFanCleaning(void);

    /**
     * setFanAutoCleaningInterval() - Sets the fan auto cleaning interval for
     * the device.
     *
     * @note This configuration is volatile, i.e. it will be reverted to the
     * default value after a device reset.
     *
     * @param interval Fan auto cleaning interval [s]. Set to zero to disable
     * auto cleaning.
     *
     * @return 0 on success, an error code otherwise
     */
    uint16_t setFanAutoCleaningInterval(uint32_t interval);

    /**
     * getFanAutoCleaningInterval() - Gets the fan auto cleaning interval from
     * the device.
     *
     * @param interval Fan auto cleaning interval [s]. Zero means auto cleaning
     * is disabled.
     *
     * @return 0 on success, an error code otherwise
     */
    uint16_t getFanAutoCleaningInterval(uint32_t& interval);

    /**
     * getProductName() - Gets the product name from the device.
     *
     * @param productName Null-terminated ASCII string containing the product
     * name. Up to 32 characters can be read from the device.
     *
     * @return 0 on success, an error code otherwise
     */
    uint16_t getProductName(unsigned char productName[],
                            uint8_t productNameSize);

    /**
     * getSerialNumber() - Gets the serial number from the device.
     *
     * @param serialNumber Null-terminated ASCII string containing the serial
     * number. Up to 32 characters can be read from the device.
     *
     * @return 0 on success, an error code otherwise
     */
    uint16_t getSerialNumber(unsigned char serialNumber[],
                             uint8_t serialNumberSize);

    /**
     * getVersion() - Gets the version information for the hardware, firmware
     * and communication protocol.
     *
     * @param firmwareMajor Firmware major version number.
     *
     * @param firmwareMinor Firmware minor version number.
     *
     * @param firmwareDebug Firmware debug state. If the debug state is set, the
     * firmware is in development.
     *
     * @param hardwareMajor Hardware major version number.
     *
     * @param hardwareMinor Hardware minor version number.
     *
     * @param protocolMajor Protocol major version number.
     *
     * @param protocolMinor Protocol minor version number.
     *
     * @param padding Padding byte, ignore this.
     *
     * @return 0 on success, an error code otherwise
     */
    uint16_t getVersion(uint8_t& firmwareMajor, uint8_t& firmwareMinor,
                        bool& firmwareDebug, uint8_t& hardwareMajor,
                        uint8_t& hardwareMinor, uint8_t& protocolMajor,
                        uint8_t& protocolMinor);

    /**
     * readDeviceStatus() - Reads the current device status register.
     *
     * @param deviceStatus Device status (32 flags as an integer value). For
     * details, please refer to the device status flags documentation.
     *
     * @return 0 on success, an error code otherwise
     */
    uint16_t readDeviceStatus(uint32_t& deviceStatus);

    /**
     * readAndClearDeviceStatus() - Reads the current device status register
     * (like command 0xD206 \"Read Device Status\") and afterwards clears all
     * flags.
     *
     * @param deviceStatus Device status (32 flags as an integer value). For
     * details, please refer to the device status flags documentation.
     *
     * @return 0 on success, an error code otherwise
     */
    uint16_t readAndClearDeviceStatus(uint32_t& deviceStatus);

    /**
     * deviceReset() - Executes a reset on the device. This has the same effect
     * as a power cycle.
     *
     * @return 0 on success, an error code otherwise
     */
    uint16_t deviceReset(void);

  private:
    TwoWire* _i2cBus = nullptr;
};

#endif /* SENSIRIONI2CSEN55_H */
