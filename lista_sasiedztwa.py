def MS(wierz, kraw):
    macierz = [[0] * wierz for i in range(wierz)]
    for i in range(kraw):
        wierz_1, wierz_2 = map(int, input().split())
        macierz[wierz_1][wierz_2] = 1
        macierz[wierz_2][wierz_1] = 1
    for i in range(wierz):
        for j in range(wierz):
            print(macierz[i][j], end = " ")
        print(end = "\n")
        

l_wierz, l_kraw = map(int, input().split())
MS(l_wierz, l_kraw)

    
