# PROBLEMA: Avem n elemente intr-o multime. Pentru n fixat, generati tpate sigma algebrele. Cel putin pentru n = 4.


# am instalat pachetul combinat, pentru ca voi folosi functia combn(), pentru a genera toate combinarile de elemente
if (!requireNamespace("combinat", quietly = TRUE)) {
  install.packages("combinat")
}

library(combinat)

generare_sigma_algebre <- function() {
  multime <- c("a", "b", "c", "d")
  n <- length(multime)
  sigma_algebre <- list()
  
  # Generati toate submultimile multimii
  for (k in 0:n) {
    submultimi <- combinat::combn(multime, k, simplify = FALSE)
    sigma_algebre <- c(sigma_algebre, submultimi)
  }
  
  return(sigma_algebre)
}

multVida <- list("mVida")
# Apelati functia pentru a genera sigma algebrele
rezultat <- generare_sigma_algebre()
rezultat2 <- append(multVida, rezultat)

# AfisaRE sigma algebre
cat("Sigma algebră: ")
for (i in 1:length(rezultat2)) {
  cat( i, ": ", unlist(rezultat2[[i]]), "\n")
}
