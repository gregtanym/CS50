from cs50 import get_int
# make a half pyramid with input between 1 and 8

while True:
    answer = get_int("Height:")
    if answer >= 1 and answer <= 8:
        break

for i in range(answer):
    print(" " * (answer - (i+1)), end = "")
    print("#" * (i+1))