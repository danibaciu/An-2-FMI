--danibaciu

-- 1

poly2::Double->Double->Double->Double->Double
poly2 a b c x = a * x * x + b * x + c

-- 2

eeny::Integer->[Char]
eeny x = if(x `mod` 2 == 0)
            then "eeny"
        else "meeny"


-- 3

fizzbuzz:: Integer -> [Char]
fizzbuzz x
    | mod x 3 == 0 && mod x 5 == 0 = "FizzBuzz"
    | mod x 3 == 0 = "Fizz"
    | mod x 5 == 0 = "Buzz"
    | otherwise = ""

-- 4

tribonacci:: Integer -> Integer
tribonacci n = if n == 1 then 1
                else if n == 2 then 1
                    else if n == 3 then 2
                        else tribonacci(n-1) + tribonacci(n-2) + tribonacci(n-3)

-- 5

binomial:: Integer->Integer->Integer
binomial n k = if n == 0 then 0
                else if k == 0 then 1
                    else binomial(n - 1) (k) + binomial (n - 1) (k - 1)



-- 6a

verifL:: [Int]->Bool
verifL x = if((length x) `mod` 2 == 0) 
                then True
            else False

-- 6b


takefinal:: [Int]->Int->[Int]
takefinal list n = if length(list) < n then list
                    else drop (length(list) - n) list


-- 6 Bonus , punem char in loc de int
takeFinal:: [Char]->Int->[Char]
takeFinal list n = if length(list) < n then list
    else drop (length(list) - n) list

-- 6c
remove::[Int]->Int->[Int]
remove lista n = (take n lista) ++ (drop (n+1) lista)


-- 7a
myreplicate::Int->Int->[Int]
myreplicate n v = if(n == 1) 
                        then [v]
                    else v : myreplicate (n - 1) v 

-- 7b

sumImp :: [Int] -> Int
sumImp list = if(length list == 0)
                    then 0
                else 
                    if((head (list)) `mod` 2 /= 0)
                        then head (list) + sumImp (drop 1 list)
                    else sumImp(drop 1 list)

-- 7c

totalLen :: [String] -> Int
totalLen [] = 0
totalLen (h : t)
    | head(h) == 'A' = length(h) + t'
    | otherwise = t'
    where t' = totalLen(t)

    

