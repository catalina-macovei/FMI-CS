import Data.Char
import Data.Ratio (numerator)

-- 1
-- Sa se scrie o functie care pentru o lista de numere intregi afiseaza suma 
-- dintre diferenta dintre doua elemente de pe pozitii consecutive daca elementele 
-- sunt divizibile cu 3 sau produsul dintre ele, altfel. 
-- f [1,2,3,6,7,9,3]= (1*2) +(2*3) +(3-6) +(6*7)+(7*9)+(9-3)=116
-- Pentru punctaj maxim scrieti si prototipul functiei cerute.
f :: [Int] -> Int
f [] = 0
f [a] = 0   -- daca am o lista cu un element
f (a:b:lista) = if mod a 3 == 0 && mod b 3 == 0
              then a - b + f (b:lista)
              else a * b + f (b:lista)

-- 2
-- 2. Sa se scrie o functie care primeste o lista de siruri de caractere 
-- si un numar intreg si verifica daca sirurile care au lungimea mai mare strict 
-- decat numarul dat contin acelasi numar de vocale si consoane.
-- Pentru punctaj maxim scrieti si prototipul functiei cerute.
-- f ["ana are mere", "mere", "pere", "unu", "aa"] 3 = False
-- f ["x are mere", "mere", "pere", "unu", "aa"] 3 = True

eVocala :: Char -> Bool
eVocala ch = elem ch "aeiouAEIOU"

eConsoana :: Char -> Bool
eConsoana ch = elem ch "qwrtypsdfghjklzxcvbnmQWRTYPSDFGHJKLZXCVBNM"

takeVocale :: String -> String
takeVocale str = filter (eVocala) str

takeConsoane :: String -> String
takeConsoane strC = filter (eConsoana) strC

f2 :: [String] -> Int -> Bool
f2 []  _ = True
f2 (el:lista) n = if length el > n
                  then (length  (takeVocale el) == length (takeConsoane el)) && f2 lista n
                  else f2 lista n

--3
-- 3. Sa se scrie o functie care primeste ca parametru o lista de liste de numere intregi 
-- si calculeaza produsul sumelor elementelor pare de pe fiecare linie. 
-- In rezolvarea exercitiului NU se vor folosi functiile product sau sum.
-- Pentru punctaj maxim scrieti si prototipul functiei cerute. 
-- f [[1,2,3],[4,5,6,7],[8,9]] == 2*10 * 8 == 160

f3 :: [[Int]] -> Int
f3 [] = 1
f3 (el:lista) = sumPare el * f3 lista


sumPare :: [Int] -> Int
sumPare [] = 0
sumPare (el:lista) = if mod el 2 == 0 
                     then el + sumPare lista
                     else sumPare lista

-- 4. 
-- Sa se scrie o functie care primeste un sir de caractere si o lista de siruri de caractere 
-- si verifica daca toate sirurile care au ca prefix sirul dat ca parametru, au lungime para.
-- Pentru punctaj maxim scrieti si prototipul functiei cerute.
-- f ["this is it", "this is that", "another example!"] "this" = True

isPrefix :: String -> String -> Bool
isPrefix str pref = if take (length pref) str == pref 
                    then True 
                    else False

f4 :: [String] -> String -> Bool
f4 [] _ = True
f4 (str:lista) pref = if isPrefix str pref 
                      then mod (length str ) 2 == 0 && f4 lista pref
                      else f4 lista pref



-- 6. Sa se scrie o functie care primeste o lista de liste de numere intregi si doua numere intregi n si m 
-- si verifica daca numarul sublistelor care au doar elemente divizibile cu 3 este cuprins intre n si m 
-- (sau m si n, in functie de ordinea in care sunt date).
-- Ex: f [[1,2,3,4,5], [3,9,12], [33], [39,123]] 4 1 == f [[1,2,3,4,5], [3,9,12], [33], [39,123]] 1 4 == True
-- Pentru punctaj maxim scrieti si prototipul functiei cerute.

mod3 :: Int -> Bool
mod3 el = mod el 3 == 0

