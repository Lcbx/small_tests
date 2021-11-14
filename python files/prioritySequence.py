import collections

Entry = collections.namedtuple('Entry', 'time priority item')

class Organiser :
	
	def __init__(self):
		self.heap = []
		self.time = 0.
	
	# linear complexity push algorithm
	def _push(self, priority, item):
		current = Entry(self.time + 1./priority, priority, item)
		for i, entry in enumerate(self.heap):
			if current.time > entry.time:
				self.heap.insert(i, entry)
				return
		self.heap.append(current)
	
	# log(n) complexity push algorithm
	def push(self, priority, item):
		entry = Entry(self.time + 1./priority, priority, item)
		if len(self.heap) == 0:
			self.heap.append(entry)
		else:
			self.heap.insert(self.findPlace(entry), entry)
	
	# divide and conquer algorithm, for kicks
	def findPlace(self, entry):
		return self._findplace(entry, 0, len(self.heap))
		
	def _findplace(self, entry, start, end):
		space = end - start
		if space <= 1:
			if entry.time > self.heap[start].time:
				return start
			else:
				return end
			
		median = start + space//2
		if entry.time > self.heap[median].time:
			return self._findplace(entry, start, median)
		else:
			return self._findplace(entry, median, end)
			
	
	def pop(self):
		current = self.heap.pop()
		self.time = current.time
		return current

		
if __name__ == "__main__":

	size = 20000
			
	o = Organiser()
	
	priorities = [*range(1, 500)] 
	for number in priorities:
		o.push(number, number)
	
	frequencies = [0] * len(priorities)
	for i in range(size):
		current = o.pop()
		o.push(current.priority, current.item)
		if i < 20:
			print(str(current.item) + ", ", end = "")
		frequencies[current.item-1] +=1
	print()
	print(frequencies)

	frequencies = list(priorities)
	tot = 0
	for i in frequencies:
		tot +=i
	for i in range(len(frequencies)):
		frequencies[i] *= size/tot
	print(frequencies)

	# interesting :P