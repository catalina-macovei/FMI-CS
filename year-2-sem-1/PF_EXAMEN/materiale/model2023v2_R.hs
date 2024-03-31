import Data.List
import Data.Char


data Expr = Var String | Val Int | Plus Expr Expr | Mult Expr Expr
            deriving (Show, Eq)

class Operations exp where
    simplify :: exp -> exp


instance Operations Expr where
    simplify :: Expr -> Expr
    simplify (Var a)  = Var a
    simplify (Val b ) = Val b
    
    simplify (Mult (Val 0) _) = Val 0
    simplify (Mult _ (Val 0)) = Val 0
    simplify (Mult exp (Val b)) 
        | b == 1 = simplify exp
        | otherwise = Mult (simplify exp) (Val b) 
    simplify (Plus  (Val 0) (Val a)) = Val a
    simplify (Plus (Val a) (Val 0)) = Val a
    
    simplify (Plus exp (Val 0)) = simplify exp
    simplify (Plus (Val 0) exp) = simplify exp

    simplify (Mult exp1 exp2) = Mult (simplify exp1) (simplify exp2)
    simplify (Plus exp1 exp2) = Plus (simplify exp1) (simplify exp2)


-- o fct care transforma un sir in varianta lui din limba pasareasca
-- cons m -> mPm

isConsoana :: Char -> Bool
isConsoana ch = if elem ch "qwrtypsfghjklzxcvbnmQWRTYPSDFGHJKLZXCVBNM"
                then True
                else False


toPasar :: String -> String
toPasar "" = ""
toPasar (c:sir) = if isConsoana c 
                  then c :'P':c:(toPasar sir)
                  else c:(toPasar sir)

-- cu monada Maybe

-- toPasarM :: String -> Maybe String
-- toPasarM "" = Nothing
-- toPasarM (c:sir) = if isConsoana c 
--                   then Just  (c : 'P' : c : toPasarM sir)
--                   else Just  (c : toPasarM sir)

toPasarM :: String -> Maybe String
toPasarM "" = Just ""
toPasarM (c:sir) =
  if isConsoana c 
    then do
      rest <- toPasarM sir
      Just (c : 'P' : c : rest)
    else do
      rest <- toPasarM sir
      Just (c : rest)


----- Alt model
-- se transforma str dupa codificarea
-- lit mari -> litere mici
-- lit mici -> litere mari
-- cifre -> *
-- restul -> elimin

codifica :: String -> String 
codifica "" = ""
codifica (s:str) 
  | isAlpha s && isUpper s = toLower s : codifica str
  | isAlpha s && isLower s = toUpper s : codifica str
  | isDigit s = '*' : codifica str
  | otherwise = codifica str

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


-- Monada ReaderM
newtype ReaderM env a = ReaderM { runReaderM :: env -> Either String a }

instance Functor (ReaderM env) where
  fmap f ma = ReaderM $ \env ->
    case runReaderM ma env of
      Left err -> Left err
      Right val -> Right (f val)

instance Applicative (ReaderM env) where
  pure x = ReaderM $ \_ -> Right x
  mf <*> ma = ReaderM $ \env ->
    case (runReaderM mf env, runReaderM ma env) of
      (Left err, _) -> Left err
      (_, Left err) -> Left err
      (Right f, Right val) -> Right (f val)

instance Monad (ReaderM env) where
  return = pure
  ma >>= k = ReaderM $ \env ->
    case runReaderM ma env of
      Left err -> Left err
      Right val -> runReaderM (k val) env

instance Show (ReaderM env a) where
  show _ = "ReaderM function"

-- Test
testReaderM :: ReaderM String String
testReaderM = ma >>= k
  where
    ma = ReaderM $ \str -> if length str > 10 then Right (length str) else Left ""
    k val = ReaderM $ \str -> if val `mod` 2 == 0 then Right "par" else Left ""






