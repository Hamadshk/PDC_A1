def readAndPerformMultiplication(filepath):
    with open(filepath, 'r') as file:
        lines = file.readlines()
        third_line = lines[2].strip()

    print(third_line)

    dimensions = map(int, third_line.split('X'))
    rows, col = dimensions

    with open(filepath, 'r') as file:
        matrix1 = []
        matrix2 = []
        count = 0
        for line in file:
            if count == 1 and third_line not in line.strip():
                matrix1.append(line.split(','))  
            elif third_line in line.strip():
                count += 1
            elif count == 2:
                matrix2.append(line.split(','))  


    print("Matrix 1:")
    for i in range(rows):
        for j in range(col):
            print(int(matrix1[i][j]), end=" ")
        print('\n')

    print("\nMatrix 2:")
    for i in range(rows):
        for j in range(col):
            print(int(matrix2[i][j]), end=" ")
        print('\n')

    result = [[0 for _ in range(col)] for _ in range(rows)]

    for i in range(rows):
        for j in range(col):
            sum = 0
            for k in range(rows):
                sum += int(matrix1[i][k]) * int(matrix2[k][j])
            result[i][j] = sum

    print("\nResult Matrix:")
    for i in range(rows):
        for j in range(col):
            print(int(result[i][j]), end=" ")
        print('\n')


readAndPerformMultiplication('/home/hamad/Desktop/PdcAssignment1/inputFIle.txt')
