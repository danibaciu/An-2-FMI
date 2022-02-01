import Data.List
import Data.Char

--1
factori :: Int -> [Int]
factori x = [nr | nr <- [1..x] , mod x nr == 0]

--2
prim :: Int -> Bool
prim x = length (factori x) == 2

--3
numerePrime :: Int -> [Int]
numerePrime x = [nr | nr <- [2..x], prim nr]

--4
myzip3 :: [Int] -> [Int] -> [Int] -> [(Int,Int,Int)]
myzip3 _ _ [] = []
myzip3 _ [] _ = []
myzip3 [] _ _ = []
myzip3 (h1 : t1) (h2 : t2) (h3 : t3) = 
  if not (null t1) &&  not (null t2) && not (null t3)
    then (h1, h2, h3) : myzip3 t1 t2 t3
  else [(h1, h2, h3)]

--5
ordonataNat :: [Int] -> Bool
ordonataNat [] = True
ordonataNat [x] = True
ordonataNat (h : t) = and [x <= y | (x, y) <- zip (h : t) t]

--6
ordonataNat1 :: [Int] -> Bool
ordonataNat1 [] = True
ordonataNat1 [x] = True
ordonataNat1 (h : t) = (h <= head t) && ordonataNat1 t

--7
ordonata :: [a] -> (a -> a -> Bool) -> Bool
ordonata [] _ = True
ordonata [x] _ = True
ordonata (h : t) sign = (h `sign` head t) && ordonata t sign

--8
(*<*) :: (Integer, Integer) -> (Integer, Integer) -> Bool
(*<*) (a,b) (c,d) = a < c && b < d

--9 ruleaza, am verif
compuneList :: (b -> c) -> [(a -> b)] -> [(a -> c)]
compuneList fct [] = []
compuneList fct (h : t) = fct.h : compuneList fct t

--10
aplicaList :: a -> [(a -> b)] -> [b]
aplicaList x list = map (\h -> h x) list
