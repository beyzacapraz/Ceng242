module PE1 where

import Text.Printf

-- PE1: Recipe Calculator
-- The premise of this homework if to write a recipe calculator that
-- calculates: how much a recipe costs to make, what can be made with the
-- ingredients already available, and how much extra ingredients need to
-- be bought in order to make a recipe.

-- Recipe = Recipe Name [(Ingredient, Quantity)]
data Recipe = Recipe String [(String, Double)] deriving Show

-- Price = Price Ingredient Quantity Price
data Price = Price String Double Double deriving Show

-- You can use this as-is
getRounded :: Double -> Double 
getRounded x = read s :: Double
               where s = printf "%.2f" x

-- Calculate how much the given amount of the given ingredient costs
getIngredientCost :: (String, Double) -> [Price] -> Double
getIngredientCost x ((Price name amount price): rest) =  let ingredient = fst x
                                                             quantity = snd x
                                                             result = (quantity/ amount)* price
                                                         in if name == ingredient then getRounded result 
                                                            else getIngredientCost x rest
                        

-- Calculate how much it costs to buy all the ingredients of a recipe
recipeCost :: Recipe -> [Price] -> Double
recipeCost (Recipe name []) price = 0
recipeCost (Recipe name ((ingredients):rest)) price = let result = getIngredientCost ingredients price
                                                      in  result + recipeCost (Recipe name rest) price


-- Given a list of how much you already have of each ingredient,
-- calculate how much of which ingredients are missing for a recipe
missingIngredients :: Recipe -> [(String, Double)] -> [(String, Double)]
missingIngredients (Recipe name []) stock = []
missingIngredients (Recipe name ((ingredients):rest)) stock = helper stock ingredients ++ missingIngredients (Recipe name rest) stock
helper :: [(String, Double)] -> (String, Double) -> [(String, Double)]
helper [] recipe = [recipe]
helper ((stock): xs) recipe =   if fst stock == fst recipe then if snd recipe > snd stock then [(fst stock, getRounded(snd recipe - snd stock))]
                                                                else []
                                else helper xs recipe


-- Given a list of ingredients in your kitchen, calculate what you would
-- have left after making the given recipe. If there isn't enough of an
-- ingredient, the recipe cannot be made! You shouldn't change the amount
-- of ingredient in that case.
makeRecipe :: [(String, Double)] -> Recipe -> [(String, Double)]
makeRecipe stock (Recipe name ingredients) = if (missingIngredients (Recipe name ingredients) stock) /= []   then stock
                                             else makeRecipe2 stock (Recipe name ingredients)

makeRecipe2 :: [(String, Double)] -> Recipe -> [(String, Double)]
makeRecipe2 [] (Recipe name ingredients) = []
makeRecipe2 stock (Recipe name ingredients) = helperRecipe (head stock) ingredients ++ makeRecipe2 (tail stock) (Recipe name ingredients)
                                             
helperRecipe :: (String, Double) -> [(String, Double)] -> [(String, Double)]
helperRecipe stock [] = [stock]
helperRecipe stock ((recipe): xs) = if fst stock == fst recipe then  [(fst stock, getRounded(snd stock - snd recipe))]
                                    else helperRecipe stock xs



      
                                              

-- Given a list of ingredients you already have, and a list of recipes,
-- make a shopping list showing how much of each ingredient you need
-- to buy, and its cost. Each ingredient mush appear in the shopping list
-- at most once (no duplicates!).
makeShoppingList :: [(String, Double)] -> [Recipe] -> [Price] -> [(String, Double, Double)]
makeShoppingList stock recipe price = let check_list =  missingIngredients2 (littleList (makeList recipe)) stock
                                          index = check2 check_list 0
                                      in if index == -1 then helperShop check_list price
                                         else helperShop (take (index+1) check_list) price 
-- Duplicateler için ayrı bir işlem yap!! öncr tek bir tupple listesi sonra stock la karşılaştırdığın başka bir func                                          
helperShop :: [(String,Double)] -> [Price] -> [(String, Double, Double)]
helperShop [] price = []
helperShop ((missing): rest) price = let money = getIngredientCost missing price
                                     in [(fst missing, snd missing, money)] ++ helperShop rest price
makeList :: [Recipe] -> [(String, Double)]
makeList []   = [] 
makeList ((Recipe name ingredients):rest)  = ingredients ++ makeList rest

littleList :: [(String, Double)] -> [(String, Double)]
littleList [] = []
littleList list = leastList (head list) (tail list) ++ littleList (tail list)

leastList :: (String, Double) -> [(String, Double)] -> [(String, Double)]
leastList a [] = [a]
leastList a ((b):rest) = if fst a == fst b then [(fst a, getRounded(snd a + snd b))]
                         else leastList a rest
missingIngredients2 :: [(String, Double)] -> [(String, Double)] -> [(String, Double)]
missingIngredients2 [] stock = []
missingIngredients2 ((a):rest) stock = helper stock a ++ missingIngredients2 rest stock

check2 :: [(String, Double)] -> Int -> Int
check2 [] _ = -1
check2 list n = let x = index (head list) (tail list) (n)
               in if x == -1 then check2 (tail list) (n+1)
                  else x

index :: (String, Double) -> [(String, Double)] -> Int -> Int
index _ [] _ = -1
index a ((b):rest) n = if fst a == fst b then n
                       else index a rest (n+1)






