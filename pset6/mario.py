import sys

def main():
    mario(int(sys.argv[1]))

def mario(n):
    blank = " "
    hashtag = "#"
    count = 1
    for i in range(n):
        print((n - 1) * blank + count * hashtag + blank + count * hashtag) 
        n = n -1
        count += 1

if __name__ == "__main__":
    main()
