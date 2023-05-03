import cs50

def main():
    while True:
        altura = cs50.get_int("Height: ")
        if altura > 0 and altura < 9:
            break
        
    for i in range(altura):
        i += 1
        print(" " * (altura - i), end="")
        print("#" * (i), end = "")
        print(" ", end = "")
        print("#" * (i))
       
    # Outro jeito, tratando como uma matriz
    #for i in range(0, altura, 1):
    #    for j in range(0, altura + i + 2, 1):
    #        if(j == altura or i+j < altura - 1):
    #           print(" ", end = "")
    #        else:
    #           print("#", end = "")
    #   print()
    
        
main()

