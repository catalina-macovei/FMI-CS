import Data.List
-- Laborator 2: --

--ex1
--poly :: double -> double -> double -> double -> double
poly a b c x = a * x * x + b * x + c

--ex2
eeny :: Integer -> String
eeny x = if (mod x 2 == 0) then "eeny" else "meeny" 

--ex3
fizzbuzz :: Integer -> String
--fizzbuzz x = if (mod x 3 == 0 && mod x 5 == 0) then "FizzBuzz" else if (mod x 3 == 0)  then "Fizz" else if (mod x 5 == 0) then "Buzz"

fizzbuzz x
    | mod x 3 == 0 && mod x 5 == 0  = "FizzBuzz"
    | mod x 3 == 0 = "Fizz"
    | mod x 5 == 0 = "Buzz"
    | otherwise = " "

--Recursivitate fibbonacci:
-- fibbonacciCazuri :: Integer -> Integer

-- fibbonacciCazuri n
--     | n < 2     = n
--     | otherwise = fibbonacciCazuri (n - 1) + fibbonacciCazuri (n - 2)

-- Stil ecuational:
fibbonacciEcuational :: Integer -> Integer

fibbonacciEcuational 0 = 0
fibbonacciEcuational 1 = 1
fibbonacciEcuational n = fibbonacciEcuational (n - 1) + fibbonacciEcuational (n - 2)

-- ex 4: Tribonacci
tribonacciCazuri :: Integer -> Integer

tribonacciCazuri n
    | n <= 2    = 1
    | n == 3    = 2
    | otherwise = tribonacciCazuri (n - 1) + tribonacciCazuri (n - 2) + tribonacciCazuri(n - 3)

-- Tribonacci stil ecuational:
tribonacciEcuational 1 = 1
tribonacciEcuational 2 = 1
tribonacciEcuational 3 = 2
tribonacciEcuational n = tribonacciEcuational (n - 1) + tribonacciEcuational (n - 2) + tribonacciEcuational (n - 3)

--ex 5
binomial :: Integer -> Integer -> Integer
binomial n k
    | n == 0    = 1
    | k == 0    = 1
    | otherwise = binomial (n - 1) k + binomial (n - 1) (k - 1)

-- ex 6 a

numUniques :: (Eq a) => [a] -> Int
numUniques = length.nub

verifL :: [Int] -> String

verifL mylist = if  (mod (length mylist) 2 == 0) then "para" else "impara"

-- ex 6 b
takeFinal :: [Int] -> Int -> [Int]

takeFinal l n = take n (reverse l)

-- ex 6 c

remove1 :: [Int] -> Int -> [Int]

remove1 l n = (take (n - 1) l) ++ (drop n l)

semiPareRec :: [Int] -> [Int]
semiPareRec [] = []
semiPareRec (h:t)
    | even h = h `div` 2 : t'
    | otherwise = t'
    where t' = semiPareRec t

myreplicate :: Int -> a -> [a]
myreplicate n x 
    | n <= 0    = []    -- -- If n is less than or equal to 0, return an empty list.
    | otherwise = x : myreplicate (n - 1) x   -- Otherwise, prepend 'x' to the result of 'myreplicate (n - 1) x'.

sumImp :: [Int] -> Int
sumImp lis
    | length lis == 0 = 0
    | otherwise = head lis + sumImp(tail lis)


totalLen :: [String] -> Int
totalLen lis = countStartingWithA lis
    where
        countStartingWithA [] = 0                  -- Base case: an empty list has 0 matches.
        countStartingWithA (x:xs)
            | isPrefixOf "A" x = 1 + countStartingWithA xs
            | otherwise = countStartingWithA xs
