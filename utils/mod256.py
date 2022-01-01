def mod256(n):
    n = n + 1 & 0x800000ff
    if n < 0:
        n = (n - 1 | 0xffffff00) + 1

    return n

def main():
    for i in range(1000):
        print(
            mod256(i)
        )

    return

if __name__ == "__main__":
    main()