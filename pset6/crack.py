import crypt
import sys

alphabet = [chr(i) for i in range(65, 65 + 26)]
alphabet += [chr(i) for i in range(97, 97 + 26)]
crypted = sys.argv[1]

def main():
    if sys.argv != 2:
        exit(1)
    brute_force()

def match_pwd(candidate):
    return crypt.crypt(candidate, crypted[0:2]) == crypted

def brute_force():
    s = ""
    test_match(s)
    # 2 digits
    for i in alphabet:
        test_match(i)
    # 3 digits
    for i in alphabet:
        for j in alphabet:
            test_match(i + j)
    # 4 digits
    for i in alphabet:
        for j in alphabet:
            for k in alphabet:
                test_match(i + j + k)
    return False

def test_match(s):
    for i in alphabet:
        if match_pwd(s + i):
            print("pass = {}".format(s + i))
            exit(0)
           
if __name__ == "__main__":
    main()
