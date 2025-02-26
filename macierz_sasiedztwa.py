def MS(wierz,kraw):
    tab = [[0] * wierz for i in range(wierz)]
    for i in range(kraw):
        wierz1, wierz2 = map(int,input().split())
        tab[wierz1][wierz2] = 1
        tab[wierz2][wierz1] = 1
    for i in range(wierz):
        for j in range(wierz):
            print(tab[i][j],end=" ")
        print(end="\n")

MS(8,11)
    
