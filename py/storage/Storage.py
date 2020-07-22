#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import os.path
from .Manifest import Manifest
from .Volume import Volume

class Storage(object):
	def __init__(self):
		self.path = ""
		self.manifest = Manifest()
		
		
		
	#--- public ---------------------------------------------------------------
	def open_db(self, path: str):
		self.path = path
		
		self.manifest.read_file(self.path)
		
		
	def load_volume(self, vol_id: str) -> Volume:
		vol_path = os.path.join(self.path, vol_id + ".vol")
		volume = Volume(vol_path)
		return volume
	#--- public ---------------------------------------------------------------