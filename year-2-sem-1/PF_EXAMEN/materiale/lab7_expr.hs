data Expr = Const Int -- integer constant
          | Expr :+: Expr -- addition
          | Expr :*: Expr -- multiplication
           deriving Eq

data Operation = Add | Mult deriving (Eq, Show)

data Tree = Lf Int -- leaf
          | Node Operation Tree Tree -- branch
           deriving (Eq, Show)
           
instance Show Expr where
  show (Const x) = show x
  show (e1 :+: e2) = "(" ++ show e1 ++ " + "++ show e2 ++ ")"
  show (e1 :*: e2) = "(" ++ show e1 ++ " * "++ show e2 ++ ")"           

--Scrieti o functie evalExp :: Expr -> Int care evalueaza o expresie determinând valoarea  acesteia.
evalExp :: Expr -> Int
evalExp (Const x) = x
evalExp (e1 :+: e2) = evalExp e1 + evalExp e2
evalExp (e1 :*: e2) = evalExp e1 * evalExp e2


exp1 = ((Const 2 :*: Const 3) :+: (Const 0 :*: Const 5))
exp2 = (Const 2 :*: (Const 3 :+: Const 4))
exp3 = (Const 4 :+: (Const 3 :*: Const 3))
exp4 = (((Const 1 :*: Const 2) :*: (Const 3 :+: Const 1)) :*: Const 2)
test11 = evalExp exp1 == 6
test12 = evalExp exp2 == 14
test13 = evalExp exp3 == 13
test14 = evalExp exp4 == 16

evalArb :: Tree -> Int
evalArb (Lf x) = x
evalArb (Node Add left right) = evalArb left + evalArb right
evalArb (Node Mult left right) = evalArb left * evalArb right


arb1 = Node Add (Node Mult (Lf 2) (Lf 3)) (Node Mult (Lf 0)(Lf 5))
arb2 = Node Mult (Lf 2) (Node Add (Lf 3)(Lf 4))
arb3 = Node Add (Lf 4) (Node Mult (Lf 3)(Lf 3))
arb4 = Node Mult (Node Mult (Node Mult (Lf 1) (Lf 2)) (Node Add (Lf 3)(Lf 1))) (Lf 2)

test21 :: Bool
test21 = evalArb arb1 == 6
test22 = evalArb arb2 == 14
test23 = evalArb arb3 == 13
test24 = evalArb arb4 == 16


expToArb :: Expr -> Tree
expToArb (Const x) = Lf x
expToArb (e1 :+: e2) = Node Add (expToArb e1) (expToArb e2)
expToArb (e1 :*: e2) = Node Mult (expToArb e1) (expToArb e2)



data IntSearchTree value
  = Empty
  | BNode
      (IntSearchTree value)     -- elemente cu cheia mai mica
      Int                       -- cheia elementului
      (Maybe value)             -- valoarea elementului
      (IntSearchTree value)     -- elemente cu cheia mai mare
  
lookup':: Int -> IntSearchTree value -> Maybe value
lookup' _ Empty = Nothing
lookup' key (BNode leftTree k value rightTree)
  | key == k = value
  | key < k = lookup' key leftTree
  | otherwise = lookup' key rightTree


keys ::  IntSearchTree value -> [Int]
keys Empty = []
keys (BNode leftTree key _ rightTree) = keys leftTree ++ [key] ++ keys rightTree


-- values :: IntSearchTree value -> [value]
-- values Empty = []
-- values (BNode leftTree _ value rightTree) = values leftTree ++ [value] ++ values leftTree

-- insert :: Int -> value -> IntSearchTree value -> IntSearchTree value
-- insert key value Empty = BNode key value Empty Empty
-- insert key value (BNode k v left right)
--   | key == k = BNode key value left right
--   | key < k = BNode k v (insert key value left) right
--   | otherwise = BNode k v left (insert key value right)


delete :: Int -> IntSearchTree value -> IntSearchTree value
delete = undefined 

toList :: IntSearchTree value -> [(Int, value)]
toList = undefined

fromList :: [(Int,value)] -> IntSearchTree value 
fromList = undefined

printTree :: IntSearchTree value -> String
printTree = undefined

-- balance :: IntSearchTree value -> IntSearchTree value
-- balance = undefined

data Natural = Zero | Succesor Natural

--adunarea tipului de date algebric Peano
(+++) :: Natural -> Natural -> Natural
m +++ Zero = m
m +++ Succesor n = Succesor (m +++ n)

-- date personale
--type
type FirstName  = String
type LastName = String
type Age = Int
type Height = Float
type Phone = String

data Person = Person FirstName LastName Age Height Phone

firstName :: Person -> String
firstName (Person firstname _ _ _ _) = firstname

lastName :: Person -> String
lastName (Person _ lastname _ _ _) = lastname

age :: Person -> Int
age (Person _ _ agev _ _) = agev

height :: Person -> Float
height (Person _ _ _ heightv _) = heightv

phone :: Person -> String
phone (Person _ _ _ _ phonev) = phonev

data Point a b = Pt a b
                 deriving (Eq, Ord, Show)

-- Instanta clasa Functor
data CountingBad a = Heisenberg Int a
                     deriving (Eq, Show)

instance Functor CountingBad where
  fmap f (Heisenberg n a) = Heisenberg n (f a)