install.packages("Ryacas")

library(Ryacas)
library(mosaic)

# pentru testare globala
fun_str <- "(3/2)*x*y^2"
# valori intervale (a,b)
values_x <- c(0, 2)
values_y <- c(0, 1)


# definesc functia f(x)
InnerFun <- function(x, y) 
{
  result <- ifelse((x >= values_x[1]) & (y >= values_y[1]) & (x <= values_x[2]) & (y <= values_y[2]), eval(parse(text = tolower(fun_str))), 0)
  return (result)
}  
f <- InnerFun(1, 1)
f
# Idee: inegrala dubla, 2 apeluri integrate

# integrez in raport cu x
integrala_dublaX <- function (fun, values_x, values_y, fun_str)
{
  integrate( 
    # vectorize pentru integrarea lui x in raport cu un vector de valori ale lui y
    Vectorize(    
        function(y)
          {
            integrate(function(x) { fun(x, y) }, values_x[1], values_x[2]) $ value   # daca integrez mai intai x
          }
      ), 
    values_y[1], values_y[2]) $ value
}

i_defx <- integrala_dublaX(InnerFun, values_x, values_y, fun_str)
i_defx


# integrez in raport cu y
integrala_dublaY <- function (fun, values_x, values_y, fun_str)
{
  integrate( 
    # vectorize pentru integrarea lui x in raport cu un vector de valori ale lui y
    Vectorize(    
      function(x)
      {
        integrate(function(y) { fun(x, y)  }, values_x[1], values_x[2]) $ value   # daca integrez mai intai x
      }
    ), 
    values_y[1], values_y[2]) $ value
}
i_defy <- integrala_dublaY(InnerFun, values_y, values_x, fun_str)
# rezultat asteptat: 
i_defy


# Fubini - dc cele 2 integrale sunt egale
fubini <- function (rez1, rez2)
{
  return (rez1 == rez2)
}  

verific_thm_Fubini <- fubini(i_defx, i_defy)
verific_thm_Fubini

# interpretarea geometrica a integralei duble,
# folosim outer pentru a aplica functia pe fiecare val x,y
# cerinta: facem functia introdusa de utilizator - GLOBALA
z <- outer(values_x, values_y, InnerFun)

# persp ne permite vizualizarea 3D 
persp(values_x, values_y, z, col = "lightblue", border = NA)


is_positive_2d <- function(fun) {
  x_range <- c(-1000, 1000)
  y_range <- c(-1000, 1000)
  len <- 1000
  # instantiez o structura de date comoda 
  data <- data.frame(x =  seq(x_range[1], x_range[2], length.out = len),
                     y = seq(y_range[1], y_range[2], length.out = len))
 
  # aplic functia pentru fiecare elem
  # verific dc toate elementele sunt pozitive
  return(all(mapply(fun, data$x, data$y) >= 0))
}

rasp <- is_positive_2d(InnerFun)
rasp

# verificare daca o functie este pozitiva si integrala_dubla(f) = 1
este_densitate <- function (fun, values_y, values_x)
{
  return (is_positive_2d(fun) && integrala_dublaX(fun, values_x, values_y, fun_str) == 1)
}

e_dens <- este_densitate( InnerFun, values_y, values_x)
e_dens


######################################
      ##### USER INPUT #####

fcitescDensBidim <- function () {
  dens <- readline("Functie densitate: ")
  fun_str <- dens
  print(fun_str)
  cat("Interval x -> (a, b): ")
  interval1 <- c(as.numeric(readline("a= ")), as.numeric(readline("b= ")))
  
  cat("Interval y -> (c, d): ")
  interval2 <- c(as.numeric(readline("c= ")), as.numeric(readline("d= ")))
  
  e_densitate <- este_densitate( InnerFun, interval2, interval1)
  
  if (e_densitate) {
    cat("Este densitate!")
    return(list(fun_str = fun_str, interval1 = interval1, interval2 = interval2))
  } else {
    cat("Nu este densitate!")
    return (0)
  }
}


#############################
##### Unidimensionala #######
expr_unidim <- "3*x^2"
interval <- c(0, 1)

InnerFunUni <- function(x, interval = interval, exp = expr_unidim) {
  res <- ifelse((x >= interval[1]) & (x <= interval[2]), eval(parse(text = tolower(exp))), 0) 
  return(res)
}

fun_unidim <- InnerFunUni(4, interval, expr_unidim)
fun_unidim
 

fpositiveUni <- function(fun, exp) {
  x_range <- c(-1000, 1000)
  len <- 1000
  # instantiez o structura de date comoda 
  data <- seq(x_range[1], x_range[2], length.out = len)
  
  # aplic functia pentru fiecare elem
  # verific dc toate elementele sunt pozitive
  # all(fun(x_values) >= 0)
  print(all(InnerFunUni(data,interval, exp) >= 0))
  return(all(InnerFunUni(data,interval, exp) >= 0))
}

e_pozitiva <- fpositiveUni(InnerFunUni, expr_unidim)
e_pozitiva

# calculez integrala pentru unidimensionala
fIntegralaUni <- function(interval, exp) {
  integralaX <- integrate(function(x) {InnerFunUni(x, interval, exp)}, lower = interval[1], upper = interval[2]) $ value
  
  return(integralaX)
}

val_integ <- fIntegralaUni(interval, expr_unidim)
val_integ

eDensitateUni <- function(exp, interval, fun) {
  return (e_pozitiva && (fIntegralaUni(interval, exp) == 1))
}

