import cs50

def main():
    texto = cs50.get_string("Texto: ")
    sentencas= 0
    letras = 0
    palavras = 1
    
    for char in texto:
        if (char == '.' or char == '!' or char == '?'):
            sentencas += 1;
        elif(char == ' '):
            palavras += 1;
        elif(ord(char.lower()) >= 97 and ord(char.lower()) <= 122):
            letras += 1;
    
    print(palavras)
    L = 100 * (letras/palavras)
    S = 100 * (sentencas/palavras)
    indice = round(0.0588 * L - 0.296 * S - 15.8)
    
    if (indice < 1):
        print("Before grade 1")
    elif(indice > 16):
        print("Grade 16+")
    else:
        print(f"Grade {indice}")
    
        
main()