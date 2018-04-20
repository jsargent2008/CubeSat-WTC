#include "LTC2991.h"
#define LTCrocks TRUE;

// Calibration Variables
//! Typical single-ended LSB weight in volts
const float LTC2991_SINGLE_ENDED_lsb = 3.05176E-04;
//! Typical differential LSB weight in volts
const float LTC2991_DIFFERENTIAL_lsb = 1.90735E-05;
//! Typical VCC LSB weight in volts
const float LTC2991_VCC_lsb = 3.05176E-04;
//! Typical temperature LSB weight in degrees Celsius (and Kelvin).
//! Used for internal temperature as well as remote diode temperature measurements.
const float LTC2991_TEMPERATURE_lsb = 0.0625;
//! Typical remote diode LSB weight in volts.
//! Used to readback diode voltage when in temperature measurement mode.
const float LTC2991_DIODE_VOLTAGE_lsb = 3.815E-05;

// TODO: Make using struct or OOP
I2C_HandleTypeDef hi2c;
UART_HandleTypeDef *myhuart;

LTC2991 *test() {
	int8_t ack = 0;
	// Read Temperature
	int8_t data_valid;
	int8_t isKelvin;
	int16_t adc_code;
	uint8_t reg_data;
	float temperature = 0;
	char prompt[20] = { };

	sprintf(prompt, "hi\r\n");
	putS(myhuart, prompt);

	ack |= LTC2991_register_write(LTC2991_I2C_ADDRESS, LTC2991_CHANNEL_ENABLE_REG,
	LTC2991_ENABLE_ALL_CHANNELS);   //! Enables all channels
	ack |= LTC2991_register_write(LTC2991_I2C_ADDRESS, LTC2991_CONTROL_V1234_REG, 0x00); //! Sets registers to default starting values.
	ack |= LTC2991_register_write(LTC2991_I2C_ADDRESS, LTC2991_CONTROL_V5678_REG, 0x00);
	ack |= LTC2991_register_write(LTC2991_I2C_ADDRESS, LTC2991_CONTROL_PWM_Tinternal_REG,
	LTC2991_REPEAT_MODE);    //! Configures LTC2991 for Repeated Acquisition mode

	// Do temp reading
	// Flush one ADC reading in case it is stale.  Then, take a new fresh reading.
	ack |= LTC2991_adc_read_new_data(LTC2991_I2C_ADDRESS, LTC2991_T_Internal_MSB_REG, &adc_code,
			&data_valid, 1000);
	ack |= LTC2991_register_read(LTC2991_I2C_ADDRESS, LTC2991_CONTROL_PWM_Tinternal_REG, &reg_data);
	if (reg_data & LTC2991_INT_KELVIN_ENABLE)
		isKelvin = 1;
	else
		isKelvin = 0;

	temperature = LTC2991_temperature(adc_code, LTC2991_TEMPERATURE_lsb, isKelvin);

	sprintf(prompt, "%.2fC\r\n", temperature);
	putS(myhuart, prompt);

	//	Do vcc voltage reading
	int16_t code;
	float voltage;

	// Flush one ADC reading in case it is stale.  Then, take a new fresh reading.
	ack |= LTC2991_adc_read_new_data(LTC2991_I2C_ADDRESS, LTC2991_Vcc_MSB_REG, &code, &data_valid,
			1000);
	voltage = LTC2991_code_to_vcc_voltage(code, LTC2991_SINGLE_ENDED_lsb);

	sprintf(prompt, "%.3fV\r\n", voltage);
	putS(myhuart, prompt);

	return NULL;
}

/**
 * @brief  Write an amount of data in blocking mode to a specific memory address
 * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
 * @retval HAL status
 */
uint8_t CheckDevAddress(uint16_t DevAddress) {
	if (DevAddress != 0x90 || DevAddress != 0x92 || DevAddress != 0x94 || DevAddress != 0x96
			|| DevAddress != 0x98 || DevAddress != 0x9A || DevAddress != 0x9C
			|| DevAddress != 0x9E) {
		return 1;
	} else {
		return 0;
	}
}

