# Construiti doi vectori x si y cu 1000 de elemente fiecare, extrase in mod
#aleator din multimea cu numere intregi -24500:76000.
#a)Stabiliti care dintre cei doi vectori are mai multe elemente,
#luate in valoare absoluta, mai mari decat valoarea absoluta a elementului
#corespondent din celalalt vector

x <- sample(-24500:76000, size = 1000)
y <- sample(-24500:76000, size = 1000)
abs(x)
xMy[abs(x) < abs(y)]
length(xMy[xMy == TRUE])  # 498
length(xMy[xMy == FALSE])  # 502

#b)Stabiliti care dintre cei doi vectori are minimul pe o pozitie mai mare
which.min(y)  # 412
which.min(x)  # 93
which.min(y) > which.min(x)

#c)Stabiliti care dintre cei doi vectori are cele mai multe valori care se repeta
print("Count of repeated values") 
length(which(table(y)>1))     # da 0 mereu

l1 <- diff(x)
l1
length(l1[l1 == -1])   # 0

l2 <- diff(y)
l2
length(l2[l2 == -1])  # 0

#e)Stabiliti care dintre cei doi vectori are mai multe valori divizibile cu corespondentele
#lor din celalalt vector
modulo1 <- x %% y
length(modulo1[modulo1 == 0])

modulo2 <- y %% x
length(modulo2[modulo2 == 0])

help(which)

#Q: Creati un vector logic t ce compara daca elementul de pe pozitia i(impara) 
# este mai mic decat elementul de pe pozitia para imediat urmatoare

vec <- c(1, 2, 3,4,5, 6)
v <- vec[c(FALSE, TRUE)]
v1 <- vec[c(TRUE, FALSE)]
print(v)
print(v1)
v1 < v

#Q: Determinati pozitiile pentru care conditia de la prima intrebare este adevarata
#HINT: which()
which(v1 < v)

#Q: Determinati cate numere cuprinse intre 411 si 7870 sunt divizibile cu 9
#dar nu cu 5
diviz1 <- c(411:7870)
diviz1
length(which((diviz1 %% 9 == 0) & (diviz1 %% 5 != 0)))  # 664 elem




