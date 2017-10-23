module F2 where

import Data.List
import Evol

instance Evol MolSeq where
    distance m1 m2 = seqDistance m1 m2
    name n = molName n 

instance Evol Profile where
    distance p1 p2 = profileDistance p1 p2
    name n = proName n
-- Value constructor
-- Skapar automatiskt funktionerna molName :: String etc.
data MolSeq = MolSeq {
    molName     :: String,
    sequence    :: String,
    molType 	:: Type
    } deriving(Show) -- Can be converted to string


data Profile = Profile{
    proName :: String,
    matrix      :: [[(Char, Int)]],
	  proType     :: Type,
	  nrOfSeqs    :: Int
} deriving(Show)

-- Type constructor.
data Type = DNA | Protein deriving (Show, Eq) -- Can be converted to string and compared

distanceMatrix a = [(name a, name y, distance a y) | t@(a:_) <- tails a, y <- t]

-- Input: Sequence name and sequence Output: MolSeq
string2seq :: String -> String -> MolSeq
string2seq molName sequence = MolSeq molName sequence (getMolType sequence)

{--Return the MolSeq parameters that the function names imply --}
seqName :: MolSeq -> String
seqName (MolSeq molName _ _) = molName

seqSequence :: MolSeq -> String
seqSequence (MolSeq _ sequence _) = sequence

seqLength :: MolSeq -> Int
seqLength (MolSeq _ sequence _) = length(sequence)

-- Get molType by sequence
getMolType :: String -> Type
getMolType str =  if (filter(==True) (map (`notElem` dnaChars) str)) == [] -- If str does not contain only dna-characters, return Protein. If protein [False, False,...].
			then DNA
			else Protein
        where
            dnaChars = "ACGT"

-- Return distance between two MolSeqs
seqDistance :: MolSeq -> MolSeq -> Double
seqDistance x y 
			| molType x /= molType y = error("Sequences cannot be matched")
      | seqLength x /= seqLength y = error("Different length")
			| molType x == Protein = proteinDistance totalDiff
			| otherwise = dnaDistance totalDiff
		where
                totalDiff = fromIntegral hammingDistance / fromIntegral (seqLength x) -- Difference for each position in the sequences
                hammingDistance = calcAlpha (seqSequence x) (seqSequence y) -- Number of positions where sequences differ

-- Add 1 to result if head from both sequences are not equal.
calcAlpha :: String -> String -> Int 
calcAlpha (x1:xs1) (x2:xs2) 
				| x1 == x2 = 0 + calcAlpha xs1 xs2
				| otherwise = 1 + calcAlpha xs1 xs2 
calcAlpha _ _ = 0 -- If inputs does not go through anything, return 0, i.e. two empty strings.

-- Jukes-Cantor formula
dnaDistance :: Double -> Double
dnaDistance alpha
		| alpha < 0.74 = (-3/4) * log(1 - (4*alpha/3))
		| otherwise = 3.3

-- Poisson-model
proteinDistance :: Double -> Double
proteinDistance alpha 
		| alpha <= 0.94 = (-19/20) * log(1 - (20*alpha/19))
		| otherwise = 3.7	

-------------------------------------------UPPGIFT 3--------------------------------------------------------


nucleotides = "ACGT"
aminoacids = sort "ARNDCEQGHILKMFPSTWYVX"

