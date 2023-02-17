#!/usr/bin/env python
# encoding: utf-8

"""
downloads music based on a file's listed content, sets metadata
Usage -
	python MusiquePourMaman.py (or just double click it)
	expects a file named 'musique.txt' in same directory
	that contains a song in each line with format 'title (artist)'
Output -
	song files in a directory called 'DJ' with
		track # equal to position,
		title and artist set based on ones given
		'Youtube' as album title
Requires -
	request, mutagen, youtube_dl
	ffmpeg (not python lib, download from https://ffmpeg.org/)
"""

import requests
import youtube_dl
import mutagen
import traceback
import os.path

ext = 'mp3' # wav could work too
songDirectory = 'DJ/' # wav could work too

def updateMusicListWithSong(listIndex, searchName):
	
	titleAndArtist = searchName.split('(')
	title = titleAndArtist[0].strip()
	artist = titleAndArtist[1].replace(')','').strip()
	
	filename = f'{songDirectory}/{artist} - {title}'
	filenameWithExt = f'{filename}.{ext}'
	print(filename)
	
	# only download if file does not exist
	if not os.path.isfile(filenameWithExt):
		# search keywords
		words = searchName.replace('(', '').replace(')', '').split()
		
		# adding "lyrics" because those videos tend to just be the song (with no intro / cinematic video)
		words.append('lyrics')
		
		url = 'http://www.youtube.com/results?search_query=' + '+'.join(words)
		html = requests.get(url).text
		#print(html)
		
		# you can reproduce a video url using videoId
		txtTofind = '"videoId":"'
		videoId_start = html.find(txtTofind) + len(txtTofind)
		videoId_end   = html.find('"',videoId_start)
		videoId = html[videoId_start : videoId_end]
		
		# only get the first video
		FirstVideoUrl = 'https://www.youtube.com/watch?v=' + videoId
		print(FirstVideoUrl)
		
		ydl_opts = {
			#'verbose': True,
			'outtmpl': f'{filename}.mpeg',
			'format': 'bestaudio/best',
			'postprocessors': [{
				'key': 'FFmpegExtractAudio',
				'preferredcodec': ext,
				'preferredquality': '192'
			}],
			'prefer_ffmpeg': True,
			'keepvideo': False # we don't need the intermediary mpeg file
			#'progress_hooks': [youtube_dl_hook],
			# to use : def youtube_dl_hook(d)
		}
		with youtube_dl.YoutubeDL(ydl_opts) as ydl:
			ydl.download([FirstVideoUrl])
			print('download done')
	
	# easy here means : add metadata if missing (equivalent to metadata.add_tags())
	metadata = mutagen.File(filenameWithExt, easy=True)
				
	#print(metadata)
	metadata["title"] = title
	metadata["artist"] = artist
	metadata["album"] = 'Youtube'
	metadata["tracknumber"] = str(listIndex)
	metadata.save()
	print('metadata updated')

if __name__=='__main__':
	try:
		with open('musique.txt','r', encoding="utf-8") as file:
			i = 0 # to set song tack number, to be used to order them as in given list
			for line in file.readlines():
				simplified = line.strip()
				if simplified:
					updateMusicListWithSong(i, simplified)
					i+=1
		
	except Exception as e:
		print( f'Exception {traceback.format_exc()} : {e}' )
		input("Press Enter to continue...")
		exit(-1)