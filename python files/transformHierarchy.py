from dataclasses import dataclass, field
from typing import Callable
from copy import copy

@dataclass
class HierarchyNode:
	name:				str
	parent: 			object
	
	hash:				int = 0
	nChildren:			int = 0
	siblingIndex:		int = 0
	
	localTransform:		float = 0
	parentTransform:	float = 0
	globalTransform:	float = 0
	
	def __hash__(self):
		return hash
	
	def getRootChildHash(self, nChild):
		# root does not have siblings, so both spot 1 and 2 are its children
		pair = n%2==0
		n = n//2
		if pair:
			return 2**(n+2)-2
		return getChildHash(n)
	
	def getChildHash(self, nChild):
		n  = nChild
		ph = self.hash
		ch = 2*ph+1 if n == 0 else 2**(n+1) * ph + 2**(n+1) + 2**(n) -2
		return ch
	
	def getParentHash(self):
		index = self.siblingIndex
		temp = 2**(index + 1)
		ph = max((self.hash - temp +1)//temp, 0)
		return ph
	
	def updateGlobalTransform(self):
		self.globalTransform = self.localTransform * self.parentTransform


class HierarchySystem:
	def __init__(self):
		self.root = HierarchyNode(name = "root", parent = None)
		self.hierarchy = { 0 : self.root }
	
	def AddNode(self, node : HierarchyNode):
		childhash = root.getRootChildHash(root.nChildren)
		self._addChild(childhash, root, child)
	
	def AddChild(self, parent : HierarchyNode, child : HierarchyNode):
		childhash = parent.getChildHash(parent.nChildren)
		self._addChild(childhash, parent, child)
	
	def _addChild(self, childhash : int, parent : HierarchyNode, child : HierarchyNode):
		child.hash = childhash
		self.hierarchy[childhash] = child
		child.siblingIndex = parent.nChildren
		parent.nChildren += 1
		child.globalTransform = parent.globalTransform
		child.updateGlobalTransform()


depth = 1
width = 10

hierarchy = HierarchySystem()

all = []
u = [hierarchy.root]
v = []
for i in range(depth):
	while u:
		parent = u.pop()
		for j in range(width):
			child = HierarchyNode(parent.name + str(j), parent)
			hierarchy.AddChild(parent, child)
			v.append(child)
		all.append(parent)
	u,v = v,u

res = sorted(all+u, key=lambda node:node.hash)
for node in res:
	print(node.name, node.hash, node.nChildren, node.getParentHash(), sep='\t')

for n1, n2 in zip(res, res[1:]):
	assert(n1.hash<n2.hash)
