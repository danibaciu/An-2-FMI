import Data.Char()
import Data.List()

data Fruct
  = Mar String Bool
  | Portocala String Int

ionatanFaraVierme = Mar "Ionatan" False
goldenCuVierme = Mar "Golden Delicious" True
portocalaSicilia10 = Portocala "Sanguinello" 10
listaFructe = [Mar "Ionatan" False,
                Portocala "Sanguinello" 10,
                Portocala "Valencia" 22,
                Mar "Golden Delicious" True,
                Portocala "Sanguinello" 15,
                Portocala "Moro" 12,
                Portocala "Tarocco" 3,
                Portocala "Moro" 12,
                Portocala "Valencia" 2,
                Mar "Golden Delicious" False,
                Mar "Golden" False,
                Mar "Golden" True]

ePortocalaDeSicilia :: Fruct -> Bool
ePortocalaDeSicilia (Portocala soi _) = soi `elem` ["Moro", "Sanguinello", "Tarocco"]
ePortocalaDeSicilia (Mar _ _) = False

test_ePortocalaDeSicilia1 =
    ePortocalaDeSicilia (Portocala "Moro" 12) == True
test_ePortocalaDeSicilia2 =
    ePortocalaDeSicilia (Mar "Ionatan" True) == False


nrFeliiSicilia :: [Fruct] -> Int
nrFeliiSicilia list = sum $ map (\(Portocala soi felii) -> felii) (filter ePortocalaDeSicilia list)

test_nrFeliiSicilia = nrFeliiSicilia listaFructe == 52


nrMereViermi :: [Fruct] -> Int
nrMereViermi list = sum $ map isInfected list
                where
                  isInfected (Mar _ True) = 1
                  isInfected _ = 0

test_nrMereViermi = nrMereViermi listaFructe == 2

type NumeA = String
type Rasa = String
data Animal = Pisica NumeA | Caine NumeA Rasa
    deriving Show

vorbeste :: Animal -> String
vorbeste (Pisica _) = "Meow!"
vorbeste (Caine _ _) = "Woof!"

rasa :: Animal -> Maybe String
rasa (Caine _ x) = Just x
rasa (Pisica _) = Nothing 

data Linie = L [Int]
   deriving Show
data Matrice = M [Linie]
   deriving Show


fct :: [Linie] -> [Int]
fct = map (\(L x) -> sum x)

f1 :: [Int] -> Int -> Bool
f1 [] _ = True 
f1 (h : t) n = (h == n) && f1 t n

f2 :: [Int] -> Int -> Bool
f2 list n = foldr ((&&) .(==n)) True list


verifica :: Matrice -> Int -> Bool
verifica (M mat) = f2 (fct mat)
-- in locul lui f2 puteam scrie f1

test_verif1 = verifica (M[L[1,2,3], L[4,5], L[2,3,6,8], L[8,5,3]]) 10 == False
test_verif2 = verifica (M[L[2,20,3], L[4,21], L[2,3,6,8,6], L[8,5,3,9]]) 25 == True

list1::Linie->[Int]
list1 (L a)=a

lungn ::Linie->Int->Bool
lungn (L a) n = length a == n

doarPozN :: Matrice -> Int -> Bool 
doarPozN (M linii) n = foldr (&&) True [length(list1 ln) == length(filter(>=0)(list1 ln))| ln <- linii ,lungn ln n]

testPoz1 = doarPozN (M [L[1,2,3], L[4,5], L[2,3,6,8], L[8,5,3]]) 3 == True

testPoz2 = doarPozN (M [L[1,2,-3], L[4,5], L[2,3,6,8], L[8,5,3]]) 3 == False


corect :: Matrice -> Bool
corect (M []) = True
corect (M [L _]) = True
corect (M (x:xs))
    |length (list1 x) == length (list1(head xs))= corect (M xs)
    |otherwise = False


testcorect1 = corect (M[L[1,2,3], L[4,5], L[2,3,6,8], L[8,5,3]]) == False
testcorect2 = corect (M[L[1,2,3], L[4,5,8], L[3,6,8], L[8,5,3]]) == True