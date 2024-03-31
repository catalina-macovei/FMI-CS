import Data.Char
-- 1
-- Sa se scrie o functie care pentru o lista de numere intregi afiseaza suma 
-- dintre diferenta dintre doua elemente de pe pozitii consecutive daca elementele 
-- sunt divizibile cu 3 sau produsul dintre ele, altfel. 
-- f [1,2,3,6,7,9,3]= (1*2) +(2*3) +(3-6) +(6*7)+(7*9)+(9-3)=116
-- Pentru punctaj maxim scrieti si prototipul functiei cerute.

f1 :: [Int] -> Int
f1 [] = 0
f1 [x] = 0
f1 (x:y:xs) = if (mod x 3 == 0) && (mod y 3 == 0)
                then (x - y) + f1 (y:xs)
                else (x * y) + f1 (y:xs)



-- 2
-- 2. Sa se scrie o functie care primeste o lista de siruri de caractere 
-- si un numar intreg si verifica daca sirurile care au lungimea mai mare strict 
-- decat numarul dat contin acelasi numar de vocale si consoane.
-- Pentru punctaj maxim scrieti si prototipul functiei cerute.
-- f ["ana are mere", "mere", "pere", "unu", "aa"] 3 = False
-- f ["x are mere", "mere", "pere", "unu", "aa"] 3 = True

nrVoc :: String -> Int
nrVoc xs = sum [1 | x <- xs, x `elem` "aeiouAEIOU"]

nrCons :: String -> Int
nrCons xs = length $ filter (`elem` "bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ") xs

f2 :: [String] -> Int -> Bool
f2 [] _ = True
f2 (x:xs) nr = if length x > nr
                then
                    (nrVoc x == nrCons x) && f2 xs nr
                else f2 xs nr


--3
-- 3. Sa se scrie o functie care primeste ca parametru o lista de liste de numere intregi 
-- si calculeaza produsul sumelor elementelor pare de pe fiecare linie. 
-- In rezolvarea exercitiului NU se vor folosi functiile product sau sum.
-- Pentru punctaj maxim scrieti si prototipul functiei cerute. 
-- f [[1,2,3],[4,5,6,7],[8,9]] == 2*10 * 8 == 160


sumPare :: [Int] -> Int
sumPare [] = 0
sumPare (x:xs) = if even x then x + sumPare xs else sumPare xs

f3 :: [[Int]] -> Int
f3 = foldr ((*) . sumPare) 1



--4
-- 4. Sa se scrie o functie care primeste un sir de caractere si o lista de siruri de caractere 
-- si verifica daca toate sirurile care au ca prefix sirul dat ca parametru, au lungime para.
-- Pentru punctaj maxim scrieti si prototipul functiei cerute.
-- f ["this is it", "this is that", "another example!"] "this" = True


f4 :: [String] ->String -> Bool
f4 [] _ = True
f4 (x:xs) str
    | take (length str) x == str && even (length x) = f4 xs str
    | take (length str) x /= str = f4 xs str
    | otherwise = False

--5
type Name = String
type Def = String
data Dictionar = I Name Def
                | Ld Name [Dictionar]
                deriving Show


d1 = Ld "animal" [Ld "mamifer" [I "elefant" "acesta e un elefant", I "caine" "acesta este un caine", I "pisica" "aceasta este o pisica"], I "animale domestice" "definitie"]
d2 = Ld "Animal" [Ld "Mamifer" [I "Elefant" "acesta e un elefant",I "calne" "acesta este un caine",I "piSIca" "aceasta este o pisica"],I "animale domestice" "definitie"]
d3 = Ld "animal" [Ld "mamifer" [I "elefant" "Acesta e un Elefant", I "caine" "acesta este un caine", I "pisica" "aceasta este o pisica"], I "animale domestice" "definitie"]

--5a
-- a) Sa se scrie o functie care primeste ca parametru un dictionar si intoarce lista de titluri ale intrarilor din acesta.
-- titluri d1 = ["elefant", "caine" "pisica" "animale domestice"]

