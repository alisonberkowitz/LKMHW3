most = max(open('actors.list', 'r'), key=len)
print most
print 'Length:'
print len(most)