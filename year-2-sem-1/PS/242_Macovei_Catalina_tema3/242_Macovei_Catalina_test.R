

# schema binomiala pe n1 si n2

comb = function(n, x) {
  factorial(n) / factorial(n-x) / factorial(x)
}

binomiala_2_cazuri <- function(n, n1, n2, p, q) {
  return (comb(n, n1) * p ^ n1 * q ^ n2)
}

# utilizare binomiala pe n1 si n2

n<-3      # nr total
n1<-1     # optiunea dorita
n2<-2     # cealalta aptiune
p<-0.5    # probabilitate succes
q<-0.5    # probabilitate esec
prob <- binomiala_2_cazuri(n, n1, n2, p, q)
print(prob)


multinomial_coef <- function(n, vec) {
  numarator <- factorial(n)
  
  numitor <- prod(sapply(vec, factorial))
  
  multinomial_coefficient <- numarator / numitor
  
  return(multinomial_coefficient)
}

prod_puteri_p <- function(p, n) {
  if(length(p) != length(n)) {
    stop("Vectorii trebuie sa aiba aceeasi lungime!")
  }
  
  result <- 1
  for(i in 1:length(p)) {
    result <- result * p[i]^n[i]
  }
  
  return(result)
}

# Schema binomiala pentru n1..nk:
binomiala_generala <- function(n_tot, n1_nk_vector, p1_pk_vector) {
  
  return (multinomial_coef(n_tot, n1_nk_vector) * prod_puteri_p(p1_pk_vector, n1_nk_vector))
}

# Utilizare binomiala pentru n1..nk: 
n_tot<-5
n1_nk_vector<-c(1, 2, 2)
p1_pk_vector<-c(0.6, 0.2, 0.2)

expr <- binomiala_generala(n_tot, n1_nk_vector, p1_pk_vector)
print(expr)

############################################
# ex 2
# Voi adapta la Schema lui Pascal
# valorile le-am luat din rezolvarea problemei pe foaie

pascal <- function (p, q, k) {
  return (p * q ^ (k - 1))
}

# Utilizare:
p <- 0.187
q <- 0.813
k <- 4

#o utilizare
prob <- pascal(p, q, k)
print(prob)

# nr exp
num_exp <- 1e6

# vector de rezulatte
results <- numeric(num_exp)

# rulez de 10^6 ori
for (i in 1:num_exp) {
  results[i] <- pascal(p, q, k)
}

# Printez primele rezultate:
print(head(results))



#############################
# Rezolvare ex 8 
# Schema cu bila nerevenita - HIPERGEOMETRICA - programul general, rezolvarea problemei este sub conditie
hipergeometrica <- function (N_vec, n_vec, n_tot, N_tot) {
  res <- 1
  for(i in 1:length(n_vec)) {
    res <- comb(N_vec[i], n_vec[i])
  }
  return (res / comb(N_tot, n_tot))
}

# Utilizare :
N_vec <- c(1, 2, 3, 4)
n_vec <- c(1, 1, 2, 3)
n_tot <- 4  # 4 soareci
N_tot <- 10
p <- hipergeometrica(N_vec, n_vec, n_tot, N_tot)
print(p)

# 4 soareci sunt scosi la intamplare dintr-o cutie care exista exact 2 soareci albi. 
# Probabilitatea ca ambii sa fie alesi e de 2 ori mai mare decat prob ca niciunul dintre soarecii albi sa fie ales... 
#Determinati nr de soareci din cutie

# rezolvare problema:

hipergeometrica <- function(N_vec, n_vec, n_tot, N_tot) {
  res <- 1
  for (i in 1:length(n_vec)) {
    res <- res * choose(N_vec[i], n_vec[i])
  }
  return (res / choose(N_tot, n_tot))
}

gaseste_N_tot <- function(N_alb, N_negru, n_alb, n_negru) {
  for (N_total in 1:100) {  # presupun nr soareci
    p_ambii_albi <- hipergeometrica(c(N_alb, N_negru), c(n_alb, n_negru), n_alb, N_total)
    p_niciun_alb <- hipergeometrica(c(N_alb, N_negru), c(0, n_negru), n_alb, N_total)
    
    if (p_ambii_albi == 2 * p_niciun_alb) {
      return(N_total)
    }
  }
  
  return(NULL)  # daca nu gasesc solutie
}

# Utilizare:
N_alb <- 2
N_negru <- 2
n_alb <- 2
n_negru <- 2

N_total_gasit <- gaseste_N_tot(N_alb, N_negru, n_alb, n_negru)
print(N_total_gasit)

#####################################################
# Ex 15 
# Problema: generati in R 10^6 valori dintr-o repartitie poisson(5), apoi din vectorul obtinut scadeti 5 si inmultiti cu 2*10^5. 
# Faceti o histograma a valorilor transformate. C erapartitie puteti asocia pentru acestea?

# Schema lui Poisson


# Generare valori dintr-o repart Poisson(5)
set.seed(42)  # valori aleatoare
valori_poisson <- rpois(1e6, lambda = 5)

# scad 5 inmult cu 2 * 10^5
valori_transformate <- (valori_poisson - 5) * 2e5

# histohgrama:
hist(valori_transformate, main = "Histograma Valorilor Transformate", xlab = "Valori Transformate")

# pot asocia o repartitie normala

#########################