// Reads a 14-bit adc_code from LTC2991.
int8_t LTC2991_adc_read(uint8_t i2c_address, uint8_t msb_register_address, int16_t *adc_code,
		int8_t *data_valid) {
	int8_t ack = 0;
	uint8_t code[2] = { };

	HAL_I2C_Master_Transmit(&hi2c, i2c_address, &msb_register_address, 1, 1000);
	ack = HAL_I2C_Master_Receive(&hi2c, i2c_address, code, 2, 1000);

	// move over first half to msb position then or the lsb in
	uint16_t actcode;
	actcode = code[0] << 8;
	actcode |= code[1];

	*data_valid = (actcode >> 15) & 0x01;	// Place Data Valid Bit in *data_valid

	*adc_code = actcode & 0x7FFF;	// Removes data valid bit to return proper adc_code value

	return (ack);
}

// Reads a 14-bit adc_code from the LTC2991 but enforces a maximum timeout.
// Similar to LTC2991_adc_read except it repeats until the data_valid bit is set, it fails to receive an I2C acknowledge, or the timeout (in milliseconds)
// expires. It keeps trying to read from the LTC2991 every millisecond until the data_valid bit is set (indicating new data since the previous
// time this register was read) or until it fails to receive an I2C acknowledge (indicating an error on the I2C bus).
int8_t LTC2991_adc_read_timeout(uint8_t i2c_address, uint8_t msb_register_address,
		int16_t *adc_code, int8_t *data_valid, uint16_t timeout, uint8_t status_bit) {
	int8_t ack = 0;
	uint8_t reg_data;
	uint16_t timer_count;  // Timer count for data_valid

	for (timer_count = 0; timer_count < timeout; timer_count++) {

		if (status_bit < 8) {
			ack |= LTC2991_register_read(i2c_address, LTC2991_STATUS_LOW_REG, &reg_data); //! 1)Read status register until correct data valid bit is set
		} else {
			ack |= LTC2991_register_read(i2c_address, LTC2991_STATUS_HIGH_REG, &reg_data); //! 1)Read status register until correct data valid bit is set
			if (status_bit == 8) {
				status_bit = 1;
			} else {
				status_bit = 0;
			}
		}

		if ((ack) || (((reg_data >> status_bit) & 0x1) == 1)) {
			break;
		}

		HAL_Delay(1);
	}

	ack |= LTC2991_adc_read(i2c_address, msb_register_address, &(*adc_code), &(*data_valid)); //! 2) It's either valid or it's timed out, we read anyways
	if (*data_valid != 1) {
//		Serial.println("Data not valid");
//		Serial.println(*data_valid);
		return (1);
	}
	return (ack);
}

// Reads new data (even after a mode change) by flushing old data and waiting for the data_valid bit to be set.
// This function simplifies adc reads when modes are changing.  For example, if V1-V2 changes from temperature mode
// to differential voltage mode, the data in the register may still correspond to the temperature reading immediately
// after the mode change.  Flushing one reading and waiting for a new reading guarantees fresh data is received.
// If the timeout is reached without valid data (*data_valid=1) the function exits.
int8_t LTC2991_adc_read_new_data(uint8_t i2c_address, uint8_t msb_register_address,
		int16_t *adc_code, int8_t *data_valid, uint16_t timeout) {
	int8_t ack = 0;

	ack |= LTC2991_adc_read_timeout(i2c_address, msb_register_address, &(*adc_code), &(*data_valid),
			timeout, ((msb_register_address / 2) - 0x05)); //! 1)  Throw away old data
	ack |= LTC2991_adc_read_timeout(i2c_address, msb_register_address, &(*adc_code), &(*data_valid),
			timeout, ((msb_register_address / 2) - 0x05)); //! 2) Read new data

	return (ack);
}

// Reads an 8-bit register from the LTC2991 using the standard repeated start format.
int8_t LTC2991_register_read(uint8_t i2c_address, uint8_t register_address, uint8_t *register_data) {
	int8_t ack = 0;

	ack = HAL_I2C_Mem_Read(&hi2c, i2c_address, register_address, I2C_MEMADD_SIZE_8BIT,
			register_data, 1, 1000);
	return (ack);
}

