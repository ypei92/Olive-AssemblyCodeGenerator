; ModuleID = 't1mem.bc'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i32 @foo(i32 %a, i32 %b, i32 %c) #0 {
entry:
  %add = add nsw i32 %a, %b
  %add1 = add nsw i32 %add, %c
  ret i32 %add1
}

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %add = add nsw i32 0, 2
  %add1 = add nsw i32 %add, 0
  %add2 = add nsw i32 %add, 2
  %call = call i32 @foo(i32 %add, i32 %add1, i32 %add2)
  ret i32 0
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.9.0 "}
