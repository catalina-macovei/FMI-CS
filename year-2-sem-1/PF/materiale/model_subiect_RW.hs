import Data.List
import Data.Maybe
import Control.Monad
-- 1

-- tip de date cu nr variabil de coordonate intregi
data Point = Pt [Int]
             deriving Show

-- arbori binari de cautare cu codurile sortate

data Arb = Empty | Node Int Arb Arb
           deriving Show

class ToFromArb a where
    toArb :: a -> Arb
    fromArb :: Arb -> a

-- Instanță pentru tipul de date Point
instance ToFromArb Point where
    -- Funcția de conversie de la Point la Arb
   toArb (Pt []) = Empty
   toArb (Pt [x]) = Node x Empty Empty
   toArb (Pt (p:x:lista)) = Node p (toArb (Pt [x])) (toArb (Pt lista))

   fromArb :: Arb -> Point
   fromArb Empty = Pt []
   fromArb (Node n Empty Empty) = Pt [n]
   fromArb (Node n arb1 arb2) = Pt (l ++ r)
                                where Pt l = fromArb arb1
                                      Pt r = fromArb arb2


-- 2
-- construieste folosind lista initiala, lista nr aflate in interval
inInterval :: Int -> Int ->  Int -> Bool
inInterval nr a b = if nr >= a && nr <= b
                    then True
                    else False


f :: Int -> Int -> [Int] -> [Int]
f _ _ [] = []
f a b (x:lista) = if inInterval x a b
                  then x : f a b lista
                  else f a b lista

-- pentru optiunea cu monade -> putem folosi Maybe


f1 :: Int -> Int -> [Int] -> Maybe [Int]
f1 _ _ [] = Nothing
f1 a b (x:lista) = if inInterval x a b
                  then Just (x : f a b lista)
                  else Just (f a b lista)



--2 Monada ReaderWriter
newtype ReaderWriter env a = RW { getRW :: env -> (a, String) }

instance Functor (ReaderWriter env) where
  fmap f ma = RW $ \env ->
    let (val, log) = getRW ma env
    in (f val, log)

instance Applicative (ReaderWriter env) where
  pure x = RW $ \_ -> (x, "")
  mf <*> ma = RW $ \env ->
    let (f, log1) = getRW mf env
        (val, log2) = getRW ma env
    in (f val, log1 ++ log2)

instance Monad (ReaderWriter env) where
  return = pure
  ma >>= k = RW $ \env ->
    let (val, log1) = getRW ma env
        (val', log2) = getRW (k val) env
    in (val', log1 ++ log2)

-- Test
testReaderWriter :: ReaderWriter String Int
testReaderWriter = do
  x <- RW $ \env -> (length env, "Calculating length\n")
  y <- RW $ \env -> (2 * x, "Doubling the length\n")
  return (x + y)

-- Example usage
example :: (Int, String)
example = getRW testReaderWriter "Hello, World!"
