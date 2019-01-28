#######################
## english decoder
## helps find the original text when a letter substitution scheme is used (ex: "A"=> "Z")
#######################
import random


text = "FGFDDIVALEHVLHQFLJFHJTFLXHLUMDDHT@FLXBFLJHTMXMGITLKIQUDLNBMGBLBI@FLGHQQFGXFULXBFPLNMXBLIQHXBFVLIQULXHLIDDRPFLIPHQSLXBFLJHNFVDLHELXBFLFIVXBLXBFLDFJIVIXFLIQULFCRITLDXIXMHQLXHLNBMGBLXBFLTINDLHELQIXRVFLIQ"

# for this to work, remember to put text to upper case
# (yes i know it already is)
text = text.upper()

# a dictionnary for all possible symbol
symbols = {}
	
# counts the number of occurences each symbol
for letter in text:
	if letter in symbols:
		symbols[letter] += 1
	else :
		symbols[letter] = 1

# we calculate their frequency
for letter in symbols.keys():
	symbols[letter] = symbols[letter]/len(text)  

	
symbols = sorted(symbols.items(), key = lambda x: x[1], reverse = True)
print ("fequencies found :\n", symbols, "\n")


# classes of letters depending on frequency 
english = ( " EART", " EARTIONSLH", "RTIONSLHDC", "SLHDCUMPGB","UMPGBGBFYWK", "FYWKVXZJQ",)

# sequences of letters often found in text
often = ("TH", "HE", "IN", "EN", "NT", "RE", "ER", "AN", "TI", "ES", "ON", "AT", "SE", "ND", "OR", "AR", "AL", "TE", "CO", "DE", "TO", "RA", "ET", "ED", "IT", "SA", "EM", "RO",  "THE", "AND", "THA", "ENT", "ING", "FOR", "NDE", "HAS", "NCE", "EDT", "TIS", "OFT", "MEN", "TION", )



translator = {

# test substitutions here
# => put the letters you found in here
# don't forget to put one of the most frequent character as " " (space)
# it's the most important step

"L":" ",

"I":"A",
"Q":"N",
"U":"D",

"E" :"F",
"H":"O",
"V":"R",

"N":"W",
"B":"H",
"M":"I",

}

# candidates[char]=> [all possible letters, in a string]
symbols =[x[0] for x in symbols]
candidates = {}
# we put the possible translations in candidates
for i, c in enumerate(symbols):
	if c not in candidates:
		index = int(i/len(symbols)*len(english)+0.1)
		candidates[c] = english[index]
#print("candidates :\n", candidates, "\n")



possibleTranslations = {}
# a helper function
def publish(key, value):
	if key in possibleTranslations:
		possibleTranslations[key] += value
	else :
		possibleTranslations[key] = value

# a probality score is computed for a code to be a specific letter,
# based on the sequences  found “often” in english
size = len(text)
text += "@@@@@@" #padding
for i in range(size):
	for t in often:
		similar = True
		for j, c in enumerate(t):
			if c not in candidates[ text[i + j] ]:
				similar = False
		if similar:
			for j, c in enumerate(t):
				publish( (text[i + j], c), len(t) )

possibleTranslations = sorted(possibleTranslations.items(), key = lambda x: x[1], reverse = True)
#print("possible translations :\n", possibleTranslations, "\n")


# the most probable translations are added first
for item, f in possibleTranslations:
	code, char = item
	if code not in translator and char not in translator.values():
		translator[code] = char
#print("translator :\n", translator, "\n")



# then the "voids" are filled randomly 
result = ""
for c in text:
	if c not in translator:
		candidate = ""
		while True:
			candidate = random.choice(candidates[c])
			if candidate not in translator.values() :
				break
		translator[c] = candidate
	result += translator[c]

# a one code/one letter display is pretty usefull
i = 0 
pad = 76	
while i<len(text):
		if i+pad>len(text):
			pad = len(text)-i
		print("  " + text[i: i+pad])
		print("=>" + result[i: i+pad]+ "\n")
		i+=pad

# pretty print of the result
print("\n\"\"\"" + result + "\"\"\"")

