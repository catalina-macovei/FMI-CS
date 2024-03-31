-- sa se instantieze clasa pentru Lista si functia myZip

data Pereche a b = MyP a b deriving Show 
newtype Lista a = MyL [a] deriving Show

--clasa
class MyOp m where 
    myZip :: m a -> m b -> m (Pereche a b)

--exemplu ajutator
lp1 = MyL [97,3,100]
lp2 = MyL ['a'..'d']
--myZip lp1 lp2 = MyL [MyP 97 'a', MyP 3 'b', MyP 100 'c']

-- instatiere clasei

instance MyOp Lista where
    myZip (MyL xs) (MyL ys) = MyL (zipWith MyP xs ys)

-- Exemplu de utilizare

example :: Lista (Pereche Int Char)
example = myZip lp1 lp2


