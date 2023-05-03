import cs50

def main():
    while True:
        valor = cs50.get_float("Valor: ")
        if valor > 0:
            break
    
    valor = round(valor*100)
    moedas = 0 
    moeda = (25,10,5,1)
    i = 0
    for i in range(0, 4, 1):
        while valor >= moeda[i]:
            valor -= moeda[i]
            moedas += 1
    
    print(moedas)

main()