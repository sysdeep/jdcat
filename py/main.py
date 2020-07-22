#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from storage.Storage import Storage



DB_PATH = "/home/nia/Development/_QT/JDcat/_storages/st1"

storage = Storage()
storage.open_db(DB_PATH)
storage.manifest.print()


for v in storage.manifest.volumes:

	volume = storage.load_volume(v.uid)
	volume.root.reprint()

