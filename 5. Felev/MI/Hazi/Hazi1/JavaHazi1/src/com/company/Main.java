package com.company;

public class Main {

    public static void main(String[] args)
    {
        String line = input()
        length = int(line.split("\t")[0])
        width = int(line.split("\t")[1])

        #num of pillars
            line = input()
        numOfPillars = int(line)

        #num of pallets5
            line = input()
        numOfPallets = int(line)


        int[numOfPallets] positions;
        for (int i = 0; i < numOfPallets; ++i)
            positions.add(-1);
        solve(positions, 0)

        result = Matrix(length, width)
        result.reset

        for idx in range(len(positions)):
        result.addPallet(pallets[idx], Coord(positions[idx] % width, int(positions[idx] / width)))

        result.write()
    }
}




class Coord:
        def __init__(self, x: int, y: int):
        self.x = x
        self.y = y


        pillars = []

        for idx in range(numOfPillars):
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
        line = input()
        pallets.append(Pallet(int(line.split("\t")[0]), int(line.split("\t")[1]), idx + 1))

        pallets.sort()


class Matrix:

        def __init__(self, width, length):
        self.width = width
        self.length = length
        self.matrix = [[0 for i in range(length)] for j in range(width)]

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

        def addPallet(self, pallet: Pallet, coord: Coord) -> bool:
        if length - coord.x >= int(pallet.length) and width - coord.y >= int(pallet.width):
        for i in pillars:
        if i.x > coord.x and i.x < coord.x + pallet.width:
        return False
        if i.y > coord.y and i.y < coord.y + pallet.length:
        return False
        for i in range(pallet.length):
        for j in range(pallet.width):
        if self.matrix[coord.x + i][coord.y + j] != 0:
        return False
        for i in range(pallet.length):
        for j in range(pallet.width):
        self.matrix[coord.x + i][coord.y + j] = pallet.id
        return True
        else:
        return False








        def valid(positions, rotated: bool) -> bool:
        tmpMatrix = Matrix(length, width)
        for idx in range(numOfPallets):
        if(positions[idx] == -1):
        continue
        if rotated:
        pallets[idx].rotate()
        if tmpMatrix.addPallet(pallets[idx], Coord(int(positions[idx]) % width, int(int(positions[idx]) / width))) == False:
        #if rotated:
        #    pallets[idx].rotate()
        return False

        return True


        def solve(positions, numOfPlacedPellets) -> bool:
        if numOfPlacedPellets == numOfPallets:
        return valid(positions, False) or valid(positions, True)

        for idx in range(numOfPallets):

        if positions[idx] != -1:
        continue

        tmp = positions
        for i in range(length * width):
        #pos = Coord(int(positions[idx]) % width, int(int(positions[idx]) / width)
        tmp[idx] = i
        if valid(tmp, False) and solve(tmp, numOfPlacedPellets + 1):
        return True
        elif valid(tmp, True) and solve(tmp, numOfPlacedPellets + 1):
        return True
        tmp[idx] = -1

        return False
















