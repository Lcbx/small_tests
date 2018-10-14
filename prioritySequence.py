
class Organiser :
	
	def __init__(self):
		self.heap = []
	
	def push(self, basePriority, element):
		self.heap.append( (1./basePriority, 1./basePriority, element) )
	
	def pop(self):
		self.heap.sort(key = lambda l: (l[0], l[1]), reverse = True)
		current = self.heap.pop()
		return current
	
	def advance(self):
		current = self.pop()
		self.heap.append( (current[0] + current[1], current[1], current[2]) )
		return current[2]
		
size = 500
		
o = Organiser()

priorities = [23., 25., 27., 30., 38.]
for i in xrange(len(priorities)):
	o.push(priorities[i],i)

frequencies = [0,0,0,0,0]
for i in xrange(size):
	current = o.advance()
	if i > size - 20:
		print str(current) + ", ",
	frequencies[current] +=1
print
print frequencies

frequencies = list(priorities)
tot = 0
for i in frequencies:
	tot +=i
for i in xrange(len(frequencies)):
	frequencies[i] *= size/tot
print frequencies

# interesting :P