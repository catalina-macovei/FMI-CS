rnorm(25);

# sintaxa: matrix(data, nrow, ncol)
random_matrix <- matrix(0, nrow = 4, ncol = 5) # creez matricea random
for (i in 1:nrow(random_matrix)) {
  for (j in 1:ncol(random_matrix)) {
    random_matrix[i, j] <- 0
  }
}
random_matrix

# creare matrice X var
X <- c(1, 2)
random_vector <- runif(length(X))
X_matrix <- matrix(c(c(1, 2), random_vector / sum(random_vector)), ncol = 2)
X_matrix

# creare matrice Y var
Y <- c(2, 3, 4)
random_vectorY <- runif(length(Y))
Y_matrix <- matrix(c(Y, random_vectorY / sum(random_vectorY)), ncol = 2)


# initializare caz particular, pot fi inlocuite mai tarziu cu valori aleatoare

random_matrix[2:(length(X) + 1), 1] <- X_matrix[,1]
random_matrix[2:(length(X) + 1),length(Y) + 2] <- X_matrix[,2]

random_matrix[1, 2:(length(Y) + 1)] <- Y_matrix[,1]
random_matrix[(length(X) + 2), 2:(length(Y) + 1)] <- Y_matrix[,2]
random_matrix[(length(X) + 2), (length(Y) + 2)] <- 1

inner_values <- runif(length(X) * length(Y))

for (i in 1:nrow(random_matrix)) {
  for (j in 1:ncol(random_matrix)) {
    if (i > 1 && i<= (length(Y) + 1) && j > 1 && j <= (length(X) + 1) && random_matrix[i, j] == 0) {
      maximul <- min(random_matrix[(length(X) + 2),i] - sum(random_matrix[2:(length(X) + 1), i]), random_matrix[i,(length(Y) + 2)] - sum(random_matrix[i,2:(length(Y) + 1)]))
      random_num <- runif(1, min = 0, max = maximu)
      random_matrix[i, j] <- random_num
      print("repeated")
    }
    print (i, j)
  }
}


# varianta sample
for (i in 2:(nrow(random_matrix) - 1) {
      maximul <- min(random_matrix[(length(X) + 2),i] - sum(random_matrix[2:(length(X) + 1), i]), random_matrix[i,(length(Y) + 2)] - sum(random_matrix[i,2:(length(Y) + 1)]))
      random_nums <- sample(0:maximul, ncol(random_matrix) - 2, replace = T)
      random_matrix[i, 2:ncol(random_matrix) - 1] <- random_nums
      print("repeated")
    }
    print (i, j)
}

count_zeros_row <- function(matrix, n) {  # numara cate zero - uri am pe linie / coloana 
  counter = 0
  for (i in 1:n) {
    if (random_matrix[i] == 0) {
      counter = counter + 1
    }   
  }
  return(counter)
}



# Example usage:
data_matrix <- random_matrix[3,1:5]
data_matrix1 <- random_matrix[2:3,1]
zero_counts_row <- count_zeros_row(data_matrix1, 2)
zero_counts_column <- count_zeros_column(data_matrix)



