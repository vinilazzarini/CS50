import csv
from sys import argv

def main():
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        return 1
    
    strs = []
    with open(f"{argv[1]}", "r") as databasefile:
        reader = csv.DictReader(databasefile)
        strs = reader.fieldnames[1:]
    
    bases = {}        
    for base in strs:
        bases[base] = 0
    
    with open(f"{argv[2]}", "r") as sequencesfile:
        texto = sequencesfile.read()
        for key in strs:        
            maximo = 0
            tam_str = len(key)
            for i in range(len(texto)):
                atual = 0 
                
                if texto[i: i + tam_str] == key:
                    atual += 1
                    
                    while texto[i: i + tam_str] == texto[i + tam_str : i + tam_str * 2]:
                        atual += 1
                        i += tam_str
            
                if atual > maximo:
                    maximo = atual
            
            bases[key] = maximo
                    
    with open(f"{argv[1]}", "r") as databasefile:
        reader = csv.DictReader(databasefile)
        
        profiles= []
        dono = False
        for row in reader:
            for key in bases:
                if int(row[key]) == int(bases[key]):
                    dono = True
                else:
                    dono = False
            
            if dono == True:
                print(row["name"])
                break
        if dono == False:  
            print("No Match")
     
main()