
import Data.Maybe

bla = 
    Just 4 >>= \x ->
    mult10 x >>= \y ->
    Just 2 >>= \z ->
    return (y + z)

mult10 :: Int -> Maybe Int
mult10 x = Just $ 10 * x
