def MS(wierz,kraw):
    tab = [[] * for i in range(wierz)]
    for i in range(kraw):
        wierz1,wierz2 = map(int,input().split())
        tab[wierz1].append(wierz2)
        tab[wierz2].append(wierz1)
    for i in range(wierz):
        print(tab[i])
        
MS(8,11)
    
