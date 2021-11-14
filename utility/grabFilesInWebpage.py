#!/usr/bin/env python

"""
Download all the files linked on a given webpage
Usage -
	python grabFilesInWebpage.py url <path/to/directory>
		url is required
		path is optional. Path needs to be absolute
		will save in the current directory if no path is given
		will save in the current directory if given path does not exist
Requires - requests >= 1.0.4
		   beautifulsoup >= 4.0.0
Download and install using
	
	pip install requests
	pip install beautifulsoup4

Based on similar script by elssar <elssar@altrawcode.com>
"""

from requests import get
from urllib.parse import urljoin
from os import path, getcwd
from bs4 import BeautifulSoup as soup
import sys
import traceback


def get_page(base_url):
	req= get(base_url)
	if req.status_code==200:
		return req.text
	raise Exception('Error {0}'.format(req.status_code))

def get_all_links(html):
	bs= soup(html)
	links= bs.findAll('a')
	return links

def get_files(base_url, base_dir):
	html= get_page(base_url)
	links= get_all_links(html)
	if len(links)==0:
		raise Exception('No links found on the webpage')
	n_files= 0
	for link in links:
		content = get(urljoin(base_url, link['href']))
		if hasattr(content, 'content'):
			n_files+= 1
			with open(path.join(base_dir, link.text), 'wb') as file:
				file.write(content.content)
	if n_files==0:
		raise Exception('No files found on the page')
	print( "{0} files downloaded and saved in {1}".format(n_files, base_dir))

if __name__=='__main__':
	if len(sys.argv) not in (2, 3):
		print('Error! Invalid arguments')
		print(__doc__)
		exit(-1)
	arg= ''
	url= sys.argv[1]
	if len(sys.argv)==3:
		arg= sys.argv[2]
	base_dir= [getcwd(), arg][path.isdir(arg)]
	try:
		get_files(url, base_dir)
	except Exception as e:
		print(f'Exception {traceback.format_exc()} : {e}' )
		exit(-1)