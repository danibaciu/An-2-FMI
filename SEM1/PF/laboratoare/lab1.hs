-- danibaciu

import Data.List

myInt = 55555

double :: Integer -> Integer
double x = x+x


--maxim :: Integer -> Integer -> Integer
maxim x y = if (x > y)
               then x
          else y

max3 x y z = let
             u = maxim x y
             in maxim  u z


triplet :: Integer->Integer
triplet x = 3 * x 


maxim3:: Integer->Integer->Integer->Integer
maxim3 x y z = if (x >= y)    -- Daca x >= y
                    then
                         if(x >= z)     -- Daca x >= y si x >= z 
                              then x    -- Se returneaza x, intrucat e maximul
                              else z    -- Daca x >= y si x < z atunci z este maximul, intrucat y <= x < z
                    else
                         if(y >= z)     -- Daca x < y si y >= z
                              then y    -- Atunci returnam y
                              else z    -- Altfel returnam z
                              
                    

maxim4:: Integer -> Integer -> Integer -> Integer -> Integer -- 4 Parametri si un rezultat
maxim4 x y z t = 
     let 
          u = maxim x y  -- Calculam maximul dintre x si y
     in 
          let
               v = maxim u z  -- Calculam maximul dintre x, y si z
          in
               maxim v t  -- Calculam maximul dintre x, y, z si t si returnam rezultatul

testare_maxim4:: Integer->Integer->Integer->Integer -> Bool
-- Functia ia ca parametri 4 Integer-uri pentru a putea apela maxim4 si intoarce un Bool(daca rezultatul se afla sau nu in relatie)
testare_maxim4 a b c d =
     let
          rezultat = maxim4 a b c d     -- rezultat == rezultatul din maxim4
     in
          if(rezultat >= a && (rezultat > b || rezultat == b) && not(rezultat < c) && rezultat >= d) -- Verficam daca rezultat >= fiecare dintre parametri
               then True
               else False


-- 6.a)

patrate:: Integer->Integer->Integer
patrate x y = x*x + y*y

-- 6.b)

este_par:: Integer->String
este_par x = if (x `mod` 2 == 0) 
          then "par"
          else "impar"


-- 6.c)

fact:: Integer->Integer
fact n = if(n == 0) then 1
     else n * fact(n - 1)


-- 6.d)

verif::Integer -> Integer -> Bool
verif x y = if(x > 2*y) then True
     else False

