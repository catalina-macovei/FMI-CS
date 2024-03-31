import Data.List
import Data.Char
ePalindrom:: String -> Bool
ePalindrom s = s == (reverse s)

eVocala:: Char -> Bool
eVocala c = elem c "aeiouAEIOU"

numarVocale:: String -> Int
numarVocale(c:s) 
    | s == " " = 0
    | eVocala c = 1 + numarVocale s
    | otherwise = numarVocale s

nrVocale:: [String] -> Int
nrVocale(s:xs)  
    | xs == [] = 0
    | ePalindrom s = numarVocale s + nrVocale xs
    | otherwise = nrVocale xs 


ePar :: Int -> Bool
ePar x = if (mod x 2 == 0) then True else False

addElem:: Int -> [Int] -> [Int]
addElem x lis 
    | lis == [] = []
    | ePar (head lis) = x: (tail lis)
    | otherwise = addElem x (tail lis)

divizori :: Int -> [Int]
divizori n = [x | x <- [1..n], mod n x == 0]

listadiv :: [Int] -> [[Int]]
listadiv lis = [(divizori x) | x <- lis]

inIntervalCom :: Int -> Int -> [Int] -> [Int]
inIntervalCom a b lis = [x | x <- lis, x >= a && x <= b]

inIntervalRec :: Int -> Int -> [Int] -> [Int]
inIntervalRec a b lis
    | lis == [] = []
    | ( head lis) <= a || (head lis) >= b = take (head lis) lis
    | otherwise = inIntervalRec a b lis

pozitivComp :: [Int] -> [Int]
pozitivComp lis = [x | x <- lis, x > 0]
  
-- zip xs [0..] pairs each element in the list xs with its corresponding index (starting from 0).  
pozitiiImpare :: [a] -> [a]
pozitiiImpare xs = [x | (x, i) <- zip xs [0..], even i]
-- !! operator in Haskell is used to access elements at a specific index within a list. It is called the list indexing operator. 


posImp :: [a] -> [a]
posImp lis = [x | (x, i) <- zip lis [0..], even i]


--EX8
productOfDigits :: String -> Int
productOfDigits "" = 1
productOfDigits (s:str) = if isDigit s
  then digitToInt s * productOfDigits str
  else productOfDigits str

--ex9
getPermutations :: [Int] -> [[Int]]
getPermutations lis = permutations lis

--ex10
getCombinations :: [Int] -> [[Int]]
getCombinations lis = tail (subsequences lis)

--ex11
getArrangements:: [Int] -> [[Int]]
getArrangements lis = permutations lis