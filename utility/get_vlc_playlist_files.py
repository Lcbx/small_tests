#!/usr/bin/env python

"""
copy music files that are within a vlc playlist to a chosen directory
this is so you can listen to files, remove those you don't like, save the result in a playist,
then get those files for your project

Usage -
	python get_vlc_playlist_files.py
		will take the first playlist (.xspf) file in the executing directory
		will save to a local ./tracks dir
"""


import xml.etree.ElementTree as ET
from glob import glob
from os.path import exists, basename
from os import makedirs
from urllib.parse import unquote, urlparse
from shutil import copy2

OUTPUT_DIR = "./tracks/"

file = glob('*.xspf')
tree = ET.parse(file[0])
root = tree.getroot()

tracklist = [child for child in root if child.tag.endswith('trackList')][0]
for track in tracklist:
	path = [child.text for child in track if child.tag.endswith('location')][0]
	path = unquote(path.replace("file:///", ""))
	#print(path, exists(path))
	
	# copy
	if not exists(OUTPUT_DIR): makedirs(OUTPUT_DIR)
	copy2(path, OUTPUT_DIR)