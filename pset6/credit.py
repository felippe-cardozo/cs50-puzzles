def main():
    card = int(input('Enter credit card: '))
    if check_len(card) and luhn(card):
        print(card_type(card))
        exit(0)
    print("Invalid card")
    return

def check_len(card):
    l = len(str(card))
    return l == 13 or l == 15 or l == 16

def luhn(card):
    #first step
    # turn card into string 
    cardlist = [int(i) for i in str(card)]
    # separate the odd and the even indexes
    odd = [ cardlist[i] for i in range(1, len(cardlist), 2) ]
    even = [ cardlist[i] for i in range(0, len(cardlist), 2) ]
    # multiple each odd index by 2
    odd = list(map(lambda x: 2 * x, odd))
    # some every digit
    odd_sum = 0
    for i in odd:
        if len(str(i)) == 1:
            odd_sum += i
        else:
            odd_sum += (i % 10) + (i // 10)
    even_sum = 0
    for i in even:
        even_sum += i
    return even_sum + odd_sum == 60

def card_type(card):
    l = len(str(card))
    if l == 15:
        return "AMEX"
    elif l == 13:
        return "VISA"
    elif l == 16:
        if str(card)[0] == '4':
            return "VISA"
        elif str(card)[0] == '5':
            return "MASTER"

if __name__ == "__main__":
    main()
