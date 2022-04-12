while True:
    try:
        x = int(input("Height: "))  # Grabs the height for use
    except ValueError:
        continue
    else:
        if x > 0 and x < 9:
            break


x = int(x)  # Converting value from string to integer
y = 0  # This value will be for incrementing height
z = x-1  # Copy of the height value for reverse increment
h = "#"
w = " "
while y < x:
    y += 1
    print("{}{}  {}".format(z * w, y * h, y * h))
    z -= 1
