type Name = String

data  Value  =  VBool Bool
     |VInt Int
     |VFun (Value -> Value)
     |VError

data  Hask  = HTrue | HFalse
     |HIf Hask Hask Hask
     |HLit Int
     |Hask :*: Hask
     |Hask :==: Hask
     |Hask :+:  Hask
     |HVar Name
     |HLam Name Hask
     |Hask :$: Hask
     


infix 4 :==:
infixl 7 :*:
infixl 6 :+:
infixl 9 :$:

type  HEnv  =  [(Name, Value)]

--1.1
instance Show Value where
     show (VBool True)="True"
     show (VBool False)="False"
     show (VInt a)=(show a)
     show (VFun a)="Functie"
   
--2
instance Eq Value where
    (VInt a)==(VInt b)= a==b
    (VBool b)==(VBool a)= a==b
    (VError)==(VError) = error "nu se poate compara VError"
    (VInt a) == (VBool a1)=error "nu se pot compara doua tipuri diferite Int cu Bool"
    (VBool a) == (VInt a1)=error "nu se pot compara doua tipuri diferite Bool cu Int"
    (VBool a) == (VError) =error "nu se pot compara doua tipuri diferite Bool cu VError"
    (VInt a) == (VError) =error "nu se pot compara doua tipuri diferite Int cu VError"
    (VFun _) == (VError) =error "nu se pot compara doua tipuri diferite functie cu Verror"
    (VFun _) == (VInt b) =error "nu se pot compara doua tipuri diferite functie cu Int"
    (VFun _) == (VBool b) =error "nu se pot compara doua tipuri diferite functie cu Bool"
    (VInt b) == (VFun _) =error "nu se pot compara doua tipuri diferite functie cu Int"
    (VBool b) == (VFun _) =error "nu se pot compara doua tipuri diferite functie cu Bool"
    (VFun  _) == (VFun _) = error "nu se pot compara doua tipuri diferite functie cu Bool"

 

cautaVal::Hask -> HEnv->Value
cautaVal (HVar a) []= VError
cautaVal (HVar a) (x:xs)
    |a==fst x=snd x
    |otherwise =cautaVal (HVar a) xs     

hEval :: Hask -> HEnv -> Value
hEval HTrue r      =  VBool True
hEval HFalse r        =  VBool False
hEval (HIf c d e) r   = hif (hEval c r) (hEval d r) (hEval e r)
  where  hif (VBool b) v w  =  if b then v else w
         hif _ _ _ = error "primul argument nu este de tip bool"
hEval (HVar a1) l=cautaVal (HVar a1) l 

hEval (HLit a) l= VInt a

hEval (HLam c p ) l = VFun (\v -> hEval p ((c, v) : l))

                            

hEval (p :==: q) l=VBool (hEval p l == hEval q l)
hEval (p :$: q) l=let
                              func = hEval p l
                              nr = hEval q l
                            in
                              case func of
                                (VFun f) -> f nr
                                _ -> error "primul argument nu este o functie"
hEval (p:+:q) l= let 
                     x = hEval p l 
                     y = hEval q l
                    in
                        case (x,y) of 
                        ((VInt v),(VInt c)) -> (VInt (v+c))
                        _ -> error "unul din argumente nu e de tip INT"
hEval (p:*:q) l= let 
                     x = hEval p l 
                     y = hEval q l
                    in
                        case (x,y) of 
                        ((VInt v),(VInt c)) -> (VInt (v*c))
                        _ ->error "unul din argumente nu este de tip INT"

h2 = hEval (HIf HTrue (HVar "x" :+: HVar "y") (HVar "x")) [("x",VInt 2),("y", VInt 30)] -- 32
h3 = hEval (HIf HFalse (HVar "x" :+: HVar "y") (HVar "x")) [("x",VInt 2),("y", VInt 30)] -- 2
h4 = hEval (HIf (HFalse :==: HTrue) (HVar "x" :+: HVar "y") (HVar "x")) [("x",VInt 2),("y", VInt 30)] -- 2
h5 = hEval (HIf (HFalse :==: HVar "x") (HVar "x" :+: HVar "y") (HVar "x")) [("x",VInt 2),("y", VInt 30)] -- *** Exception: Nu se pot compara
h6 = hEval (HVar "x") [("x",VInt 2),("y", VInt 30)] -- 2
h7 = hEval (HVar "x") [("z",VInt 2),("y", VInt 30)] -- eroare                                                      

                                


--4
run :: Hask -> String
run pg = show (hEval pg [])

test :: Value
test = hEval (HLam "varA" (HLit 1 :+: HVar "varA") :$: HLit 5) []
pg1 =(HLit 1 :+: HLit 2 :==: HLit 3) :==:HTrue
pg2 = HLam "varA" (HVar "varA" :+: HLit 5 :*: HLit 3) :$: HIf pg1 (HLit 0) (HLit 1)
pg3 = HFalse :+: HTrue
