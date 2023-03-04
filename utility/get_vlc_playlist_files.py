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

OUTPUT_DIR = "./"

filePaths = glob('*.xspf')
listPath = filePaths[0]
listName = basename(listPath.split('.')[0])

tree = ET.parse(listPath)
root = tree.getroot()

tracklist = [child for child in root if child.tag.endswith('trackList')][0]
for track in tracklist:
	path = [child.text for child in track if child.tag.endswith('location')][0]
	path = unquote(path.replace("file:///", ""))
	#print(path)
	
	# copy
	dirName = f'{OUTPUT_DIR}/{listName}/'
	if not exists(dirName): makedirs(dirName)
	copy2(path, dirName)