makeProfileMatrix :: [MolSeq] -> [[(Char, Int)]]
makeProfileMatrix [] = error "Empty sequence list"
makeProfileMatrix sl = res
  where 
    t = molType (head sl) -- Check if DNA or Protein
    defaults = 
      if (t == DNA) then
        zip nucleotides (replicate (length nucleotides) 0) -- Rad (i) zip together [A,C,G,T] and [0,0,0,0] (as tuples): [(A,0), (C,0), (G,0), (T,0)]
      else 
        zip aminoacids (replicate (length aminoacids) 0)   -- Rad (ii) zip with protein sequence instead
    strs = map seqSequence sl                              -- Rad (iii) strs en lista som innehåller alla sekvenser som matrisen skapas utifrån i.e. ["ACGTTGDT", "AAAACCGT", "ACGDTYGD"]
    tmp1 = map (map (\x -> ((head x), (length x))) . group . sort)(transpose strs)  
                                                           -- Rad (iv)  transponera listan strs och sortera samt gruppera varje sekvens och skapa listor av tuplar m.h.a. mappning den anonyma funktionen t.ex. ('A', 2)
                                                           -- Denna lista utav listor kommer endast att innehålla tuplar som har värden större än 0.
                                                           -- T.ex. ["ACGT", "AAAA"] = [[('A', 2)], [('A', 1), ('C', 1)], [('A', 1), ('G', 1)], [('A', 1), ('T', 1)]]
    equalFst a b = (fst a) == (fst b) -- Kolla ifall första elementet i två tuplar är lika
    res = map sort (map (\l -> unionBy equalFst l defaults) tmp1)	-- Adds missing tuples (the letters that are missing from defaults) to the res and then sorts them. Like so: [[("A", 2), ("C", 3), ("T", 0),("G", 1)], [("A", 4), ("C", 4), ("T", 5)]]
    																-- Sorting is done by the first element in the tuples first, if any are equal, the second elements are compared.
-- Jämför första elementet i tuplarna i tmp1 med defaults och fyll på med de bokstäver som inte finns.
-- Se om det första elementet i två tuplar är lika för tmp1 och defaults, om detta är fallet behövs inte denna bokstav läggas till.

molseqs2profile :: String -> [MolSeq] -> Profile
molseqs2profile x y = Profile x (makeProfileMatrix y) (molType(head y)) (length y)

profileName :: Profile -> String
profileName (Profile proName _ _ _) = proName

-------------------Profile Frequency------------------------

getList :: [[(Char, Int)]] -> Int -> [(Char, Int)]
getList m i
          | i == 0 = head m
          | otherwise = getList (tail m) (i-1) -- Call getList recursively until the list at position i has been found.

profileFrequency :: Profile -> Int -> Char -> Double
profileFrequency p i c = fromIntegral (snd (head filteredList)) / fromIntegral (nrOfSeqs p) -- Divide value of the specified tuple with number of sequences.
        where
            pickedList = getList (matrix p) i -- Get the list that represents the specified column.
            filteredList = (filter (\(a,_) -> a == c) pickedList) -- Filter for the tuple with given specified character

--------------------Profile distance------------------------        

profileDistance :: Profile -> Profile -> Double
profileDistance p1 p2 = countDistance (matrix p1) (matrix p2) p1 p2 -- Call countDistance with the 2 profiles specified and their corresponding matrices
  
countDistance :: [[(Char, Int)]] -> [[(Char, Int)]] -> Profile -> Profile-> Double
countDistance [] [] _ _ = 0
countDistance m1 m2 p1 p2 = a + countDistance (tail m1) (tail m2) p1 p2 -- Perform element-by-element calculation on the first column of values and call countDistance with the remaining tail.
        where a = countElementDistance (head m1) (head m2) p1 p2

countElementDistance :: [(Char, Int)] -> [(Char, Int)] -> Profile -> Profile -> Double
countElementDistance [] [] _ _ = 0
countElementDistance m1 m2 p1 p2 = abs(h1 - h2) + countElementDistance (tail m1) (tail m2) p1 p2 -- Calculate the difference between the calculated values h1 and h2 and call countElementDistance again with the remaining tail
        where
             h1 = fromIntegral (snd $ head m1) / fromIntegral (nrOfSeqs p1) -- Calculate the value of the first tuple in matrix one by dividing it by number of sequences
             h2 = fromIntegral (snd $ head m2) / fromIntegral (nrOfSeqs p2) -- -||- matrix two