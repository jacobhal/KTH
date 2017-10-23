module Evol (Evol(..)) where

import Data.List

class Evol a where
	distance       :: a -> a -> Double
	name           :: a -> String
	distanceMatrix :: [a] -> [(String, String, Double)]

   -- Input: [a] = [MolSeq "Hej" "ACCGTD" DNA, MolSeq "Kbry" "ACDDGT" DNA]
   -- tails [a] = [[M1, M2], [M2], []]
   -- Sätt t till ett värde som börjar med a och välj sedan ett b av t. På så sätt 
   -- får man endast med ("Hej", "Kbry", distance) och inte ("Kbry", "Hej", distance)

   -- Exempel för tuplar av storlek 2:
   -- Input: [a] = ["a", "b", "c"]
   -- Tails [a] = [["abc"], ["bc"], ["c"], []]
   -- Output = [('a', 'a'), ('a', 'b'). ('a', 'c'), ('b', 'b'), ('b', 'c'), ('c', 'c')]
   -- Med alla kombinationer = [('a', 'a'), ('a', 'b'). ('a', 'c'), ('b', 'a'), ('b', 'b'), ('b', 'c'), ('c', 'a'), ('c', 'b'), ('c', 'c')]
   -- Istället för att beräkna alla kombinationer kommer t@(a:_) att säkerställa a som första element i de tuplar som skapas där
   -- a är första elementet i varje lista som produceras av tails a. Vi väljer med andra ord ut en character b som ska efterfölja a m.h.a y <- t.
	distanceMatrix a = [(name a, name y, distance a y) | t@(a:_) <- tails a, y <- t] -- Pair every element in a list with itself and all elements to the right.