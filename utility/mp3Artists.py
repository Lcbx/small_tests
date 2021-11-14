#!/usr/bin/env python

"""
Set Artist, Titlem album and track # based on mp3 files
Usage -
	python mp3Artists.py <path/to/directory>
		path to files is optional. Path needs to be absolute
		will search the current directory if no path is given

Files must be mp3, and be in format : "Artist - Title"
sets Album to Youtube and track # to 1
will print "STRANGER DANGER {file}" if there are more than 1 '-'  since name of file is confusing

Requires - mutagen 
Download and install using
	pip install mutagen
"""

import mutagen
from mutagen.easyid3 import EasyID3
import sys
import os
import traceback


def process(path):
	for root, dirs, files in os.walk(path):
		for file in files:
			if file.upper()[-4:] == '.MP3':
				#print(f'found {file}')
				
				cutFile = file.split('-')
				
				if cutFile[0].strip().isdigit():
					print(f'skipping {file}')
					continue
				
				name = ''
				artist = ''
				if len(cutFile) == 1:
					name = cutFile[0][:-4].strip()
					artist = ''
				elif len(cutFile) == 2:
					artist = cutFile[0].strip()
					name = cutFile[1][:-4].strip()
				else:
					#raise Exception(f'STRANGER DANGER {file}')
					print(f'STRANGER DANGER {file}')
					artist = cutFile[0].strip()
					name = ''.join(cutFile[1:])[:-4].strip()
				
				try:
					audio = EasyID3(file)
				except:
					audio = mutagen.File(file, easy=True)
					audio.add_tags()
				
				#print(audio)
				if 'album' not in str(audio):
					#print(f'setting stuff')
					audio["title"] = name
					audio["artist"] = artist
					audio["album"] = 'Youtube'
					audio["tracknumber"] = '1'
					audio.save()
					#newName = name + '.mp3'
					#os.rename(file, newName)
					#audio.save(newName)
					#print(audio)


if __name__=='__main__':
	if len(sys.argv) not in (1,2):
		print('Error! Invalid arguments')
		print(__doc__)
		exit(-1)
		
	if len(sys.argv) == 1:
		path = os.getcwd()
	else:
		path = sys.argv[1]
	try:
		process(path)
	except Exception as e:
		print( f'Exception {traceback.format_exc()} : {e}' )
		exit(-1)


# from mutagen.easyid3 import EasyID3
# p = "E:\\Musik\\Aeon\\2005 Bleeding the False\\01 Cenobites - Copy.mp3"
# audio = EasyID3(p)
# audio["title"] = u"t"
# audio["artist"] = u"a"
# audio["album"] = "al"
# audio["date"] = u"2000"
# audio["tracknumber"] = u"1"
# audio["genre"] = u"g"
# audio.save()
# print('\n'.join(EasyID3.valid_keys.keys()))