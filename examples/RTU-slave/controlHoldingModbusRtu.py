#!/usr/bin/env python
# -*- coding: UTF-8 -*-
# ----------------------------------------------------------------------------
#
#  @author       brainelectronics
#  @file         controlHoldingModbusRtu.py
#  @date         April, 2020
#  @version      0.1.0
#  @brief        Read and control holding register via modbus on serial port
#
#  @required     RTU-slave.ino at version 0.1.0
#  				 pymodbus 2.3.0 or higher
#
#  @usage        python3 controlHoldingModbusRtu.py
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
from pymodbus.client.sync import ModbusSerialClient
import time

client = ModbusSerialClient(
	method="rtu",
	port="/dev/tty.usbserial-A50285BI",		# port of USB-RS485 converter
	stopbits=1,
	bytesize=8,
	parity="N",
	baudrate=9600,
	timeout=1,
	retries=2)

# connect to the serial modbus server
connection = client.connect()
print("Connection result is %s" %(connection))

# address: the starting address to read from
registerAddress = 100
# value:   the value to set the register to
# theValue = 0
# unit:    the slave unit this request is targeting (the slave device ID)
slaveID = 12

# function 03 - read holding register (address=0, count=1, unit=12)
print("Reading data from register %s" %(registerAddress))
data = client.read_holding_registers(address=registerAddress, unit=slaveID)
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
data = client.write_register(address=registerAddress, value=hexValue, unit=slaveID)
if data != None:
	print(data)
time.sleep(1)

# function 03 - read holding register (address=0, count=1, unit=12)
print("Reading data from register %s" %(registerAddress))
data = client.read_holding_registers(address=registerAddress, unit=slaveID)
hexValue = 0
if data != None:
	# print(data)
	# print(data.registers)
	hexValue = int(data.registers[0])
	print("0x%X" %(hexValue))
time.sleep(1)

client.close()
