import Data.List()
import Data.Char()


--1
firstEl :: [(a, b)] -> [a]
firstEl ls = map fst ls


--2
sumList :: [[Int]] -> [Int]
sumList = map sum


--3
prel2 :: [Int] -> [Int]
prel2 = map (\x -> if even x then x `div` 2 else x * 2)


-- 4.
filtreaza :: Char -> [[Char]] -> [[Char]]
filtreaza c = filter (elem c)
 

-- 5.
patrateImpare :: [Int] -> [Int]
patrateImpare ls = map (^2) (filter odd ls)


--6
patratePozitiiImpare :: [Int] -> [Int]
patratePozitiiImpare ls = map ((^2).snd) (filter (odd.fst) (zip [1..] ls))


--7
noCons :: [String] -> [String]
noCons = map (filter (`elem` "AEIOUaeiou"))


--8
mymap :: (a -> b) -> [a] -> [b]
mymap f [] = []
mymap f (h : t) = (f h) : (mymap f t)
 

myfilter :: (a -> Bool) -> [a] -> [a]
myfilter f [] = []
myfilter f (h : t)
    | f h = h : (myfilter f t)
    | otherwise = myfilter f t
    

-- 9.
sumPatrateImpare :: [Int] -> Int
sumPatrateImpare ls = foldr (+) 0 (map (^2) (filter odd ls))
 

-- 10
allTrue :: [Bool] -> Bool
allTrue = foldr (&&) True

-- 11
rmChar :: Char -> String -> String
rmChar ch string = [c | c <- string, c /= ch]

rmCharsRec :: String -> String -> String 
rmCharsRec _ [] = []
rmCharsRec unwanted (x:xs)
  | x `notElem` unwanted = x: rmCharsRec unwanted xs
  | otherwise            = rmCharsRec unwanted xs

rmCharsFold :: String -> String -> String
rmCharsFold unwanted = foldr (\c -> if c `notElem` unwanted then (c:)
  else id) []