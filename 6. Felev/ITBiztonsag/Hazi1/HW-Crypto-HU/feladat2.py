inputfile1 = "LabProfile-v1.crypt"
inputfile1_1 = "LabProfile-v1.1.crypt"

input1 = open(inputfile1, "rb")
input1_1 = open(inputfile1_1, "rb")

eof = False
# while (eof == False):
#     line = ifile.read(16)
#     if(line != 1)
#         print(ifile.read(16))

text1_1 = input1_1.readlines()
lines1_1 = []
 
with open(inputfile1, "rb") as f:
    byte = f.read(1)
    while byte != "":
        print(byte)
        byte = f.read(1)

count = 0
# # Strips the newline character
# for line in text1_1:
#     count += 1
#     print("Line{}: {}".format(count, line.strip()))

input1.close()
input1_1.close()