import Data.Maybe(fromJust)
import Data.List (nub)
type Nume=String 
data Prop
    =Var Nume
    | F
    | T
    |Not Prop
    | Prop :|: Prop
    | Prop :&:  Prop
    | Prop :->: Prop
    | Prop :<->: Prop
    deriving Eq
infixr 2 :|:
infixr 3 :&:
infixr 7 :->:
infixr 8 :<->:

p1 :: Prop
p1 = (Var "P" :|: Var "Q") :&: (Var "P" :&: Var "Q")

p2 :: Prop
p2 = (Var "P" :|: Var "Q") :&: (Not (Var "P") :&: Not (Var "Q"))
 
p3 :: Prop
p3 =
    (Var "P" :&: (Var "Q" :|: Var "R"))
        :&: ((Not (Var "P") :|: Not (Var "Q")) :&: (Not (Var "P") :&: Not (Var "R")))



instance Show Prop where
    show (Var nume) = nume
    show F = "F"
    show T = "T"
    show (Not prop) = "(~" <> show prop <> ")"
    show (prop1 :&: prop2) = "(" <> show prop1 <> "&" <> show prop2 <> ")"
    show (prop1 :|: prop2) = "(" <> show prop1 <> "|" <> show prop2 <> ")"
    show (prop1 :->: prop2) = "(" <> show prop1 <> "->" <> show prop2 <> ")"
    show (prop1 :<->: prop2) = "(" <> show prop1 <> "<->" <> show prop2 <> ")"

 
test_ShowProp :: Bool
test_ShowProp =
    show (Not (Var "P") :&: Var "Q") == "((~P)&Q)"



type Env = [(Nume, Bool)]

impureLookup :: Eq a => a -> [(a,b)] -> b
impureLookup a = fromJust . lookup a



eval :: Prop -> Env -> Bool
eval (Var nume) env = impureLookup nume env
eval F env = False
eval T env = True
eval (Not prop) env = not (eval prop env)
eval (prop1 :&: prop2) env = eval prop1 env && eval prop2 env
eval (prop1 :|: prop2) env = eval prop1 env || eval prop2 env
eval (prop1 :->: prop2) env = eval prop1 env < eval prop2 env
eval (prop1 :<->: prop2) env = eval prop1 env == eval prop2 env

test_eval = eval  (Var "P" :|: Var "Q") [("P", True), ("Q", False)]



variabile :: Prop -> [Nume]
variabile (Var nume) = [nume]
variabile F = []
variabile T = []
variabile (Not prop) = variabile prop
variabile (prop1 :&: prop2) = nub $ variabile prop1 <> variabile prop2
variabile (prop1 :|: prop2) = nub $ variabile prop1 <> variabile prop2
variabile (prop1 :->: prop2) = nub $ variabile prop1 <> variabile prop2
variabile (prop1 :<->: prop2) = nub $ variabile prop1 <> variabile prop2
 
test_variabile =
  variabile (Not (Var "P") :&: Var "Q") == ["P", "Q"]




envs :: [Nume] -> [[(Nume, Bool)]]
envs [] = []
envs [x] = [[(x, False)], [(x, True)]]
envs (str : xs) =
    let r = envs xs
     in map ((str, False) :) r ++ map ((str, True) :) r
 
test_envs = 
    envs ["P", "Q"]
    ==
    [ [ ("P",False)
      , ("Q",False)
      ]
    , [ ("P",False)
      , ("Q",True)
      ]
    , [ ("P",True)
      , ("Q",False)
      ]
    , [ ("P",True)
      , ("Q",True)
      ]
    ]

satisfiabila :: Prop -> Bool
satisfiabila p = foldr ((||) . eval p) False (envs (variabile p))
 
test_satisfiabila1 = satisfiabila (Not (Var "P") :&: Var "Q")
test_satisfiabila2 = satisfiabila (Not (Var "P") :&: Var "P") == False

valida :: Prop -> Bool
valida p = not $ satisfiabila (Not p)

test_valida1 = valida (Not (Var "P") :&: Var "Q") == False
test_valida2 = valida (Not (Var "P") :|: Var "P")


echivalenta :: Prop -> Prop -> Bool
echivalenta p q = and [eval (p :<->: q) (x ++ y) | x <- envs( variabile p),y <- envs(variabile q)]

 
test_echivalenta1 = (Var "P" :&: Var "Q") `echivalenta` (Not (Not (Var "P") :|: Not (Var "Q")))
test_echivalenta2 =
  False
  ==
  (Var "P") `echivalenta` (Var "Q")
test_echivalenta3 = (Var "R" :|: Not (Var "R")) `echivalenta` (Var "Q" :|: Not (Var "Q"))