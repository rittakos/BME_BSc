test = True

if test:
    f = open("input.txt", "r")


if test:
    line = f.readline()
else:
    line = input()

numfOfNodes = int(line)


nodes = []

class Node:
	def __init__(self, id: int, numOfValues: int, chances, chanceTable, parents):
		self.id = id
		self.numOfValues = numOfValues
		self.chances = chances
		self.chanceTable = chanceTable
		self.parents = parents
		self.childrens = []
		self.fixValue = -1
		self.__initParents()
	
	def __initParents(self):
		for i in range(len(self.parents)):
			self.addParent(self.parents[i])
	
	def getChance(self, value: int):
		if len(self.chances) <= value:
			return -1
		if self.fixValue != -1:
			return self.chances[self.fixValue]
		return self.chances[value]
		
	def getChanceFromTable(self, parentValues, value):
		key = ""
		values = parentValues
		for i in range(len(values)):
			if i < len(values) - 1:
				key += str(values[i]) + ","
		key += str(values[-1])
		if key in self.chanceTable:
			return self.chanceTable[key].split(",")[value]
		return -1
	
	def addChildren(self, childrenId):
		self.childrens.append(childrenId)
		
	def addParent(self, parentId):
		if not parentId in parents:
			self.parents.append(parentId)
		nodes[parentId].addChildren(self.id)
		
	def setFixValue(self, value: int):
		self.fixValue = value
		
	def P(self, value: int):
		result = 0.0
		# for key, chance in chanceTable.items():
		# 	add = True
		# 	i = 0
		# 	for c in key.split(","):
		# 		if nodes[parents[i]].fixValue != -1:
		# 			if nodes[parents[i]].fixValue != int(c):
		# 				add = False
		# 				break
		# 	i += 1
		# 	if add:
		# 		result += float(chance.split(",")[value])
		

		


		return result




	



for i in range(numfOfNodes):
    if test:
        line = f.readline()
    else:
        line = input()
        
    k = int(line.split("\t")[0])
    parentsNum = int(line.split("\t")[1])

    parents = []
    chances = []
    chanceTable = {}

    for j in range(parentsNum):
        parents.append(int(line.split("\t")[2 + j]))

    if parentsNum == 0:
        chs = line.split("\t")[2 + parentsNum]
        for j in range(k):
            chances.append(float(chs.split(",")[j]))
    else:
        for j in range(len(line.split("\t")) - 2 - parentsNum):
            chs = line.split("\t")[2 + parentsNum + j]
            chanceTable[chs.split(":")[0]] = chs.split(":")[1]

    nodes.append(Node(i, k, chances, chanceTable, parents))

    

if test:
    line = f.readline()
else:
    line = input()

numOfEvidenceVariables = int(line)

for i in range(numOfEvidenceVariables):
    if test:
        line = f.readline()
    else:
        line = input()
    
    id = int(line.split("\t")[0])
    value = int(line.split("\t")[1])

    nodes[id].setFixValue(value)


if test:
    line = f.readline()
else:
    line = input()

targetVariable = int(line)    




def FelsorolasLekerdezes(currentId: Node, parentValues, bn):
	Q = []
	for xi in range(currentId.numOfValues):
		return 0
		#Q.append(FelsorolMindet())
	return Q

def FElsorolMindet(variables, e):
	if len(variables):
		return 1.0




def Count(value: int):
	result = 0.0

	return result



#print (nodes[2].getChanceFromTable([1, 0], 1))
#print (nodes[2].fixValue)

#print(nodes[targetVariable].chanceTable)

for value in range(nodes[targetVariable].numOfValues):
    print(Count(value))