allVerifies3 :: [Int] -> Bool
allVerifies3 [] = False
allVerifies3 lista = foldl (&&) True (map mod3 lista)

f6 :: [[Int]] -> Int -> Int -> Bool
f6 [] _ _ = True
f6 liste n m = length (filter allVerifies3 liste) > n && length (filter allVerifies3 liste) < m || length (filter allVerifies3 liste) < n && length (filter allVerifies3 liste) > m 




--5. Se dau urmatoarele tipuri de date reprezentand dictionare. 
--Un dictionar poate fi format dintr-o intrare (cu titlu si definitie) sau o lista de dictionare 
--(continand un titlu si lista de dictionare).


type Name = String
type Def = String
data Dictionar = I Name Def| Ld Name [Dictionar]
                 deriving Show
d1 = Ld "animal" [Ld "mamifer" [I "elefant" "acesta e un elefant", I "caine" "acesta este un caine", I "pisica" "aceasta este o pisica"], I "animale domestice" "definitie"]
d2 = Ld "Animal" [Ld "Mamifer" [I "Elefant" "acesta e un elefant",I "calne" "acesta este un caine",I "piSIca" "aceasta este o pisica"],I "animale domestice" "definitie"]
d3 = Ld "animal" [Ld "mamifer" [I "elefant" "Acesta e un Elefant", I "caine" "acesta este un caine", I "pisica" "aceasta este o pisica"], I "animale domestice" "definitie"]

-- a) Sa se scrie o functie care primeste ca parametru un dictionar 
-- si intoarce lista de titluri ale intrarilor din acesta.
-- titluri d1 = ["elefant", "caine" "pisica" "animale domestice"]

f5 :: Dictionar -> [Name]
f5 (I nume definitie) = [nume]
f5 (Ld nume dict) = concatMap f5 dict


-- b) Sa se instantieze clasa Eq asfel incat sa se verifice egalitatea intre doua dictionare, 
-- comparand componentele lor in ordinea in care apar. Titlurile intrarilor sunt verificate 
-- fara a tine cont de litere mici sau mari.
-- I "caine" "animal" == I "CaiNe" "animal" = True
-- I "Caine" "Animal" == I "Caine" "animal" = False

instance Eq Dictionar where 
    (I nume definitie) == (I nume1 definitie1) = map toLower nume == map toLower nume1 &&  definitie == definitie1
    (Ld nume dict) == (Ld nume1 dict1) = map toLower nume == map toLower nume1 && dict == dict1     -- apel recursiv
    _ == _ = False


--7
-- 7. Se da urmatorul tip de date reprezentand arbori ternari cu informatia de tip intreg in radacina.
data Tree = Empty 
  | Node Int Tree Tree Tree -- arbore vid cu valoare de tip Int in radacina si 3 fii

extree :: Tree
extree = Node 4 (Node 5 Empty Empty Empty) (Node 3 Empty Empty (Node 1 Empty Empty Empty)) Empty

-- Sa se instantieze clasa urmatoare pentru tipul Tree. 
class ArbInfo t where
    level :: t-> Int -- intoarce inaltimea arborelui; pt un arbore vid se considera ca are inaltimea 0
    sumval:: t -> Int -- intoarce suma valorilor din arbore, pt arborer vid suma = 0
    nrFrunze :: t -> Int -- intoarce nr de frunze al arborelui, pt arbore cu copacii goi nrFrunze = 1


instance ArbInfo Tree where 
    level Empty = 0
    level (Node nr arb1 arb2 arb3) = 1 + max (max (level arb1) (level arb2)) (level arb3)

    sumval Empty = 0
    sumval (Node nr arb1 arb2 arb3) = nr + sumval arb1 + sumval arb2 + sumval arb3

    nrFrunze Empty = 0
    nrFrunze (Node _ Empty Empty Empty) = 1
    nrFrunze (Node nr arb1 arb2 arb3) = nrFrunze arb1 + nrFrunze arb2 + nrFrunze arb3
