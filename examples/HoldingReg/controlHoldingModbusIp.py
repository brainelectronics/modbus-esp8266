#!/usr/bin/env python
# -*- coding: UTF-8 -*-
# ----------------------------------------------------------------------------
#
#  @author       brainelectronics
#  @file         controlHoldingModbusIp.py
#  @date         April, 2020
#  @version      0.1.0
#  @brief        Control coil via modbus on external IP
#
#  @required     HoldingReg.ino at version 0.1.0
#  				 pymodbus 2.3.0 or higher
#
#  @usage        python3 controlHoldingModbusIp.py
#
#  @todo         None
# ----------------------------------------------------------------------------

__author__ = "brainelectronics"
__copyright__ = "Copyright by brainelectronics, ALL RIGHTS RESERVED"
__credits__ = ["brainelectronics"]
__version__ = "0.1.0"
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
# value:   the value to set the coil to
# theValue = 0
# unit:    the slave unit this request is targeting (the slave device ID)
# slaveID = 12

# function 03 - read holding register (address=0, count=1, unit=12)
print("Reading data from register %s" %(registerAddress))
data = client.read_holding_registers(address=registerAddress)
hexValue = 0
if data != None:
	# print(data)
	# print(data.registers)
	hexValue = int(data.registers[0])
	print("0x%X" %(hexValue))
time.sleep(1)

# function 06 - write single registers (address=0, value=4, unit=12)
hexValue += 1
print("Setting data of register %s to 0x%X" %(registerAddress, hexValue))
data = client.write_register(address=registerAddress, value=hexValue)
if data != None:
	print(data)
time.sleep(1)

# function 03 - read holding register (address=0, count=1, unit=12)
print("Reading data from register %s" %(registerAddress))
data = client.read_holding_registers(address=registerAddress)
hexValue = 0
if data != None:
	# print(data)
	# print(data.registers)
	hexValue = int(data.registers[0])
	print("0x%X" %(hexValue))
time.sleep(1)

client.close()
