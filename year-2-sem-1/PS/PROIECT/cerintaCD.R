frepcomgencomp <- function(m, n) {
  #cream o matrice cu 0
  rep <- matrix(data = 0,
                nrow = n+2,
                ncol = m+2)
  
  #generam valorile lui x
  x <- sample(-100:100, n)
  x <- sort(x)
  rep[,1] <- c(NA, x, NA)
  
  #generam valorile lui y
  y <- sample(-100:100, m)
  y <- sort(y)
  rep[1,] <- c(NA, y, NA)
  
  rep[n+2,m+2] <- 1
  
  #generam probabilitatile repartitiei comune
  for(i in 2:(n)) {
    for(j in 2:(m)) {
      #generam o valoare
      val <- round(runif(1, 0.000, round(1 - sum(rep[2:(n+1),2:(m+1)]),3)),2)
      rep[i,j] <- val
    }
  }
  #completam celula lipsa
  rep[n+1, m+1] <- 1 - sum(rep[2:(n+1),2:(m+1)])
  
  for(i in 2:(n+1)) {
    rep[i,m+2] <- sum(rep[i,-1, drop = FALSE])
  }
  
  for(i in 2:(m+1)) {
    rep[n+2, i] <- sum(rep[-1,i, drop = FALSE])
  }
  
  rep
}

solverep <- function(m,n,repartitie) {
  
  #gasim celulele goale si salvam coordonatele
  df <- data.frame(i=NULL,j=NULL)
  for (i in 2:(n+2)){
    for (j in 2:(m+2)){
      if (is.na(repartitie[i,j])) {
        a <- data.frame(i,j)
        names(a) <- c("i", "j")
        df <- rbind(df, a)
      } 
    }
  }
  
  #preluam indicii de linie si de coloana unici (pe aceste linii si coloane sunt celule goale => trebuie rezolvate)
  linii <- unique(df$i)
  coloane <- unique(df$j)
  
  #cream matricea de coeficienti (fiecare coloana o necunoscuta) si vectorul cu rezultate (pentru fiecare ecuatie)
  ma <- matrix(data = 0, ncol = length(df$i))
  rez <- c(0)
  
  #luam fiecare linie cu celule goale si completam matricea de coeficienti si vectorul de rezultate
  for(i in 1:length(linii)) {
    
    indice <- linii[i]
    
    if(i > 1) {
      ma <- rbind(ma, rep(0,length(df$i)))
      rez <- c(rez, 0)
    }
    
    
    for(j in 2:(m+2)) {
      if(is.na(repartitie[indice,j]) == T) {
        nec <- which(df$i == indice & df$j == j)
        if(j == m+2)
          ma[nrow(ma),nec] <- -1
        else
          ma[nrow(ma),nec] <- 1
      } else {
        if(j == m+2)
          rez[length(rez)] <- rez[length(rez)] + repartitie[indice, j]
        else
          rez[length(rez)] <- rez[length(rez)] - repartitie[indice, j]
      }
    }
  }
  
  #luam fiecare coloana cu celule goale si completam matricea de coeficienti si vectorul de rezultate
  for(j in 1:length(coloane)) {
    indice <- coloane[j]
    ma <- rbind(ma, rep(0,length(df$j)))
    rez <- c(rez, 0)
    
    for(i in 2:(n+2)) {
      if(is.na(repartitie[i,indice]) == T) {
        nec <- which(df$i == i & df$j == indice)
        if(i == n+2) {
          ma[nrow(ma),nec] <- -1
        }
        else {
          ma[nrow(ma),nec] <- 1
        }
      } else {
        if(i == n+2)
          rez[length(rez)] <- rez[length(rez)] + repartitie[i, indice]
        else
          rez[length(rez)] <- rez[length(rez)] - repartitie[i, indice]
      }
    }
  }
  # print("solve\n")
  # print(repartitie)
  # print(ma)
  # print("rez\n")
  # print(rez)
  
  #incercam sa rezolvam sistemul de ecuatii
  #daca nu se poate, nu avem solutie unica, altfel am gasit solutia
  solution <- numeric()
  tryCatch(solution <- qr.solve(ma,rez),
           
           error = function(e){
             solution <- numeric()
           }, silent = T)
  solution
}

