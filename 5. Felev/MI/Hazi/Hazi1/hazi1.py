test = False

if test:
    f = open("input.txt", "r")


#length and with
if test:
    line = f.readline()
else:
    line = input()

length = int(line.split('\t')[0])

width = int(line.split('\t')[1])

#num of pillars
if test:
    line = f.readline()
else:
    line = input()

numOfPillars = int(line)

#num of pallets5
if test:
    line = f.readline()
else:
    line = input()
numOfPallets = int(line)


class Coord:
    def __init__(self, x: int, y: int):
        self.x = x
        self.y = y


pillars = []

for idx in range(numOfPillars):
    if test:
        line = f.readline()
    else:
        line = input()
    pillars.append(Coord(int(line.split("\t")[1]), int(line.split("\t")[0])))



class Pallet:
    def __init__(self, length, width, id):
        self.length = length
        self.width = width
        self.id = id

    def rotate(self):
        tmp = self.length
        self.length = self.width
        self.width = tmp

    def __lt__(self, other):
         return self.length * self.width < other.length * other.width


pallets = []

for idx in range(numOfPallets):
    if test:
        line = f.readline()
    else:
        line = input()
    pallets.append(Pallet(int(line.split("\t")[1]), int(line.split("\t")[0]), idx + 1))


if test:
    f.close()

pallets.sort(reverse = True)
for p in pallets:
    if p.length > p.width:
        p.rotate()


class Matrix:
    palletsIn = []


    def __init__(self, width, length):
        self.width = width
        self.length = length
        self.matrix = [[0 for i in range(width)] for j in range(length)]

    def palletIn(self, pallet: Pallet):
        return pallet.id in self.palletsIn

    def write(self):
        for i in range(length): 
            for j in range(width): 
                if j == width - 1:
                    print(self.matrix[i][j], end = "\n")
                else:
                    print(self.matrix[i][j], end = "\t")

    def reset(self):
        for i in range(length): 
            for j in range(width): 
                self.matrix[i][j] = 0
    
    def checkPallet(self, pallet: Pallet, coord: Coord) -> bool:
        if width - coord.x >= int(pallet.width) and length - coord.y >= int(pallet.length):
            for i in pillars:
                if coord.x < i.x and i.x < coord.x + pallet.width:
                    if coord.y < i.y and i.y < coord.y + pallet.length:
                        return False
            for i in range(pallet.length): 
                for j in range(pallet.width): 
                    if self.matrix[coord.y + i][coord.x + j] != 0:
                        return False
            return True
        else:
            return False


    def addPallet(self, pallet: Pallet, coord: Coord) -> bool:
            for i in range(pallet.length): 
                for j in range(pallet.width):
                    self.matrix[coord.y + i][coord.x + j] = pallet.id
            self.palletsIn.append(pallet.id)

    def removePallet(self, pallet: Pallet, coord: Coord):
        for i in range(pallet.length): 
            for j in range(pallet.width): 
                self.matrix[coord.y + i][coord.x + j] = 0
        self.palletsIn.remove(pallet.id)







"""def valid(positions, newid, rotated: bool) -> bool:
    tmpMatrix = Matrix(width, length)
    for idx in range(newid):
        if(positions[idx] == -1):
            continue
        tmpMatrix.addPallet(pallets[idx], Coord(int(positions[idx]) % width, int(int(positions[idx]) / width)))

    if rotated:
        pallets[newid].rotate()
    if tmpMatrix.checkPallet(pallets[newid], Coord(int(positions[newid]) % width, int(int(positions[newid]) / width))) == False:
        return False
        
    tmpMatrix.addPallet(pallets[newid], Coord(int(positions[newid]) % width, int(int(positions[newid]) / width)))
    
    return True"""


"""def solve(positions, numOfPlacedPellets) -> bool:
    if numOfPlacedPellets == numOfPallets:
        return True #valid(positions, False) or valid(positions, True)

    for idx in range(numOfPallets):
        
        if positions[idx] != -1:
            continue

        tmp = positions
        for i in range((length - min(pallets[idx].length, pallets[idx].width)) * width):
            #pos = Coord(int(positions[idx]) % width, int(int(positions[idx]) / width)
            tmp[idx] = i
            if valid(tmp, numOfPlacedPellets, False) and solve(tmp, numOfPlacedPellets + 1):
                return True
            elif valid(tmp, numOfPlacedPellets, True) and solve(tmp, numOfPlacedPellets + 1):
                return True
        tmp[idx] = -1

        return False"""

num = 0


def solve(matrix: Matrix, numOfPlacedPellets) -> bool:
    if numOfPlacedPellets == numOfPallets:
        return True

    #if numOfPlacedPellets == 1:
        #print(numOfPlacedPellets)

    for idx in range(numOfPlacedPellets, numOfPallets):
        pallet = pallets[idx]
        tmp = matrix
        added = False
        m =  min(pallet.width, pallet.length)
        for i in range(length * (width - m + 1)): 
            #range((length - m + 1) * width):
            #pos = Coord(int(i) % width, int(int(i) / width))
            pos = Coord(int(int(i) / width), int(i) % width)
            """ if not width - m >= pos.x:
                continue
            if(pos.x > width - p.width):
                continue"""
            if tmp.matrix[pos.y][pos.x] != 0:
                continue
            if tmp.checkPallet(pallet, pos):
                tmp.addPallet(pallet, pos)
                added = True
                if solve(tmp, numOfPlacedPellets + 1):
                    return True
                else:
                    added = False
                    tmp.removePallet(pallet, pos)
            pallet.rotate()
            if tmp.checkPallet(pallet, pos):
                tmp.addPallet(pallet, pos)
                added = True
                if solve(tmp, numOfPlacedPellets + 1):
                    return True 
                else:
                    added = False
                    tmp.removePallet(pallet, pos)  

        return False




result = Matrix(width, length)
solve(result, 0)
#result.reset()


#for idx in range(len(positions)):
        #result.addPallet(pallets[idx], Coord(positions[idx] % width, int(positions[idx] / width)))

result.write()












