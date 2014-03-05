from pymongo import MongoClient

class Node(object):
	def __init__(self, name=None, nodeType="actor", children=[], numberChildren=0):
		self._name = name
		self._nodeType = nodeType
		self._children = children
		self._numberChildren = numberChildren

	@property
	def name(self):
		return self._name

	@property
	def nodeType(self):
		return self._nodeType

	@property
	def children(self):
		return self._children

	@property
	def numberChildren(self):
		return self._numberChildren

	def addChild(self, name):
		self.children.append(name)
		self._numberChildren += 1

	def addChildren(self, children):
		self._children = children;
		self._numberChildren += len(children)

class Parser(object):
	def __init__(self, infile="", dbService=None):
		self._infile = infile
		self._dbService = dbService

	@property
	def infile(self):
		return self._infile

	def parse(self):
		with open(self._infile) as actorList:
			chunk = []
			for line in actorList:
				splitLine = line.split('\t')
				if len(splitLine) > 1:
					chunk.append(line)
				elif len(splitLine) == 1 and chunk:
					node = self.processChunk(chunk)
					self._dbService.createNode(node)
					chunk = []

	def processChunk(self, chunk):
		splitLines = [line.split('\t') for line in chunk]
		name = splitLines[0][0]
		movies = []
		for elem in splitLines:
			movies.append(elem[-1])
		node = Node(name = name)
		node.addChildren(movies)
		return node

class DatabaseService(object):
	"""docstring for DatabaseService"""
	def __init__(self, dbName=""):
		self._dbName = dbName
		client = MongoClient('localhost', 27017)
		self._db = client[dbName]

	@property 
	def dbName(self):
		return self._dbName

	def createNode(self, node):
		nodes = self._db.nodes
		nodes.insert({'name':node.name, 'children':node.children, 'type':node.nodeType, 'numberChildren':node.numberChildren})

		

# TESTS
def testNode():
	n = Node("Michael Jordan")
	n.addChild("Space Jam")
	n.addChild("Shazzam")
	assert (n.name == "Michael Jordan")
	assert (n.children == ["Space Jam", "Shazzam"])
	assert (n.numberChildren == 2)

def testParse():
	parser = Parser("dummy.data")
	parser.parse()

def testDataService():
	db = DatabaseService('test')
	n = Node("Michael Jordan")
	n.addChild("Space Jam")
	n.addChild("Shazzam")
	db.createNode(n)

def testIntegration():
	dbs = DatabaseService('test')
	parser = Parser("dummy.data", dbs)
	parser.parse()

if __name__ == "__main__":
	testIntegration()