f5a :: Dictionar -> [Name]
f5a (I n d) = [n]
f5a (Ld n dict) = concatMap f5a dict

--5b
-- b) Sa se instantieze clasa Eq asfel incat sa se verifice egalitatea intre doua dictionare, 
-- comparand componentele lor in ordinea in care apar. Titlurile intrarilor sunt verificate fara a tine cont de litere mici sau mari.
-- I "caine" "animal" == I "CaiNe" "animal" = True
-- I "Caine" "Animal" == I "Caine" "animal" = False

instance Eq Dictionar where
  (I title1 def1) == (I title2 def2) = map toLower title1 == map toLower title2 && def1 == def2
  (Ld title1 entries1) == (Ld title2 entries2) = map toLower title1 == map toLower title2 && entries1 == entries2
  _ == _ = False

--6 
-- 6. Sa se scrie o functie care primeste o lista de liste de numere intregi si doua numere intregi n si m
--  si verifica daca numarul sublistelor care au doar elemente divizibile cu 3 este cuprins intre n si m 
--  (sau m si n, in functie de ordinea in care sunt date).
-- Ex: f [[1,2,3,4,5], [3,9,12], [33], [39,123]] 4 1 == f [[1,2,3,4,5], [3,9,12], [33], [39,123]] 1 4 == True
-- Pentru punctaj maxim scrieti si prototipul functiei cerute.


divBy3 :: [Int] -> Bool
divBy3 list = filter (\x -> mod x 3 == 0) list == list

howMany :: [[Int]] -> Int
howMany [] = 0
howMany (x:xs) = if divBy3 x then 1 + howMany xs else howMany xs

f6 :: [[Int]] -> Int -> Int -> Bool
f6 [] _ _ = True
f6 xs m n
  | m >= n &&  howMany xs >= n && howMany xs <= m = True
  | m < n &&  howMany xs >= m && howMany xs <= n = True
  | otherwise = False

--7
-- 7. Se da urmatorul tip de date reprezentand arbori ternari cu informatia de tip intreg in radacina.
-- data Tree = Empty 
--   | Node Int Tree Tree Tree -- arbore vid cu valoare de tip Int in radacina si 3 fii

-- extree :: Tree
-- extree = Node 4 (Node 5 Empty Empty Empty) (Node 3 Empty Empty (Node 1 Empty Empty Empty)) Empty

-- Sa se instantieze clasa urmatoare pentru tipul Tree. 
-- class ArbInfo t where
--   level :: t-> Int -- intoarce inaltimea arborelui; pt un arbore vid se considera ca are inaltimea 0
--   sumval:: t -> Int -- intoarce suma valorilor din arbore
--   nrFrunze :: t -> Int -- intoarce nr de frunze al arborelui



data Tree = Empty 
  | Node Int Tree Tree Tree -- arbore vid cu valoare de tip Int in radacina si 3 fii

extree :: Tree
extree = Node 4 (Node 5 Empty Empty Empty) (Node 3 Empty Empty (Node 1 Empty Empty Empty)) Empty

class ArbInfo t where
  level :: t-> Int -- intoarce inaltimea arborelui; pt un arbore vid se considera ca are inaltimea 0
  sumval:: t -> Int -- intoarce suma valorilor din arbore
  nrFrunze :: t -> Int -- intoarce nr de frunze al arborelui



instance ArbInfo Tree where 
  level Empty = 0 
  level (Node r t1 t2 t3) = 1 + max (max (level t1) (level t2)) (level t3)

  sumval Empty = 0
  sumval (Node r t1 t2 t3) =  r + sumval t1 + sumval t2 + sumval t3 

  nrFrunze Empty = 0 
  nrFrunze (Node _ Empty Empty Empty) = 1 
  nrFrunze (Node r t1 t2 t3) = nrFrunze t1 + nrFrunze t2 + nrFrunze t3
