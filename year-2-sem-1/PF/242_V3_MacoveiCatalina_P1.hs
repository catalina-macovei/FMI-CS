-- nr din lista [11,33,55] se ridica la patrat
-- ex : P/U LISTA [3,11,24,6] -> SE OBTINE SIRUL [3,3,121,6,6]
-- Rezolvati o solutie fara monade si una cu monade 

isPar10 :: Int -> Bool
isPar10 nr = if mod nr 2 == 0 && nr > 10
             then True
             else False

isInLista :: Int -> Bool
isInLista nr = if elem nr [11,33,55]
               then True
               else False


codific :: [Int] -> [Int]
codific [] = []
codific (el:lista) = if el < 10
                     then el:el:(codific lista) 
                     else if isInLista el
                          then el*el :(codific lista) 
                     else if isPar10 el 
                          then (codific lista)
                     else el:(codific lista)


-- codifc cu monade, intra intr-un loop infinit 
codificM :: [Int] -> [Int]
codificM [] = []
codificM lista = do
        el <- lista
        if el < 10
        then do return el
        else if isInLista el
            then do return (el*el)  
        else if isPar10 el 
            then do (codificM lista)    --se genereaza un apel recursiv , din cauza lui e loop infinit, dar nu am stiut cum altfel sa sterg elementul corespunzator din lista
        else do return el