frepcomgen <- function(m,n) {
  
  #generam o repartitie completa
  repartitie <- frepcomgencomp(m, n)
  
  print(repartitie)
  
  nr_nec <- 0
  
  vis <- matrix(data = 0, nrow = n+2, ncol = m+2)
  
  while(length(which(vis == 0)) - m - n - 4> 0) {
    
    #alegem aleator o pozitie din repartitie
    x <- sample(2:(n+2), 1)
    if(x == n+2) {
      y <- sample(2:(m+1), 1)
    } else {
      y <- sample(2:(m+2), 1)
    }
    vis[x, y] <- 1
    
    #retinem si stergem valoarea
    val <- repartitie[x,y]
    repartitie[x,y] <- NA
    
    #incercam sa completam repartitia
    solution <- round(solverep(m,n,repartitie),2)
    
    #daca nu am reusit, punem valoarea extrasa inapoi
    if(length(solution) == 0 | length(solution[solution < 0]) > 0) {
      repartitie[x, y] <- val
    }
    else {
      
      nr_nec <- nr_nec + 1
    }
  }
  # print("solutie: ")
  # print(solution)
  repartitie
  
}

fcomplrepcom <- function(m, n, repartitie) {
  solution <- solverep(m, n, repartitie) 
  
  df <- data.frame(i=NULL,j=NULL)
  for (i in 2:(n+2)){
    for (j in 2:(m+2)){
      if (is.na(repartitie[i,j])) {
        a <- data.frame(i,j)
        names(a) <- c("i", "j")
        df <- rbind(df, a)
      } 
    }
  }
  
  for(indice in 1:length(df$i)) {
    repartitie[df$i[indice], df$j[indice]] <- round(solution[indice],2)
  }
  
  # print(repartitie)
  repartitie
  
}

m <- 4
n <- 4

grid <- frepcomgen(m,n)
grid

rs <- fcomplrepcom(m, n, grid)
rs


###########################################################################################################################
###########################################################################################################################


# cerinta c
# Construiți o funcție frepmarginal care construiește repartițiile marginale 
# pentru X și Y pornind de la repartiția lor comună.

frepmarginal <- function(rep_comuna) {
  # nr col/rand pentru repartitia marginala
  nr_col = ncol(rep_comuna) - 1  
  nr_rand = nrow(rep_comuna) - 1  

  # initializare cu 0
  mY <- matrix(0, nrow = 2, ncol = nr_col - 1)
  mX <- matrix(0, nrow = 2, ncol = nr_col - 1)
  
  # variabila Y
  mY[1,] <- rep_comuna[1, 2:nr_col]
  mY[2,] <- rep_comuna[nr_rand+1, 2:nr_col]
  
  # variabila X
  mX[1,] <- rep_comuna[2:nr_rand, 1]
  mX[2,] <- rep_comuna[2:nr_rand, nr_col+1]
  
  # returnez o lista cu 2 repartitii (matrici)
  result <- list(mX = mX, mY = mY)
  
  return(result)
}

# stocarea repartitiilor in rezultat
rezultat <- frepmarginal(rs)

# acces repartitii din lista rezultatelor
repX <- rezultat$mX
repY <- rezultat$mY

repX
repY

#calculul Mediei unei variabile
frepMed <- function(rep) {
  medie <- apply(rep, MARGIN = 2, FUN = prod)
  return(sum(medie))
}

# calcul patratului unei variabile
frepSquare <- function(rep) {
  # pentru X^2
  repSq <- rep
  repSq[1,] <- rep[1,]^2
  return(repSq)
}

# multiplicarea variabilelor
frepMultiply <- function(repX, repY, repComun) {
  # initializare matrice
  repMult <- matrix(data = 0, nrow = 2 ,ncol = ncol(repX) * ncol(repY))
  indexRep <- 1
  # fiecare element din rep X
  for (i in 1:ncol(repX)) {
    # fiecare elem din rep Y
    for (j in 1:ncol(repY)) {
      # stocam in matricea rezultat
      repMult[1, indexRep] <- repX[1,i] * repY[1,j]
      repMult[2, indexRep] <- repComun[j + 1, i + 1]

      # cat("repMult[1, ", indexRep, "]:", repMult[1, indexRep], "\n")
      # cat("repMult[2, ", indexRep, "]:", repMult[2, indexRep], "\n")
      
      indexRep <- indexRep + 1
    }
  }
  return(repMult)
}


