import cs50

def main():
    while True:
        altura = cs50.get_int("Height: ")
        if altura > 0 and altura < 9:
            break
        
    for i in range(altura):
        i += 1
        print(" " * (altura - i), end="")
        print("#" * (i))
        
main()