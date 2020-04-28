#!/usr/bin/env python
# -*- coding: UTF-8 -*-
# ----------------------------------------------------------------------------
#
#  @author       brainelectronics
#  @file         readSwitchModbusIp.py
#  @date         April, 2020
#  @version      0.1.0
#  @brief        Read digital input register via modbus on external IP
#
#  @required     SwitchStatus.ino at version 0.1.0
#  				 pymodbus 2.3.0 or higher
#
#  @usage        python3 readSwitchModbusIp.py
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
# count:   the number of registers to read
theAmount = 1
# unit:    the slave unit this request is targeting (the slave device ID)
# slaveID = 12

# function 02 - read input status (discrete inputs/digital input) (address=0, count=1, unit=12)
print("Reading data from register %s" %(registerAddress))
data = client.read_discrete_inputs(address=registerAddress)
pinState = 0
if data != None:
	print(data)
	print(data.bits)
	# [True, False, False, False, False, False, False, False]

	# as we only request theAmount=1 we are only interested in the first ele
	pinState = int(data.bits[theAmount-1])
	print("%d" %(pinState))
time.sleep(1)

# function 02 - read input status (discrete inputs/digital input) (address=0, count=1, unit=12)
print("Reading data from register %s" %(registerAddress))
data = client.read_discrete_inputs(address=registerAddress)
pinState = 0
if data != None:
	print(data)
	print(data.bits)
	# [True, False, False, False, False, False, False, False]

	# as we only request theAmount=1 we are only interested in the first ele
	pinState = int(data.bits[theAmount-1])
	print("%d" %(pinState))
time.sleep(1)

# function 02 - read input status (discrete inputs/digital input) (address=0, count=1, unit=12)
print("Reading data from register %s" %(registerAddress))
data = client.read_discrete_inputs(address=registerAddress)
pinState = 0
if data != None:
	print(data)
	print(data.bits)
	# [True, False, False, False, False, False, False, False]

	# as we only request theAmount=1 we are only interested in the first ele
	pinState = int(data.bits[theAmount-1])
	print("%d" %(pinState))
time.sleep(1)

client.close()