repMultXY <- frepMultiply(repX, repY, rs)
repMultXY
# varianta pentru o variab
frepVar <- function(repX) {
  var <- frepMed(frepSquare(repX)) - frepMed(repX)^2
  
  return(var)
}

varianta <- frepVar(repX)
varianta

# Intr-un sfarsit calculul covariantei cu proprietatile:
# Cov(aX + bY, cX + dY) = a*c* Var(X) + (a*d + b*c)*Cov(X,Y) + b*d * Var(Y)
# Cov(X, Y) = E(X * Y) - E(X) * E(Y)

fcov <- function (repX, repY, rs) {
  cov <- frepMed(frepMultiply(repX, repY, rs)) - frepMed(repX) * frepMed(repY)
  return (cov)
}

cov <- fcov(repX, repY, rs)
cov

fpropcov <- function(a, b, repX, c, d, repY, rs) {
  propCov <- a * c * frepVar(repX) + (a * d + b * c) * fcov(repX, repY, rs) + b * d * frepVar(repY)
  return(propCov)
}

propCov <- fpropcov(1, 1, repX, 1, 1, repY, rs)
propCov

# fct pentru corelatie
fvernecor <- function(repX, repY, rs) {
  pearson <- fcov(repX, repY, rs) / sqrt(frepVar(repX) * frepVar(repY)) # trebuie de verificat sa nu fie 0 (s-a intamplat sa dea 0) 
  
  if (pearson == 0) {
    print("Variabile necorelate!")
  } else if (abs(pearson) <= 0.25) {
    print("Variabile slab corelate!")
  } else if (abs(pearson) <= 0.75) {
    print("Variabile corelate!")
  } else {
    print("Variabile puternic corelate")
  }
  
  return (pearson)
}

pearson <- fvernecor(repX, repY, rs)
pearson

# punctul g, calculare Cov
# cov(aX, bY) = a * b * cov(X, Y)
# cov(X + a, Y + b) = cov(X, Y)
# In concluzie avem: cov(aX + b, cY + d) = a * c * cov(X, Y)
# PS: sper ca e corect

frezolvaG <- function(repX, repY, rs, a, c) { # nu cred ca are rost sa dau b, d daca nu-i folosesc
  return (a * c * fcov(repX, repY, rs))
}

raspunsGcov <- frezolvaG(repX, repY, rs, 5, -3)
raspunsGcov



########################################################################################################################
########################################################################################################################



