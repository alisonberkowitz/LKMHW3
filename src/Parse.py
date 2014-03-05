""" Copyright 2013 Nathan Lintz and Alison Berkowitz
	This file contains parsing logic and database logic for putting a 
	dataset of actors and movies into a mongo database
"""
from pymongo import MongoClient

class Node(object):
	"""An object that represents a movie or an actor."""
	def __init__(self, name=None, nodeType="actor", children=[], numberChildren=0):
		self._name = name # Movie Name
		self._nodeType = nodeType # node type -> either actor or movie
		self._children = children # children of the movie node -> movies for actors and vice versa
		self._numberChildren = numberChildren # how many children the node has

#   Getters for the class attributes
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

	""" 
		Adds a single child to the node

		name: string representing the child's name
	"""
	def addChild(self, name):
		self.children.append(name)
		self._numberChildren += 1

	""" 
		Adds many children to the node

		children: array of stirngs represeting many children for the node
	"""
	def addChildren(self, children):
		self._children = children;
		self._numberChildren += len(children)

class Parser(object):
	"""An object that goes through the data file line by line and extracts nodes.
	This object is also responsible for putting the nodes into the database.

	infile: file name you want to parse
	dbService: database system that puts nodes into the mongo database
	"""
	def __init__(self, infile="", dbService=None):
		self._infile = infile
		self._dbService = dbService

#   Getters for the class attributes
	@property
	def infile(self):
		return self._infile

	"""
	Reads the file line by line and looks for actors and their respective movies. 
	Puts the actor nodes into a mongo database
	"""
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
	"""
	Reads in a chunk from the file and puts the data into the node model

	chunk: an array of strings which contain the actors name and all movies they've
	been in
	"""
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
	"""An object which we use to interact with the mongo database

	dbName: string for the name of the database you want mongo to use
	"""

	def __init__(self, dbName=""):
		self._dbName = dbName
		client = MongoClient('localhost', 27017) # Creates the connection to mongo database
		self._db = client[dbName]

#   Getters for the class attributes
	@property 
	def dbName(self):
		return self._dbName

	"""
	Takes a node model and inserts it into the database

	node: node model that will be inserted into the node collection
	"""
	def createNode(self, node):
		nodes = self._db.nodes
		nodes.insert({'name':node.name, 'children':node.children, 'type':node.nodeType, 'numberChildren':node.numberChildren})
		nodes.ensure_index('name')

		

# TESTS

# Creates a node and checks that its attributes are set properly
def testNode():
	n = Node("Michael Jordan")
	n.addChild("Space Jam")
	n.addChild("Shazzam")
	assert (n.name == "Michael Jordan")
	assert (n.children == ["Space Jam", "Shazzam"])
	assert (n.numberChildren == 2)

# Parses the text file
def testParse():
	parser = Parser("dummy.data")
	parser.parse()

# Creates dummy data into our database to test that inserts are working properly
def testDataService():
	db = DatabaseService('test')
	n = Node("Michael Jordan")
	n.addChild("Space Jam")
	n.addChild("Shazzam")
	db.createNode(n)

# Tests that the database service can connect with the parser to insert actors into the db
def testIntegration():
	dbs = DatabaseService('test')
	parser = Parser("dummy.data", dbs)
	parser.parse()

if __name__ == "__main__":
	testIntegration()