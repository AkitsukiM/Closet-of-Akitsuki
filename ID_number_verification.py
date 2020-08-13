co = (7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2, 1)
ID_LEN = 18

while True:
    id = input("Input an ID number: ")
    if id == "exit":
        break
    if len(id) != ID_LEN:
        print("Error: ID number has an illegal length!")
        continue

    sum = 0
    illegal_character_flag = -1
    for i in range(ID_LEN - 1):
        if id[i] < "0" or id[i] > "9":
            illegal_character_flag = i
            break
        sum += co[i] * int(id[i])

    if illegal_character_flag != -1:
        print("Error: ID number has an illegal character {}!".format(id[illegal_character_flag]))
        continue

    sum = sum % 11
    sum = (12 - sum) % 11
    if sum == 10:
        sum = "X"
    else:
        sum = str(sum)
    if sum == id[ID_LEN - 1]:
        print("ID number verified successfully.")
    else:
        print("ID number verification failed. The last number should be {}.".format(sum))