// Write one byte to an LTC2991 register.
// Writes to an 8-bit register inside the LTC2991 using the standard I2C repeated start format.
int8_t LTC2991_register_write(uint8_t i2c_address, uint8_t register_address, uint8_t register_data) {
	int8_t ack = 0;

	ack = HAL_I2C_Mem_Write(&hi2c, i2c_address, register_address, I2C_MEMADD_SIZE_8BIT,
			&register_data, 1, 1000);
	return (ack);
}

// Used to set and clear bits in a control register.  bits_to_set will be bitwise OR'd with the register.
// bits_to_clear will be inverted and bitwise AND'd with the register so that every location with a 1 will result in a 0 in the register.
int8_t LTC2991_register_set_clear_bits(uint8_t i2c_address, uint8_t register_address,
		uint8_t bits_to_set, uint8_t bits_to_clear) {
	uint8_t register_data;
	int8_t ack = 0;

	ack |= LTC2991_register_read(i2c_address, register_address, &register_data); //! 1) Read register
	register_data = register_data & (~bits_to_clear); //! 2) Clear bits that were set to be cleared
	register_data = register_data | bits_to_set;
	ack |= LTC2991_register_write(i2c_address, register_address, register_data); //! 3) Write to register with the cleared bits
	return (ack);
}

// Calculates the LTC2991 single-ended input voltages
float LTC2991_code_to_single_ended_voltage(int16_t adc_code, float LTC2991_single_ended_lsb) {
	float voltage;
	int16_t sign = 1;
	if (adc_code >> 14) {
		adc_code = (adc_code ^ 0x7FFF) + 1;               //! 1) Converts two's complement to binary
		sign = -1;
	}
	adc_code = (adc_code & 0x3FFF);
	voltage = ((float) adc_code) * LTC2991_single_ended_lsb * sign; //! 2) Convert code to voltage from lsb
	return (voltage);
}

// Calculates the LTC2991 Vcc voltage
float LTC2991_code_to_vcc_voltage(int16_t adc_code, float LTC2991_single_ended_lsb) {
	float voltage;
	int16_t sign = 1;
	if (adc_code >> 14) {
		adc_code = (adc_code ^ 0x7FFF) + 1;               //! 1) Converts two's complement to binary
		sign = -1;
	}

	voltage = (((float) adc_code) * LTC2991_single_ended_lsb * sign) + 2.5; //! 2) Convert code to Vcc Voltage from single-ended lsb
	return (voltage);
}

// Calculates the LTC2991 differential input voltage.
float LTC2991_code_to_differential_voltage(int16_t adc_code, float LTC2991_differential_lsb) {
	float voltage;
	int16_t sign = 1;
	if (adc_code >> 14) {
		adc_code = (adc_code ^ 0x7FFF) + 1;                //! 1)Converts two's complement to binary
		sign = -1;
	}
	voltage = ((float) adc_code) * LTC2991_differential_lsb * sign; //! 2) Convert code to voltage form differential lsb
	return (voltage);
}

// Calculates the LTC2991 temperature
float LTC2991_temperature(int16_t adc_code, float LTC2991_temperature_lsb, uint8_t unit) {
	float temperature;
	adc_code = (adc_code & 0x1FFF);					//! 1) Removes first 3 bits
	if (!unit) {									//! 2) Checks to see if it's Kelvin
		if (adc_code >> 12) {
			adc_code = (adc_code | 0xE000);			//! Sign extend if it's not Kelvin (Celsius)
		}
	}
	temperature = ((float) adc_code) * LTC2991_temperature_lsb; //! 3) Converts code to temperature from temperature lsb

	return (temperature);
}

//  Calculates the LTC2991 diode voltage
float LTC2991_code_to_diode_voltage(int16_t adc_code, float LTC2991_diode_voltage_lsb) {
	float voltage;
	adc_code = (adc_code & 0x1FFF);								//! 1) Removes first 3 bits
	voltage = ((float) adc_code) * LTC2991_diode_voltage_lsb;//! 2) Convert code to voltage from diode voltage lsb
	return (voltage);
}
