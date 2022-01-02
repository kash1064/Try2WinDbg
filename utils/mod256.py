def mod256(n):
    n = n & 0x800000ff
    if n < 0:
        n = (n - 1 | 0xffffff00)

    return n

def main():
    for i in range(250, 260):
        print(mod256(i), end=" ")
    print("")

    return

if __name__ == "__main__":
    main()