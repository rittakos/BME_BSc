inputfile = "LabProfile-v1.1.crypt"

ifile = open(inputfile, "rb")

eof = False
while (eof == False):
    print(ifile.read(16))