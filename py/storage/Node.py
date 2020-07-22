#!/usr/bin/env python3
# -*- coding: utf-8 -*-

class Node(object):
	def __init__(self):
		self.name = ""
		self.childrens = []
		
		
	def parse(self, data: dict, re: bool = False):
		self.name = data.get("name", "")
		
		
		
		childrens = data.get("childrens", [])
		for ch in childrens:
			n = Node()
			n.parse(ch, re)
			self.childrens.append(n)
			
			
	def reprint(self, level = 0):
		
		print("--"*level + self.name)
		for ch in self.childrens:
			ch.reprint(level + 1)
			