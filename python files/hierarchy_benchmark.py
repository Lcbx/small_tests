from dataclasses import dataclass, field
from typing import Callable
from copy import copy

# trash lib :
#from treelib import Node, Tree


@dataclass
class AbstractNode:
	name:		str
	
	def getParent(self):
		raise Exception( "not implemented")
	
	def setParent(self, _parent):
		raise Exception( "not implemented")
	
	def hasChildren(self):
		raise Exception( "not implemented")
	
	def getChildren(self):
		raise Exception( "not implemented")
		
	def getFirstChild(self):
		raise Exception( "not implemented")
		
	###
	# functions used to verify tree is legit :
	
	def __repr__(self):
		return f"{type(self).__name__ }: {self.name} { ','.join(child.name for child in self.getChildren() )}"
	def __str__(self):
		return self.name
	
	def countNodes(self):
		total_nodes = 1
		for child in self.getChildren():
			total_nodes += child.countNodes()
		return total_nodes
		
	def printTree(self, level = 0):
		def prettyName(_name): # align names
			return f"{'-' * (7-len(_name))}{_name}"
		
		repr = prettyName(self.name)
		if level > 0:
			repr =  f" {'        ' * (level-1)}    |--{repr}"
		
		# put first child on same line
		current = self
		exploredLevel = level
		while current.hasChildren():
			firstChild = current.getFirstChild()
			exploredLevel +=1
			repr  += f"-{prettyName(firstChild.name)}"
			current = firstChild
		
		print(repr)
		
		# end traversal
		while exploredLevel != level:
			current = current.getParent()
			exploredLevel -=1
			current._EndPrintTree(level)
	
	def _EndPrintTree(self, level):
		it = self.getChildren()
		next(it)
		for child in it:
			child.printTree(level+1)



# class used for naïve conceptual implementation
@dataclass
class NaiveNode(AbstractNode):
	parent: 	object = None
	children:	list   = field(default_factory = lambda: [])
	
	def getParent(self):
		return self.parent
	
	def setParent(self, _parent ):
		self.parent = _parent
		if _parent != self:
			if not _parent.children:
				_parent.children = []
			_parent.children.append(self)
	
	def hasChildren(self):
		return len(self.children) != 0
		
	def getChildren(self):
		for child in self.children:
			yield child 
		
	def getFirstChild(self):
		return self.children[0]

# my idea : dict with binary representation hash used :
# for node of hash n, 2n+1 is first child, 2n+2 is child's first sibling
relationDict = {}
@dataclass
class MyNode(AbstractNode):
	hash : int = 0
	
	def getParent(self):
		global relationDict
		pHash = int( (self.hash-1)/2 ) 
		if pHash in relationDict:
			return relationDict[pHash]
		return self
		
	def setParent(self, _parent ):
		global relationDict
		childhash = int( _parent.hash*2+1 )
		if childhash not in relationDict:
			self.hash = childhash
		else:
			siblingHash = int( childhash*2+2 )
			while True :
				self.hash = siblingHash
				if siblingHash not in relationDict:
					break
				siblingHash = int( siblingHash*2+2 )
		relationDict[self.hash] = self
			
	
	def hasChildren(self):
		global relationDict
		childHash = int( self.hash*2+1 ) 
		return childHash in relationDict
		
	# THIS is where the problem is.
	# by the end of the day we ended with a linked list of children
	def getSibling(self):
		siblingHash = int( self.hash*2+2 )
		if siblingHash in relationDict:
			return relationDict[siblingHash]
		return None
		
	def getChildren(self):
		global relationDict
		childHash = int( self.hash*2+1 )
		if childHash in relationDict:
			current = relationDict[childHash]
			while current != None:
				yield current
				current = current.getSibling()
		
	def getFirstChild(self):
		return next(self.getChildren())
	

if __name__ == '__main__':
	#from time import time
	from datetime import datetime
	from random import seed, randrange
		
	def buildRandomHierarchy(type, nodeCount):
		seed(42)
		nodes = [type(f'test{i}') for i in range(nodeCount)]
		root = nodes[0]
		root.setParent(root) # avoid tripping checks
		# randrange(0) throws exception
		nodes[1].setParent(root)
		it = -1
		for i, node in enumerate(nodes):
			i-=1 # can't be your own parent
			if i < 1:
				# setup done for root and first Node
				continue
			node.setParent(nodes[randrange(i)])
		assert all( node.getParent() != None for node in nodes), 'some nodes don\'t have a parent'
		count = nodes[0].countNodes()
		assert count == nodeCount, f'count is {count} instead of expected {nodeCount}'
		return nodes
	
	def timereps(reps, func):
		start = datetime.now()
		for _ in range(reps):
			func()
		end = datetime.now()
		#print(end - start)
		# returns average time / rep
		return (end - start) / float(reps)
	
	
	SIZE = 100000
	hierarchyNaive = buildRandomHierarchy(NaiveNode, SIZE)
	#hierarchyNaive[0].printTree()
	
	print("-----------------------")
	
	relationDict = {}
	hierarchyMine = buildRandomHierarchy(MyNode, SIZE)
	#hierarchyMine[0].printTree()
	
	# TODO : better test : we have a list of Nodes and we want to traverse them and their children the fastest way possible
	# my method can help us iterate the hierarchy in a memory-firendly way
	
	def test(node):
		def apply():
			node[randrange(SIZE)].countNodes()
		return apply
	
	naiveResult = timereps(SIZE, test(hierarchyNaive))
	myResults =   timereps(SIZE, test(hierarchyMine))
	#
	print(f'Naive {naiveResult}')
	print(f'Mine  {myResults}')
				

###
# By the end of the day that looks a lot like premature optimization