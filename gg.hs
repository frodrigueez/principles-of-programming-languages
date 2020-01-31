-- Name: Fernanda Rodriguez

-- recursive generation part II: Haskell!!
-- to execute: ghc --make gg.hs
--			   ./gg

import System.Random  -- module for random function 

-- recursive generation functions. All need to generate random number.
-- function to pick 'actor'
pick_actor :: Int -> [Char]
pick_actor x = (actors !! x)
	where actors = ["Grocer1", "Grocer2", "Warehouse1", "Warehouse2", "Market1", "Market2"]

-- function to pick 'action'
pick_action :: Int -> [Char]
pick_action x = (actions !! x)
	where actions = ["buy", "sell", "deliver", "pick up"]

-- function to pick 'acted'
pick_acted :: Int -> [Char]
pick_acted x = (acted !! x)
	where acted = ["rice", "asparagus", "lettuce", "apples", "oranges", "bread", "celery"]


-- function to recursively generate order:
-- if 7	 	print EPSILON,
-- else 	generate order.
-- this needs to be called recursively, with generator.
order :: StdGen -> IO()
order gen = do 
	-- use g to generate a random number and a new generator 
	let ( randNumber, newgen ) = randomR(1,100) gen :: (Int, StdGen)
	if randNumber == 7 
		then putStrLn("EPSILON")
	else do
		let (actor, newergen1) = randomR(0,5) newgen :: (Int, StdGen)
		let (action, newergen2) = randomR(0,3) newergen1 :: (Int, StdGen)
		let (acted, newergen3) = randomR(0,6) newergen2 :: (Int, StdGen)
		putStrLn("ORDER:   " ++ pick_actor(actor) ++ " " ++ pick_action(action) ++ " " ++ pick_acted(acted))
		order(newergen3)

main = do
	-- call order with random generator for system
	gen <- getStdGen

	let epsilon = 7
	-- opening procedure
	putStrLn "Orders of the day:"
	putStrLn "=================="

	order(gen)