#e)
fPcond <- function(repartitie, xInfEg = NA, xInfSt = NA, xEg = NA, xSupEg = NA, xSupSt = NA, 
                   yInfEg = NA, yInfSt = NA, yEg = NA, ySupEg = NA, ySupSt = NA) {
  #dimensiunile m, n
  m <- ncol(repartitie) - 2
  n <- nrow(repartitie) - 2
  
  #verificam datele furnizate
  if(length(which(!is.na(c(xInfEg, xInfSt, xEg)))) > 1 | length(which(!is.na(c(xSupEg, xSupSt, xEg)))) > 1 | 
     length(which(!is.na(c(yInfEg, yInfSt, yEg)))) > 1 | length(which(!is.na(c(ySupEg, ySupSt, yEg)))) > 1 |
     all(is.na(c(xInfEg, xInfSt, xEg, xSupEg, xSupSt))) | 
     all(is.na(c(yInfEg, yInfSt, yEg, ySupEg, ySupSt)))) {
    return("Datele furnizate nu sunt corecte")
  }
  
  #identificam indicii pentru valorile lui X
  
  #limita inferioara
  xi <- numeric()
  
  if(!is.na(xInfEg)) {
    xi <- which(repartitie[,1] >= xInfEg)
  }
  else if(!is.na(xInfSt)) {
    xi <- which(repartitie[,1] > xInfSt)
  }
  else if(!is.na(xEg)) {
    xi <- which(repartitie[,1] == xEg)
  }
  #n-am niciun parametru pentru limita inferioara
  else {
    xi <- 2:(n+1)
  }
  
  #este setat un parametru, dar nu s-a gasit nicio valoare care sa respecte conditia
  if(length(xi) == 0) return(0)
  
  #limita superioara
  xs <- numeric()
  
  if(!is.na(xSupEg)) {
    xs <- which(repartitie[,1] <= xSupEg)
  }
  else if(!is.na(xSupSt)) {
    xs <- which(repartitie[,1] < xSupSt)
  }
  else if(!is.na(xEg)) {
    xs <- which(repartitie[,1] == xEg)
  }
  #n-am niciun parametru pentru limita superioara
  else {
    xs <- 2:(n+1)
  }
  
  #este setat un parametru, dar nu s-a gasit nicio valoare care sa respecte conditia
  if(length(xs) == 0) return(0)
  
  #pozitiile corespunzatoare valorilor cerute ale lui Y
  x <- intersect(xi, xs)
  
  #identificam indicii pentru valorile lui Y
  
  #limita inferioara
  yi <- numeric()
  
  if(!is.na(yInfEg)) {
    yi <- which(repartitie[1,] >= yInfEg)
  }
  else if(!is.na(yInfSt)) {
    yi <- which(repartitie[1,] > yInfSt)
  }
  else if(!is.na(yEg)) {
    yi <- which(repartitie[1,] == yEg)
  }
  #n-am niciun parametru pentru limita inferioara
  else {
    yi <- 2:(m+1)
  }
  
  #este setat un parametru, dar nu s-a gasit nicio valoare care sa respecte conditia => P = 0
  if(length(yi) == 0) return(0)
  
  #limita superioara
  ys <- numeric()
  
  if(!is.na(ySupEg)) {
    ys <- which(repartitie[1,] <= ySupEg)
  }
  else if(!is.na(ySupSt)) {
    ys <- which(repartitie[1,] < ySupSt)
  }
  else if(!is.na(yEg)) {
    ys <- which(repartitie[1,] == yEg)
  }
  #n-am niciun parametru pentru limita superioara
  else {
    ys <- 2:(m+1)
  }
  
  #este setat un parametru, dar nu s-a gasit nicio valoare care sa respecte conditia => P = 0
  if(length(ys) == 0) return(0)
  
  #pozitiile corespunzatoare valorilor cerute ale lui Y
  y <- intersect(yi, ys)
  
  #daca nu se gasesc valori, probabilitatea este 0
  if(length(y) == 0) return(0)
  
  #probabilitatea ca Y sa aiba valorile cerute
  py <- sum(repartitie[n+2, y])
  
  #probabilitatea ca X si Y sa aiba simultan valorile cerute
  pxy <- sum(repartitie[x, y])
  
  #suma probabilitatilor pentru valorile cerute ale lui X si Y
  xcondy <- pxy/py
  
  xcondy
}

#fPcond(rs, xInfEg = -65, yInfEg=-66)

