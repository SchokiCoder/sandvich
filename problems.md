# Problems 

## Constants performance and safety
In C, the constant's values are baked into the binary file.  
Trying to change a constant directly, will alert the compiler, we can sneak
around the compiler with a pointer however.  
Doing so will unsurprisingly result in a SEGFAULT.  
  
To implement constants in an interpreter it would need to check at each
variable assignment if the current variable is constant or not.  
Maybe it would lose that performance penalty upon JITing the code but until
that point, performance is universally gimped.  

Another point of concern is that if we bake the constant's value into binary
via JITing, from that moment on assigning to a constant would result in a
SEGFAULT.  
Potentially leaving a programmer or end-user with no useful debug
oppurtinites.  

## Types performance and safety
Literally everything from "Constants performance and safety", when
"constant's values" is replaced with "variables types".  
It also doe not cause segfault's (probably) but it could cause int overflows
after JITing.  
Who knows what else it would break.

## Variable declaration
Something i wanted to have, because i hate typos and accidentally creating a
new variable und leaving another one without an update in a certain case will
lead to unexpected behavior.  
Too bad this also would require a runtime check, gimping performance yet
again.  

# Conclusion
My entire language falls apart by it's design.  
I might would have had a mental breakdown, if it weren't for my overall
experience.  
I did not yet start implementing everything and waited for my planning to
finish (aside from some minor playing around).  
  
Instead i just feel enlightened. I finally understand that languages designed
for interpretation don't have types, declarations, constants and other good
shit for a very good reason.  
  
I think this knowledge should be spread, because whenever i tried to do any
research like "statically typed interpreted languages" i just found nothing all
the time, which made me think: "This does not exist yet, i should totally do
it."  
  
Instead what should have found, is this very conclusion, telling me that it is
possible, but with quite a few downsides, which is why no one ever bothered.  

# What happens now?
Can we never have these good things in a script-language?  
How can i make sure, that my script works?  
Linters... yup that's it... good night everyone.  

Python provides type hints, which i interpreted as a cruel joke back when i was
less informed but now see as a blessing since it feeds your linter.  

So a language could be made for interpreters, specifically designed to feed a
linter... or we just use a language which already comes with constants,
declarations, types and just use/write an interpreter for it.  

The only other way of implementing this is to just enforce these things via a
compiler AOT... kind of like TypeScript.  

