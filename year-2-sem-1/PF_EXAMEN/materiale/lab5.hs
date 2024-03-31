import Data.List
import Data.Char
    


--1
sumAllEven :: [Int] -> Int
sumAllEven lista = foldr (+) 0 (filter odd lista)

sumEven :: [Int] -> Int
sumEven lista = foldl (+) 0 (filter odd lista)

--2
allTrue :: [Bool] -> Bool
allTrue lista = foldr (&&) True lista

allT::[Bool] -> Bool
allT lista = foldl (&&) True lista
--3 
allVerifies :: (Int -> Bool) -> [Int] -> Bool
allVerifies pr lista = foldr (&&) True (map pr lista)

--4
anyVerifies :: (Int -> Bool) -> [Int] -> Bool
anyVerifies pr lista = foldr (||) True (map pr lista)

--5
mapFoldr :: (a -> b) -> [a] -> [b]
mapFoldr pr lista = foldr ((:) . pr) [] lista

filterFoldr :: (a -> Bool) -> [a] -> [a]
filterFoldr pr lista = foldr (\x acumulez -> if pr x then x : acumulez else acumulez) [] lista

--6
--elem*10+elem urmator
listToInt :: [Integer]-> Integer
listToInt lista = foldl (\acc x -> acc * 10 + x ) 0 lista

--7a
rmChar :: Char -> String -> String
rmChar ch str = foldr (\x acc -> if ch == x then acc else x : acc) "" str

--7b
rmCharsRec :: String -> String -> String
rmCharsRec " " " " = " "
rmCharsRec " " str2 = str2
--rmCharsRec (s1:str1) str2 = 

--7c
--rmCharsFold :: String -> String -> String
--rmCharsFold str1 str2 = foldr (\acc x -> rmChar x str2 : acc) "" str2

--8
myReverse :: [Int] -> [Int]
myReverse lista = foldl (\acc x -> x : acc) [] lista

--9
myElem :: Int -> [Int] -> Bool
myElem el lista = foldl (\acc x -> if x == el then True else acc) False lista

--10
myUnzip :: [(a, b)] -> ([a], [b])
myUnzip = foldr (\(x, y) (xs, ys) -> (x:xs, y:ys)) ([], [])

--11
myunion :: [Int] -> [Int] -> [Int]
myunion list1 list2 = foldl (\acc x -> if x `elem` list1 then acc else x:acc) list1 list2 

--12
myintersect :: [Int] -> [Int] -> [Int]
myintersect list1 list2 = foldl (\acc x -> if (x `elem` list1 && x `elem` list2) then x:acc else acc ) [] list1

--13

--mypermutations lista = 