e_dens_unidim <- eDensitateUni(expr_unidim, interval, InnerFunUni)
e_dens_unidim


fcitescDensUni <- function() {
  dens <- readline("Functie densitate: ")
  fun_str <- dens
  print(fun_str)
  
  cat("Interval x -> (a, b): ")
  interval1 <- c(as.numeric(readline("a= ")), as.numeric(readline("b= ")))
  
  # validitate densitate
  e_densitate <- eDensitateUni(fun_str, interval1, InnerFunUni)
  
  if (e_densitate) {
    cat("Este densitate!")
    return(list(fun_str = fun_str, interval1 = interval1))
  } else {
    cat("Nu este densitate!")
    return(0)
  }
}

lista_val <- fcitescDensUni()


##### Unidimensionala #######
#############################



# verifica input: (3/2)*x*y^2
if (fcitescDensBidim() != 0) {
  densitate_citita <- fcitescDensBidim()
  
  # update valoare fun_str global, values_x, values_y
  fun_str <- densitate_citita$fun_str
  values_x <- densitate_citita$interval1
  values_y <- densitate_citita$interval2
}

# creare obiect variabila aleatoare continua, universala p/u bidimensionale si unidimensionale

# creare instanta
setClass("Variabila_Aleatoare_Continua_Bidi", 
         slots = list(
           fdensitate = "character", 
           values_x = "numeric",
           values_y = "numeric"
         ))

setClass("Variabila_Aleatoare_Continua_Uni", 
         slots = list(
           fdensitate = "character", 
           values_x = "numeric"
         ))

creaza_variabila <- function()
{
  user_input_tip <- readline("Tip variabila:  0 - Unidimensionala | 1 - Bidimensionala: ")
  bidimensionala <- as.numeric(user_input_tip)
  

  # verifica dc conversia s-a facut si am tipul numeric
  if (!is.na(bidimensionala) && identical(bidimensionala, 1)) {
      
      densitate_citita <- fcitescDensBidim()
      
      var_bidim_obj <- new("Variabila_Aleatoare_Continua_Bidi", 
                           fdensitate = densitate_citita$fun_str,
                           values_x = densitate_citita$interval1,
                           values_y = densitate_citita$interval2
                           )
      # returnez obj dupa initializare
      return(var_bidim_obj)
  } else {
    densitate_citita <- fcitescDensUni()
    
    var_unidim_obj <- new("Variabila_Aleatoare_Continua_Uni", 
                         fdensitate = densitate_citita$fun_str,
                         values_x = densitate_citita$interval1
    )
    # returnez obj dupa initializare
    return(var_unidim_obj)
  }
}

# ruleaza comenzile pe rand, mai intai citeste
obj <- creaza_variabila()
# apoi vizualizare
obj

  

####### MARGINALE
fun_str <- "(3/2)*x*y^2"
fx <- function() {
  yac_str(sprintf("Integrate(y,%s,%s) %s" , values_y[1], values_y[2], fun_str))
}
fy <- function() {
  yac_str(sprintf("Integrate(x,%s,%s) %s" , values_x[1], values_x[2], fun_str))
}

fun_x <- fx()
fun_y <- fy()

############

####### CONDITIONATE  ####### 

dens_fx <- function() 
{
  dens_fx <- yac_str(sprintf("(%s) / (%s)", fun_str, fun_y))
  # pentru solutie: initializam x, y:sol <- eval(parse(text=dens_fx))
  return(dens_fx)
}
dens_fx <- dens_fx()

dens_fy <- function() 
{
  dens_fy <- yac_str(sprintf("(%s) / (%s)", fun_str, fun_x))
  return(dens_fy)
}
dens_fy <- dens_fy()
########################## 

######### INTEGRALE NEDEFINITE 

#lucreaza pe variabile globale
x <- c(0,1, 2)
#y <- c(0,1, 2)

fun_x <- yac_str("Integrate(x) y/Sqrt(x)")
fun_y <- yac_str(paste("Integrate(y) " , fun_x))

fun_parse <- str2lang(tolower(fun_x))

my_f <- eval(fun_parse)
my_f

# intoarce o noua functie g(y) definita
# ca f(x, y), unde x este o valoare fixata
f_set_x <- function(x, f) function(y) f(x, y)

rez <- InnerFunExp(x, y, fun_x)
print(eval(f(1,2)))


library(rlang)

# Define the symbolic variables
x <- sym("x")
y <- sym("y")

# Define the expression
expn <- expression(y / sqrt(x))

# Substitute x = 4 into the expression
require(graphics)
result.s.e <-eval(substitute(expression(str2lang(tolower(fun_str))), list(x = 4))) 
result.s
# Print the result
print(result)

fun_x <- yac_str(sprintf("Integrate(y,%s,%s) %s" , values_y[1], values_y[2], fun_str))
fun_y <- yac_str(sprintf("Integrate(x,%s,%s) %s" , values_x[1], values_x[2], fun_str))



# Suppose you have a non-vectorized function
vectorized_function <- function(x) {
  return(x^2)
}

# Use Vectorize to create a vectorized version
vectorized_function <- Vectorize(non_vectorized_function)
nonv <- vectorized_function(c(1, 2, 3, 4, 5))
# Now you can use vectorized_function with a vector
result <- vectorized_function(c(1, 2, 3, 4, 5))

# 'result' is now a vector containing the squared values
print(result)