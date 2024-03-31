import Data.Char
-- 1
data Prop =
  V String
  | T
  | F
  | Prop :&: Prop
  | Prop :|: Prop
  deriving (Show, Eq)

class Operations exp where
  simplify :: exp -> exp

instance Operations Prop where
  simplify (T :&: p) = simplify p 
  simplify (p :&: T) = simplify p 
  simplify (F :|: p) = simplify p 
  simplify (p :|: F) = simplify p
  simplify (p1 :&: p2) = (simplify p1) :&: (simplify p2)
  simplify (p1 :|: p2) = (simplify p1) :|: (simplify p2) 
  simplify e = e

prop1 = ((V "p") :|: (V "q")) :&: T
prop2 = prop1 :|: (V "r")
prop3 = ((F :&: V "p") :|: (V "q"))
prop4 = prop3 :&: (V "q")

-- 2

morph :: String -> String
morph "" = ""
morph (h:t)
  |isUpper h = (toLower h) : morph t
  |isLower h = (toUpper h) : morph t 
  |isDigit h = '*' : morph t
  |otherwise = morph t

morphM :: String -> String
morphM s = do
  c <- s
  if isUpper c then
    do return $ toLower c
  else if isLower c then
    do return $ toUpper c
  else if isDigit c then
    do return '*'
  else 
    ""

-- 3

newtype WriterM a =  MW {getMW :: (Maybe a, String)}
  deriving Show

instance Monad WriterM where
  return x = MW (Just x, "")
  ma >>= k = let (a1 , s1) = getMW ma
              in case a1 of
                Nothing -> MW (Nothing, s1)
                Just val -> let (a2, s2) = getMW $ k val
                            in MW (a2, s1 ++ s2)


testWriterM :: WriterM Int
testWriterM = ma >>= k
 where
 ma = MW (Nothing, "ana are mere ")
 k x = MW (if x `mod` 2==0 then Just x else Nothing, "si pere!" )


instance Applicative WriterM where
  pure = return
  mf <*> ma = do
    f <- mf
    a <- ma
    return (f a)
  
instance Functor WriterM where
  fmap f ma = pure f <*> ma