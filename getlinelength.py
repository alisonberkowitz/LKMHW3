""" Copyright 2013 Nathan Lintz and Alison Berkowitz
	This file parses actors.list to find the longest line.
	This is so we know what line length to give fgets in our C parser
"""
most = max(open('actors.list', 'r'), key=len)
print most
print 'Length:'
print len(most)