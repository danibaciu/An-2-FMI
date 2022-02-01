{-
class Functor f where
fmap :: ( x -> b ) -> f x -> f b

-}
{-# LANGUAGE InstanceSigs #-}

newtype Identity a = Identity a
                 deriving (Show)
instance Functor Identity where
    fmap :: (t -> x) -> Identity t -> Identity x
    fmap f (Identity x)=Identity (f x)

data Pair x = Pair x x
            deriving(Show)
instance Functor Pair where
    fmap :: (x->b)->Pair x ->Pair b  
    fmap f (Pair x1 x2) = Pair (f x1) (f x2)

data Constant x b = Constant b
                    deriving(Show)
instance Functor (Constant c) where 
    fmap :: (x->y)->Constant c x -> Constant c y
    fmap f (Constant x)=Constant (f x)
data Two x y = Two x y
                deriving(Show)
instance Functor (Two c) where
    fmap ::(x->y)->Two c x ->Two c y
    fmap f (Two c x)=Two  c (f x)   
       

data Three x y z = Three x y z
                    deriving (Show)
instance Functor (Three x y) where
    fmap::(c->d)->Three x y c->Three x y d
    fmap f (Three x y c)=Three x y (f c)

data Three' x y = Three' x y y
                    deriving (Show)
instance Functor (Three' x) where
    fmap::(c->d)->Three' x c->Three' x d
    fmap f (Three' x c1 c2)=Three' x (f c1) (f c2)

data Four a b c d = Four a b c d
                    deriving(Show)
instance Functor (Four a b c ) where
    fmap::(d->e)->Four a b c d->Four a b c e    
    fmap f (Four a b c d)=Four a b c (f d)
data Four'' a b = Four'' a a a b
                  deriving(Show)
instance Functor (Four'' a  ) where
    fmap::(d->e)->Four'' a  d->Four'' a  e    
    fmap f (Four'' a a1 a2 d4)=Four'' a a1 a2 (f d4)
data Quant a b = Finance | Desk a | Bloor b    
                    deriving (Show)
instance Functor (Quant a) where
    fmap::(b->c)->Quant a b->Quant a c
    fmap _ (Desk a)=Desk a
    fmap _ (Finance)=Finance
    fmap f (Bloor b)=Bloor (f b)



data LiftItOut f a = LiftItOut (f a)
                     deriving (Show)
instance Functor f=>Functor (LiftItOut f) where
    fmap::(a->b)->LiftItOut f a->LiftItOut f b
    fmap f1 (LiftItOut fa)=LiftItOut (fmap f1 fa)
    

data Parappa f g a = DaWrappa (f a) (g a)
                      deriving (Show)
instance (Functor f,Functor g) => Functor (Parappa f g) where
    fmap::(a->b)->Parappa f g a->Parappa f g b
    fmap f1 (DaWrappa fa ga)=DaWrappa (fmap f1 fa) (fmap f1 ga)
data IgnoreOne f g a b = IgnoringSomething (f a) (g b)
                        deriving (Show)
instance (Functor f, Functor g)=>Functor (IgnoreOne f g a) where
    fmap::(b->c)->IgnoreOne f g a b->IgnoreOne f g a c  
    fmap f1 (IgnoringSomething fa gb)=IgnoringSomething  fa (fmap f1 gb)

data Notorious g o a t = Notorious (g o) (g a) (g t)
                         deriving (Show)
instance Functor g=>Functor(Notorious g o a) where
    fmap::(t->b)->Notorious g o a t->Notorious g o a b
    fmap f1 (Notorious fo fa ft)=Notorious fo fa (fmap f1 ft)
data GoatLord a = NoGoat | OneGoat a | MoreGoats (GoatLord a) (GoatLord a) (GoatLord a)
                          deriving (Show)
instance Functor GoatLord where
    fmap::(a->b)->GoatLord a->GoatLord b
    fmap _ (NoGoat) =NoGoat
    fmap f (OneGoat a)=OneGoat(f a)
    fmap f (MoreGoats a1 a2 a3)=MoreGoats (fmap f a1) (fmap f a2) (fmap f a3)
data TalkToMe a = Halt | Print String a | Read (String -> a) 
instance Show a=> Show(TalkToMe a) where
    show Halt="Halt"
    show (Print s a)="Print "++s++" "++show a
    show (Read f)="Read "++show (f "")

instance Functor TalkToMe where
    fmap::(a->b)->TalkToMe a->TalkToMe b
    fmap _ (Halt)=Halt
    fmap f (Read a)=Read (f.a)
    fmap f (Print s a)=Print s (f a)


c= fmap (+1) (MoreGoats (MoreGoats (OneGoat 5) (OneGoat 6) (OneGoat 7)) (OneGoat 6) (OneGoat 7))                    