#f)
fPcomun <- function(repartitie, xInfEg = NA, xInfSt = NA, xEg = NA, xSupEg = NA, xSupSt = NA, 
                    yInfEg = NA, yInfSt = NA, yEg = NA, ySupEg = NA, ySupSt = NA) {
  
  #dimensiunile m si n
  m <- ncol(repartitie) - 2
  n <- nrow(repartitie) - 2
  #verificam datele furnizate
  if(length(which(!is.na(c(xInfEg, xInfSt, xEg)))) > 1 | length(which(!is.na(c(xSupEg, xSupSt, xEg)))) > 1 | 
     length(which(!is.na(c(yInfEg, yInfSt, yEg)))) > 1 | length(which(!is.na(c(ySupEg, ySupSt, yEg)))) > 1 |
     all(is.na(c(xInfEg, xInfSt, xEg, xSupEg, xSupSt))) | 
     all(is.na(c(yInfEg, yInfSt, yEg, ySupEg, ySupSt)))) {
    return("Datele furnizate nu sunt corecte")
  }
  
  #identificam indicii pentru valorile lui X
  
  #limita inferioara
  xi <- numeric()
  
  if(!is.na(xInfEg)) {
    xi <- which(repartitie[,1] >= xInfEg)
  }
  else if(!is.na(xInfSt)) {
    xi <- which(repartitie[,1] > xInfSt)
  }
  else if(!is.na(xEg)) {
    xi <- which(repartitie[,1] == xEg)
  }
  #n-am niciun parametru pentru limita inferioara
  else {
    xi <- 2:(n+1)
  }
  
  #este setat un parametru, dar nu s-a gasit nicio valoare care sa respecte conditia
  if(length(xi) == 0) return(0)
  
  #limita superioara
  xs <- numeric()
  
  if(!is.na(xSupEg)) {
    xs <- which(repartitie[,1] <= xSupEg)
  }
  else if(!is.na(xSupSt)) {
    xs <- which(repartitie[,1] < xSupSt)
  }
  else if(!is.na(xEg)) {
    xs <- which(repartitie[,1] == xEg)
  }
  #n-am niciun parametru pentru limita superioara
  else {
    xs <- 2:(n+1)
  }
  
  #este setat un parametru, dar nu s-a gasit nicio valoare care sa respecte conditia
  if(length(xs) == 0) return(0)
  
  #pozitiile corespunzatoare valorilor cerute ale lui Y
  x <- intersect(xi, xs)
  
  #identificam indicii pentru valorile lui Y
  
  #limita inferioara
  yi <- numeric()
  
  if(!is.na(yInfEg)) {
    yi <- which(repartitie[1,] >= yInfEg)
  }
  else if(!is.na(yInfSt)) {
    yi <- which(repartitie[1,] > yInfSt)
  }
  else if(!is.na(yEg)) {
    yi <- which(repartitie[1,] == yEg)
  }
  #n-am niciun parametru pentru limita inferioara
  else {
    yi <- 2:(m+1)
  }
  
  #este setat un parametru, dar nu s-a gasit nicio valoare care sa respecte conditia => P = 0
  if(length(yi) == 0) return(0)
  
  #limita superioara
  ys <- numeric()
  
  if(!is.na(ySupEg)) {
    ys <- which(repartitie[1,] <= ySupEg)
  }
  else if(!is.na(ySupSt)) {
    ys <- which(repartitie[1,] < ySupSt)
  }
  else if(!is.na(yEg)) {
    ys <- which(repartitie[1,] == yEg)
  }
  #n-am niciun parametru pentru limita superioara
  else {
    ys <- 2:(m+1)
  }
  
  #este setat un parametru, dar nu s-a gasit nicio valoare care sa respecte conditia => P = 0
  if(length(ys) == 0) return(0)
  
  #pozitiile corespunzatoare valorilor cerute ale lui Y
  y <- intersect(yi, ys)
  
  
  #suma probabilitatilor pentru valorile cerute ale lui X si Y
  pr <- sum(repartitie[x, y])
  
  pr
  
}

#fPcomun(rs, xInfEg = -65, xSupSt = 50, yInfSt = -54)

#g)

#P(0<X<0.8|Y>0.3)
fPcond(rs, xInfSt = 0, xSupSt = 0.8, yInfSt = 0.3)

#P(X>0.2,Y<1.7)
fPcomun(rs, xInfSt = 0.2, ySupSt = 1.7)

#h)
fverind <- function(repartitie) {
  
  #dimensiunile m si n
  m <- ncol(repartitie) - 2
  n <- nrow(repartitie) - 2
  
  #probabilitatile din repartitia marginala a lui X
  x <- repartitie[n+2, 2:(m+1)]
  
  #pentru fiecare linie din repartitia comuna, se verifica daca rezulta din inmultirea
  #probabilitatilor marginale ale lui X cu probabilitatea marginala a lui Y de pe linia curenta
  for(i in 2:(n+1)) {
    linie <- repartitie[i, 2:(m+1)]
    xy <- x * repartitie[i, m+2]
    
    #daca exista un rezultat care nu corespunde, variabilele nu sunt independente
    if(any(xy != linie))
      return(FALSE)
  }
  
  return(TRUE)
}

fverind(rs)
