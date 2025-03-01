def LS(wierz, kraw):
    lista_sas = [[] for i in range(wierz)]
    for i in range(kraw):
        wierz_1, wierz_2 = map(int, input().split())
        lista_sas[wierz_1].append(wierz_2)
        lista_sas[wierz_2].append(wierz_1)
    for i in range(wierz):
        print(lista_sas[i])
        

l_wierz, l_kraw = map(int, input().split())
LS(l_wierz, l_kraw)

    
