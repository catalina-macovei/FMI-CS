import Data.List
import Data.Char
import System.Console.Terminfo (restoreDefaultColors)
import Distribution.Simple.Utils (safeHead)

myInt = 31415926535897932384626433832795028841971693993751058209749445923

double :: Integer -> Integer
double x = x + x


--maxim :: Integer -> Integer -> Integer
maxim x y = if (x > y)
               then x
          else y

max3 x y z = let
             u = maxim x y
             in (maxim  u z)

max4 :: Integer -> Integer -> Integer -> Integer -> Integer
max4 x y z m = let
            u = maxim x y 
            in (maxim u (maxim z m))    -- definitie locala cu let

sumSq x y = x*x + y*y


oddOrEven :: Integral a => a -> String
oddOrEven x = if (mod x 2 == 0) then "par" else "impar"

factorial n = product[1..n]

graterOrLower x y = if (x > 2 * y) then "greater" else "lower"
 
findMaximum :: Ord a => [a] -> a
findMaximum xs = maximum xs

-- foo2 :: (Int -> Char) -> String
-- foo2 (n,s) = "str"


------------------------------------------------------------------------------------------------------------------
----------------------------       RECAPITULARE        -----------------------------------------------------------

circleArea :: Double -> Double
circleArea r = pi * rsquare 
    where pi = 3.1415926           -- definitie pi
          rsquare = r * r          -- definite rsquare


-- Acelasi lucru cu let -> let este o expresie
circleAreaL :: Double -> Double
circleAreaL r = let pi = 3.1415    -- atentie la identari!!!
                    rsquare = r * r
               in pi * rsquare     -- definitiile exista deja, aceasta e expr principala


-- Definitiile locale pot avea si definitii de functii
circleAreaFun :: Double -> Double
circleAreaFun r = pi * rsquare r
     where pi = 3.14
           rsquare r = r * r

circleAreaFunL :: Double -> Double
circleAreaFunL r = let pi = 3.14
                       rsquare r = r * r
                    in pi * rsquare r


-- nu putem avea definitii multiple !
-- Exemplu de infinite loop in haskell
-- deoarece incearca sa defineasca variabila locala x = x + 1, prin urmare, evaluand x continua sa incrementeze la infinit
increment x  = let x = x + 1
               in x



-----------------------------------------------------------
----------- Despre pattern matching -----------------------

describe :: Integer -> String
describe 0 = "This is zero!"
describe 1 = "The one!"
describe 2 = "The second!"
describe n = "Any other number greater than 2!"        -- cazul general mereu la sfarsit!


----------- Patteern match pe argumente multiple -----------
login :: String -> String -> String
login "Unicorn66" "Fabulous99" = "You've successfully logged in!"
login "Unicorn66" _ = "Wrong password, baby!"
login _ _ = "Oops, unknown user!"


-----------------------------------------------------------
----------- Despre Recursion        -----------------------
----------- Beneficiu global: tot felul de iteratii in haskell sunt implementate recursiv

factorial1 :: Int -> Int
factorial1 1 = 1
factorial1 n = n * factorial(n - 1)

fibonacci :: Int -> Int
fibonacci 1 = 1
fibonacci 2 = 1     -- caz de baza -> aici se opreste loop-ul 
fibonacci n = fibonacci (n - 2) + fibonacci (n - 1)


----------- Recursivitate + Helper functions 
--ex: o functie care repeta un string de n ori si returneaza concatenarea repetitiilor
repString :: Int -> String -> String
repString n str = helperf n str "" 
     
helperf n str result = if (n == 0)
                       then result
                       else helperf (n - 1) str (result ++ str)

-- aceeasi functie cu pattern matching
repeat1 :: Int -> String -> String

repeat1 n str = helperr n str ""

helperr 0 str result = result
helperr n str result = helperr (n - 1) str (result ++ str)


----------- Guards
-- similar pattern matching, dar poti avea ecuatii arbitrare
describe1 :: Int -> String
describe1 n 
     | n == 2 = "Doi"
     | even n = "Par"
     | otherwise = "No description"

-- putem combina guards cu pattern mathing

-- joc -> ghici varsta
guess :: String -> Int -> String
guess "Griselida" age 
     | age == 0 = "No way!!!"
     | age < 30 = "Too low!"
     | age > 30 = "Too high!"
     | otherwise = "Right!"
guess "Harry" age
     | age == 0 = "No way!!!"
     | age < 35 = "Too low!"
     | age > 35 = "Too high!"
     | otherwise = "Right!"
guess name age = "Unknown person!"


-----------------------------------------------------------
-----------         Despre Liste        -------------------

-- [a] - means any list
-- import Data.List syntax

-- un ex care sterge elementele 3 si 4 dintr-o lista folosind take si drop

sterg :: [Int] -> [Int] 
sterg lista = take 2 lista ++ drop 4 lista

rotatie :: [Int] -> [Int]
rotatie lista = tail lista ++ [head lista]   -- mut elementul de la inceput la final

rotatiePolimorfism :: [a] -> [a]
rotatiePolimorfism lista = tail lista ++ [head lista]   -- mut elementul de la inceput la final

-----------------------------------------------------------
-----------         Despre Maybe        -------------------
pherapsmult :: Int -> Maybe Int -> Int
pherapsmult num Nothing = num
pherapsmult num (Just another_num) = num * another_num

-- Safe HEAD
intOrZero :: Maybe Int -> Int
intOrZero Nothing = 0
intOrZero (Just a_number) = a_number

safeHead1 :: [Int] -> Maybe Int
safeHead1 lista = if null lista 
                 then Nothing 
                 else Just (head lista)

headOrZero :: [Int] -> Int
headOrZero lista = intOrZero (safeHead1 lista)

lecturePart :: [Either Int String]
lecturePart = [Right "one", Left 1, Left 2, Right "secret"]

-- Un exemplu interesant
palindrome :: String -> Bool
palindrome str = str == reverse str     -- merge si pe string

-- putem folosi show pentru a converti din Int in String
palindromeN ::[ Int ]-> [String]
palindromeN lista = filter palindrome (map show lista) 

-- cate cuvinte dintr-un string incep cu a
startsWithA :: String -> Int
startsWithA prop = length (filter help (words prop))
     where help a = head a == 'a'


