#!/usr/bin/env python
# -*- coding: UTF-8 -*-
# ----------------------------------------------------------------------------
#
#  @author       brainelectronics
#  @file         controlLedModbusIp.py
#  @date         April, 2020
#  @version      0.1.0
#  @brief        Control coil via modbus on external IP
#
#  @required     Led.ino at version 0.1.0
#  				 pymodbus 2.3.0 or higher
#
#  @usage        python3 controlLedModbusIp.py
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

# function 06 - write single registers (start=0, length=4, unitid=12)
data = client.write_coil(address=registerAddress, value=1)
if data != None:
	print(data)
time.sleep(1)

# function 06 - write single registers (start=0, length=4, unitid=12)
data = client.write_coil(address=registerAddress, value=0)
if data != None:
	print(data)
time.sleep(1)

# function 06 - write single registers (start=0, length=4, unitid=12)
data = client.write_coil(address=registerAddress, value=1)
if data != None:
	print(data)
time.sleep(1)

# function 06 - write single registers (start=0, length=4, unitid=12)
data = client.write_coil(address=registerAddress, value=0)
if data != None:
	print(data)

client.close()
