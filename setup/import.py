#!/usr/bin/env python3

"""
QT kit importer
===============

- Used to import existing kits into qt config files
  (with their dependencies such as devices, toolchains...)

- The affected files are in directory ~/.config/QtProject/qtcreator:
	- profiles.xml
	- toolchains.xml 
	- devices.xml
	- qtversion.xml
	- debuggers.xml
	
- Imported XMLs are genereated from export.py and are in format (the ordering is optional):

	<import>
	  <profile>
		<data>
		  <variable> Profile.x </variable>         <!-- x will be automatically repalced-->
		  ...
		</data>
	  </profile>
	  ...
	  <toolchain> <data> ... </data> </toolchain>
	  ...
	  <qtversion> <data> ... </data> </qtversion>
	  ...
	  <debugger> <data> ... </data> </debugger>
	  ...
	  <device> <valuemap type="QVariantMap"> ... </valuemap> </device>
	  ...		
	</import>

Created on 14.06.2022 by Milan Vesely
"""

import os	
import sys
import xml.etree.ElementTree as et

QTCONFIG_PATH = os.path.expanduser("~/.config/QtProject/qtcreator")

PROFILES_PATH = os.path.join(QTCONFIG_PATH, "profiles.xml")
TOOLCHAINS_PATH = os.path.join(QTCONFIG_PATH, "toolchains.xml")	
DEVICES_PATH = os.path.join(QTCONFIG_PATH, "devices.xml")
QTVERSION_PATH = os.path.join(QTCONFIG_PATH, "qtversion.xml")
DEBUGGER_PATH = os.path.join(QTCONFIG_PATH, "debuggers.xml")


def main():
	# The file from which the kit will be imported - can be argument or inputed
	if (len(sys.argv) > 2):
		sys.stderr.write("Maximum number of arguments is 1\n")
		exit(1)
	elif(len(sys.argv) == 2):
		importFile = sys.argv[1]
	else:
		importFile = input("Enter import file name: ")
		
	importRoot = et.parse(importFile).getroot()
	
	
	# Appending the nodes to different files according to their tags
	for node in importRoot:
		if (node.tag == "profile"):
			generic_append(node[0], PROFILES_PATH, "Profile", True)
		elif (node.tag == "toolchain"):
			generic_append(node[0], TOOLCHAINS_PATH, "ToolChain", True)
		elif (node.tag == "debugger"):
			generic_append(node[0], DEBUGGER_PATH, "DebuggerItem", True)
		elif (node.tag == "qtversion"):
			generic_append(node[0], QTVERSION_PATH, "QtVersion", False)
		elif (node.tag == "device"):
			device_append(node, DEVICES_PATH, "Device")
			
		# In case any other type needs to be added:
		
		# elif (node.tag == [new tag in import XML]):
		#    generic_append(node[0], [path to the config XML file], [prefix such as Profile in Profile.Count])
			
		print(f"Succesfully imported {node.tag}")
		
	print("Done.")


def generic_append(importProfileNode, filename, prefix, shouldIncrement):
	# Imported file check
	if (importProfileNode[0].text.split(".")[0] != prefix or importProfileNode[0].tag != "variable"):
		sys.stderr.write(f"Imported {prefix} isn't valid, skipping\n")
		return
	
	# Destination file parse
	destinationFile = et.parse(filename) 
	destinationRoot = destinationFile.getroot()
	
	# NewNum is based on maximal index which is present in the file
	maxNum = find_max(destinationRoot, prefix)
	
	# In some cases there is variable called ___.Count which needs to be incremented
	if (shouldIncrement and not increment_count(destinationRoot, prefix, maxNum)):
		return
		
	# Edit the imported node with new num and append it
	importProfileNode[0].text = prefix + "." + str(maxNum + 1)
	destinationRoot.append(importProfileNode)	
	destinationFile.write(filename)


# Finds the largest number x such as <variable> [prefix].x </variable> is child of root
def find_max(root, prefix):
	maxNum = 0
	
	for node in root:	
		var = node.find("variable")
		if (node is None or len(node) == 0):
			continue
		
		split = var.text.split(".")

		if (split[0] == prefix and split[1].isnumeric()):
			maxNum = max(maxNum, int(split[1]))

	return maxNum


# Finds node <variable>[prefix].Count</variable> <value type="int"> x </value> and increments the x by one
def increment_count(root, prefix, maxNum):
	for node in root:	
		var = node.find("variable")
		if (node is None or len(node) == 0):
			continue
		
		if (var.text == prefix + ".Count"):		
			countNode = node.find("value")
			count = int(countNode.text)
			
			if (count - 1 != maxNum):
				sys.stderr.write(f"Max {prefix} number doesn't match {prefix}.Count, skipping\n")
				return False
			
			countNode.text = str(count + 1)
			return True
	
	sys.stderr.write(prefix + ".Count wasn't found\n")
	return False


def device_append(importProfileNode, filename, prefix):
	# Imported file check
	if (importProfileNode[0].tag != "valuemap"):
		sys.stderr.write("Imported device isn't valid, skipping\n")
		return
	
	destinationFile = et.parse(filename) 
	destinationRoot = destinationFile.getroot()
	
	# Appending to specific part of the devices file (try could be rewritten as double empty check...)
	try:	
		valueList = destinationRoot[0].find("valuemap").find(".//valuelist[@key='DeviceList']").append(importProfileNode)	
	except:
		sys.stderr.write("Imported device isn't valid, skipping\n")
		return
		
	destinationFile.write(filename)


if __name__=="__main__":
	main()
