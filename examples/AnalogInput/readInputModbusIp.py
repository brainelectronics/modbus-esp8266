#!/usr/bin/env python
# -*- coding: UTF-8 -*-
# ----------------------------------------------------------------------------
#
#  @author       brainelectronics
#  @file         readInputModbusIp.py
#  @date         April, 2020
#  @version      0.1.1
#  @brief        Read input register via modbus on external IP
#
#  @required     AnalogInput.ino at version 0.1.0
#  				 pymodbus 2.3.0 or higher
#
#  @usage        python3 readInputModbusIp.py
#
#  @todo         None
# ----------------------------------------------------------------------------

__author__ = "brainelectronics"
__copyright__ = "Copyright by brainelectronics, ALL RIGHTS RESERVED"
__credits__ = ["brainelectronics"]
__version__ = "0.1.1"
__maintainer__ = "brainelectronics"
__email__ = "git@brainelectronics.de"
__status__ = "Development"

# pip install pymodbus
from pymodbus.client.sync import ModbusTcpClient
import time

client = ModbusTcpClient(
	host="192.168.178.61",
	# retries=2,
	# retry_on_empty=True,
	port=502)

# connect to the serial modbus server
connection = client.connect()
print("Connection result is %s" %(connection))

# address: the starting address to read from
registerAddress = 100
# count:   the number of registers to read
# theAmount = 1
# unit:    the slave unit this request is targeting (the slave device ID)
# slaveID = 12

# function 04 - read input registers (address=0, count=1, unit=12)
print("Reading data from register %s" %(registerAddress))
data = client.read_input_registers(address=registerAddress)
adcValue = 0
if data != None:
	# print(data)
	# print(data.registers)
	adcValue = int(data.registers[0])
	print("%d" %(adcValue))
time.sleep(1)

# function 04 - read input registers (address=0, count=1, unit=12)
print("Reading data from register %s" %(registerAddress))
data = client.read_input_registers(address=registerAddress)
adcValue = 0
if data != None:
	# print(data)
	# print(data.registers)
	adcValue = int(data.registers[0])
	print("%d" %(adcValue))
time.sleep(1)

# function 04 - read input registers (address=0, count=1, unit=12)
print("Reading data from register %s" %(registerAddress))
data = client.read_input_registers(address=registerAddress)
adcValue = 0
if data != None:
	# print(data)
	# print(data.registers)
	adcValue = int(data.registers[0])
	print("%d" %(adcValue))
time.sleep(1)

client.close()
