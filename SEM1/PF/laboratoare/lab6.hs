import Data.Char
import Data.List


-- 1.
rotate :: Int -> [Char] -> [Char]
rotate n (l:lista)
        | n == 0                        = l:lista
        | n < 0 || n > length (l:lista) = error "N este negativ sau mai mare decat lungimea listei"
        | n > 0                         = rotate (n-1) (lista ++ [l])

-- 2.
prop_rotate :: Int -> String -> Bool
prop_rotate k str = rotate (l - m) (rotate m str) == str
                        where l = length str
                              m = if l == 0 then 0 else k `mod` l

-- 3.
makeKey :: Int -> [(Char, Char)]
makeKey n = [(x,y)| (x,y)<- zip ['A'..'Z'] (rotate n ['A'..'Z'])]

-- 4.
lookUp :: Char -> [(Char, Char)] -> Char
lookUp c (l:lista)
        | null lista  = c
        | c == fst l      = snd l
        | otherwise       = lookUp c lista

-- 5.
encipher :: Int -> Char -> Char
encipher key ch = lookUp ch $ makeKey key

-- 6.
normalize :: String -> String
normalize (s:str)
  | str == "" = ""
  | isAlphaNum s = if isLower s then toUpper s : normalize str
      else s : normalize str
  | otherwise = normalize str

-- 7.
encipherStr :: Int -> String -> String
encipherStr nr list = [encipher nr carac | carac <- normalize list]

-- 8.
reverseKey :: [(Char, Char)] -> [(Char, Char)]
reverseKey sir = [(snd x, fst x) | x <- sir]

-- 9.
decipher :: Int -> Char -> Char
decipher val ch = lookUp ch . reverseKey . makeKey $ val

decipherStr :: Int -> String -> String
decipherStr _ "" = ""
decipherStr val (x:xs)
  | x == ' ' || isDigit x = x : decipherStr val xs
  | isAlpha x && isUpper x = decipher val x : decipherStr val xs
  | otherwise = decipherStr val xs