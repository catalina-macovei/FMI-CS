
import Control.Monad

newtype BM a = BM { getBM :: (String, Maybe a) } deriving Show

instance Functor BM where
  fmap f (BM (log, maybeVal)) = BM (log, fmap f maybeVal)

instance Applicative BM where
  pure x = BM ("", Just x)
  (BM (log1, mf)) <*> (BM (log2, ma)) =
    BM (log1 ++ log2, mf <*> ma)

-- instanta pentru monada
instance Monad BM where
  return x = BM ("", Just x)
  (BM (log1, ma)) >>= k =
    let (log2, mb) = getBM (k <$> ma)
    in BM (log1 ++ log2, joinMaybe mb)

-- utilitar pwntru maybe
joinMaybe :: Maybe (BM a) -> (String, Maybe a)
joinMaybe Nothing = ("", Nothing)
joinMaybe (Just (BM (log, maybeVal))) = (log, maybeVal)

-- este generata o eroare
-- 242_V3_MacoveiCatalina_P3.hs:28:7: error:
--     parse error on input ‘<-’
--     Suggested fix: Possibly caused by a missing 'do'?
testBM :: BM Int
testBM = ma >>= f
  where 
    x <- BM ("ana are mere ", Just 7)
    f x <- BM ("si pere!", if even x then Just x else Nothing)


main :: IO ()
main = print $ getBM testBM
