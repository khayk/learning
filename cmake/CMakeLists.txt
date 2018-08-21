cmake_minimum_required(VERSION 3.10)

function(func resultVar1 resultVar2)
    set(${resultVar1} "First result" PARENT_SCOPE)
    set(${resultVar2} "Second result" PARENT_SCOPE)
endfunction()

func(myVar otherVar)

message("myVar: ${myVar}")
message("otherVar: ${otherVar}")
