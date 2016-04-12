; ModuleID = 't3mem.bc'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i64 @anotherfoo(i64 %a, i64 %b) #0 {
entry:
  %add = add nsw i64 %a, %b
  %add1 = add nsw i64 %a, %b
  %add2 = add nsw i64 %add1, %add
  ret i64 %add
}

; Function Attrs: nounwind uwtable
define i64 @foo(i64 %a, i64 %b, i64 %c) #0 {
entry:
  %call = call i64 @anotherfoo(i64 %a, i64 %b)
  %add = add nsw i64 %a, %b
  %add1 = add nsw i64 %add, %call
  ret i64 %add1
}

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %add = add nsw i64 0, 2
  %add1 = add nsw i64 %add, 0
  %add2 = add nsw i64 %add, 2
  %call = call i64 @foo(i64 %add, i64 %add1, i64 %add2)
  ret i32 0
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.9.0 "}
