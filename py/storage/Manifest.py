#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import os.path
import json

class Manifest(object):
	FILE_NAME = "manifest"
	def __init__(self):
		self.version = 0
		self.description = ""
		self.created = None
		self.updated = None
		self.volumes = []
	
	def read_file(self, path: str):
		file_path = os.path.join(path, self.FILE_NAME)
		
		with open(file_path, "r", encoding="utf-8") as fd:
			jdata = json.load(fd)
			
			self.__from_dict(jdata)


	def print(self):
		print("===== manifest =====")
		print("version: ", self.version)
		print("description: ", self.description)
		print("volumes: ", len(self.volumes))


	def __from_dict(self, data: dict):
		self.version = data.get("version", 0)
		self.description = data.get("description", "")
		
		volumes = data.get("volumes", [])
		
		for v in volumes:
			vol = MVolume()
			vol.from_dict(v)
			self.volumes.append(vol)



class MVolume(object):
	def __init__(self):
		self.name = ""
		self.uid = ""
		self.icon = 0
		
	def from_dict(self, data: dict):
		self.name = data.get("name", "")
		self.uid = data.get("id", "")
		self.icon = data.get("icon", 0)
