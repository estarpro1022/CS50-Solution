while True:
    try:
        height = int(input("Height: "))
        if 1 <= height <= 8:
            break
        print("Invalid number. Enter again!")
    except Exception:
        print("Invalid number. Enter again!")

for i in range(height):
    for j in range(height - i - 1):
        print(" ", end="")
    for j in range(i + 1):
        print("#", end="")
    print("  ", end="")
    for j in range(i + 1):
        print("#", end="")
    print()