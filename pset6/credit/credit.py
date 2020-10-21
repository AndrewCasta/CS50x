from cs50 import get_int

# function to return index of longer number


def d(number, n):
    return number // 10**n % 10


# get credit card number
cn = get_int("Please enter your card #: ")
# cn = 4111111111111111


# print(cn)
# print(d(cn,0))

check1 = 0
# check return
# for each number in cn (0 -> 16, increment of 2)
# d(cn,(i)) = return index of cn
# d(return,0)+d(return,1)
# d(d(cn,(i)),0)+d(d(cn,(i)),1)

for i in range(1, 16, 2):
    check1 += d(d(cn, (i)) * 2, 0)+d(d(cn, (i)) * 2, 1)
# print(check1)


check2 = 0
for i in range(0, 17, 2):
    check2 += d(cn, i)
# print(check2)

checkSum = check1 + check2
# print(checkSum)

# MasterCard - 16-digit - start with 51, 52, 53, 54, or
mc = cn // 10**14 % 100
# American Express - 15-digit - start with 34 or 37
ae = cn // 10**13 % 100
# Visa - 13 & 16-digit - start with 4
v16 = cn // 10**15 % 10
v13 = cn // 10**12 % 10


if checkSum % 10 == 0:
    if mc == 51 or mc == 52 or mc == 53 or mc == 54 or mc == 55:
        print("MASTERCARD")
    if ae == 34 or ae == 37:
        print("AMEX")
    elif v16 == 4 or v13 == 4:
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")
