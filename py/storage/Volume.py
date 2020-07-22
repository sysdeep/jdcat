#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import json
from .Node import Node

class Volume(object):
	def __init__(self, path: str):
		self.path = path
		self.root = None
		
		self.__open()
		
	def __open(self):
		
		with open(self.path, "r", encoding="utf-8") as fd:
			jdata = json.load(fd)
			self.__from_dict(jdata)
			
			
	def __from_dict(self, data: dict):
		root_nodes = data.get("root", None)
		
		if root_nodes:
			self.root = Node()
			self.root.parse(root_nodes, re=True)