import Data.List
import Data.Char

{-
[x^2 |x <- [1..10], x `rem` 3 == 2]
[(x,y) | x <- [1..5], y <- [x..(x+2)]]
[(x,y) | x <- [1..3], let k = x^2, y <- [1..k]]
[x | x <- "Facultatea de Matematica si Informatica", elem x ['A'..'Z']]
[[x..y] | x <- [1..5], y <- [1..5], x < y]
-}

ordonataNat :: [Int] -> Bool
ordonataNat [] = True
ordonataNat [x] = True
ordonataNat (x:xs) = undefined
ordonata :: [a] -> (a -> a -> Bool) -> Bool
ordonata = undefined

--Exemplu ex 2:
factori :: Int -> [Int]
factori n = [x | x <- [1..n], mod n x == 0 ]

--Ex 3:
prim :: Int -> Bool
prim n = if length (factori n) == 2 then True else False

--Ex4:
numerePrime :: Int -> [Int]
numerePrime n = [x | x <- [1..n], prim x]

--Ex5
--expected: myzip3 [1,2,3] [1,2] [1,2,3,4] == [(1,1,1),(2,2,2)]

myzip3 :: Int -> Int -> Int -> [(Int, Int, Int)]
myzip3 a b c = [(x, y, z) | x <- [1..a], y <- [1..b], z <- [1..c]]

myzip31 ::[Int] -> [Int] -> [Int] -> [(Int, Int, Int)]
myzip31 a b c = [(x, y, z) | x <- a, y <- b, z <- c]

--Ex6
firstEl :: [(a, b)] -> [a]
firstEl lis = map fst lis


sn :: [(a, b)] -> [b]
sn lis = map snd lis

--Ex7
sumList :: [[Int]] -> [Int]
sumList lis = map sum lis

--Ex8
divMult :: Int -> Int
divMult n = if even n then div n 2 else n * 2 

prel1 :: [Int] -> [Int]
prel1 lis = map ( \x -> divMult x) lis


--Ex9

charL :: Char -> [String] -> [String]
charL ch lis = filter (elem ch) lis

--Ex10
squareN :: [Int] -> [Int]
squareN lis = map (\x -> x * x) lis

--Ex11
pozitiiImpare :: [Int] -> [Int]
pozitiiImpare xs = [x*x | (x, i) <- zip xs [0..], even i]

--Ex12
eVocala:: Char -> Bool
eVocala c = elem c "aeiouAEIOU" 

takeVoc :: String -> String
takeVoc str = filter (eVocala) str

numaiVocale :: [String] -> [String]
numaiVocale lstr = map (takeVoc) lstr

--Ex13
mymapD:: (a -> b) -> [a] -> [b]
mymapD f xs = [f x | x <- xs]

mymap :: (a -> b) -> [a] ->[b]
mymap f [] = []
mymap f (x:xs) = f x : mymap f xs

myFilterD :: (a -> Bool) -> [a] -> [a]
myFilterD p xs = [x | x <- xs, p x]  --selecteaza elem din lista care satisfac predicatul

myfilter :: (a -> Bool) -> [a] -> [a]
myfilter p [] = []
myfilter p (x:xs) | p x = x : myfilter p xs
                | otherwise = myfilter p xs 


-- myUnzip :: [(a, b)] -> ([a], [b])
-- myUnzip [] = ([], [])  -- Base case: Empty list, return empty lists
-- myUnzip ((x, y):rest) =  -- Deconstruct the head of the list
--     let (xs, ys) = myUnzip rest  -- Recursively process the rest of the list
--     in (x : xs, y : ys)  -- Construct the resulting lists by prepending x and y
-- myUnzip :: [(a, b)] -> ([a], [b])
-- myUnzip = foldr (\(x, y) (xs, ys) -> (x:xs, y:ys)) ([], [])


