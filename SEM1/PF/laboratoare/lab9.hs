{-# LANGUAGE InstanceSigs #-}
import Data.Char()
import Data.List()

sfChr :: Char -> Bool
sfChr c = c `elem` ".?!:"

countProp :: String -> Int 
countProp "" = 0
countProp (h : t) = if sfChr h then 1 + countProp t else countProp t

countProp2 :: String -> Int 
countProp2 text = sum [if sfChr x then 1 else 0 | x <- text]

--ex2
elemPoz :: [Int] -> Bool
elemPoz [] = True
elemPoz l = foldr (\h -> (&&) (h > 0)) True l

check :: [[Int]] -> Int -> Bool
check matrice n = foldr ((&&). elemPoz) True $ filter (\linie -> length linie == n) matrice


--ex 3

data Punct = Pt [Int]
  deriving (Show, Eq)

data Arb = Vid | F Int | N Arb Arb
  deriving (Show, Eq)

class ToFromArb a where
  toArb :: a -> Arb
  fromArb :: Arb -> a

instance ToFromArb Punct where
  toArb :: Punct -> Arb
  toArb (Pt []) = Vid
  toArb (Pt (h : t)) = N (F h) (toArb(Pt t))

  fromArb :: Arb -> Punct
  fromArb Vid = Pt []
  fromArb (F x) = Pt [x]
  fromArb (N st dr) = 
    let Pt lst1 = fromArb st 
        Pt lst2 = fromArb dr
    in
      Pt (lst1 ++ lst2)

