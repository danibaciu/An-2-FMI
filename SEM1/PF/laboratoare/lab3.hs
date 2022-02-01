--danibaciu
import Data.List
import Data.Char

--1 numarare vocale din cuvinte palindrom
nrVocale :: [String] -> Int
nrVocale [] = 0
nrVocale (h:t)
  | h == reverse h =
    let 
      calcul :: String -> Int
      calcul "" = 0
      calcul (x : xs)
        | elem x "aeiou" = 1 + calcul xs
        | otherwise = calcul xs
    in
      calcul h + nrVocale t
  | otherwise = nrVocale t


--2 adaugare x dupa fiecare element par din lista
fct :: Int -> [Int] -> [Int]
fct _ [] = []
fct nr (x : xs) 
  | mod x 2 == 0 = x : nr : (fct nr xs)
  | otherwise = x : (fct nr xs)


--3 divizori
divizori :: Int -> [Int]
divizori x = [nr | nr <- [1..x], mod x nr == 0]


--4 lista listelor de divizori
listadiv :: [Int] -> [[Int]]
listadiv list = [divizori nr | nr <- list]


--5a) recursiv
inIntervalRec :: Int -> Int -> [Int] -> [Int]
inIntervalRec x y [] = []
inIntervalRec x y (h:t)
  | x <= h && h <= y = h : inIntervalRec x y t
  | otherwise = inIntervalRec x y t


--5b)
inIntervalComp :: Int -> Int -> [Int] -> [Int]
inIntervalComp x y list = [nr | nr <- list, nr >= x, nr <= y]


--6a) recursiv
pozitiveRec :: [Int] -> Int
pozitiveRec [] = 0
pozitiveRec (h:t)
  | h > 0 = 1 + pozitiveRec t
  | otherwise = pozitiveRec t


--6b)
pozitiveComp :: [Int] -> Int
pozitiveComp list = length [nr | nr <- list, nr > 0]


--7a recursiv
pozitiiImpare :: [Int] -> [Int]
pozitiiImpare list =
  let f [] _ = []
      f (h : t) i
        | mod h 2 == 1 = i : f t (i + 1)
        | otherwise = f t (i + 1)
  in f list 0


--7b
pozitiiImpareComp :: [Int] -> [Int] --fac perechi cu zip
pozitiiImpareComp list = [snd x | x <- zip list [0..(length list - 1)], mod (fst x) 2 == 1]


--8a
multDigitsRec :: String -> Int 
multDigitsRec "" = 1
multDigitsRec (h : t)
  | isDigit h = digitToInt h * multDigitsRec t
  | otherwise = multDigitsRec t


--8b
multDigitsComp :: String -> Int 
multDigitsComp list = foldl (*) 1 [digitToInt nr | nr <- list, isDigit nr]
