""" Credit card check """
ini = input("Number: ")  # Grabbing user's input

# Initializing variables for use
smp2 = int(ini)
smp = int(ini)
length = len(ini)
i = 1
product = 0
sum = 0

while smp > 0:
    samp = smp % 10
    if i % 2 == 0:
        val = samp * 2
        if val > 9:
            product += (val // 10) + (val % 10)  # Separating both values
        else:
            product += val
    else:
        sum += samp

    smp //= 10
    i += 1


totalVal = product + sum  # Getting the total sum of both values

if totalVal % 10 == 0:
    visaChck = smp2 // 10**(length-1)
    cardChck = smp2 // 10**(length-2)
    if visaChck == 4:
        print("VISA")
    if cardChck in (34, 37):
        print("AMEX")
    if cardChck >= 51 and cardChck <= 55:
        print("MASTERCARD")
else:
    print("INVALID")
