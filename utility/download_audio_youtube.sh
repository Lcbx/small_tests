 #!/bin/bash
 
# windows dependent, use equivalent or use command line version
./youtube-dl --extract-audio --audio-format mp3 $(powershell -command "Get-Clipboard") #$1 