from cs50 import get_float
# get input from user and calculate the minimum number of coins it would take to produce that amt (1, 5, 10, 25 cents)

# making sure user amount is a positive value
while True:
    amount = get_float("change owed: ")
    if amount > 0:
        break

counter = 0

# counting the individual coins is would take to get that amount
while True:
    if amount >= 0.25:
        amount = round(amount - 0.25, 2)
        counter += 1
    elif amount < 0.25 and amount >= 0.10:
        amount = round(amount - 0.10, 2)
        counter += 1
    elif amount < 0.10 and amount >= 0.05:
        amount = round(amount - 0.05, 2)
        counter += 1
    elif amount < 0.05 and amount >= 0.01:
        amount = round(amount - 0.01, 2)
        counter += 1
    elif amount == 0:
        break

# printing out the calculated amount
print(f"{counter}")