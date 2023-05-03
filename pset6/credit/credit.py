import cs50

def main():
    number = str(cs50.get_int("Number: "))
    soma = 0
    i = len(number)
    
    for num in number:
        num = float(num)
        if (i % 2 == 1):
            soma += num
        else:
            num *= 2
            if num >= 10:
                soma += num % 10
                num -= num % 10
                num /= 10
                soma += num
            else:
                soma += num
        i -= 1
        
    if (soma % 10 == 0):
        n1 = int(number[0])
        n2 = int(number[1])
        if n1 == 3 and n2 == 4 or n2 == 7:
            print("AMEX")
        elif n1 == 5 and 1 <= n2 <= 5:
            print("MASTERCARD")
        elif n1 == 4:
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")

    
main()