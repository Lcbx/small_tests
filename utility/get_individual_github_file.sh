#!/bin/bash

# windows dependent, useequi valent or use command line version
url=$(powershell -command "Get-Clipboard") #$1
url=${url/github.com/raw.githubusercontent.com}
url=${url/blob\//}
#echo $url
file=${url##*/}
#echo $file
curl $url > $file