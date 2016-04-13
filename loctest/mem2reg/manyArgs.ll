; ModuleID = 'manyArgs.bc'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i64 @stuff(i64 %a, i64 %b, i64 %c, i64 %d, i64 %e, i64 %f, i64 %g, i64 %h, i64 %j) #0 {
entry:
  %add = add nsw i64 %a, %b
  %add1 = add nsw i64 %add, %c
  %add2 = add nsw i64 %add1, %d
  %add3 = add nsw i64 %add2, %e
  %add4 = add nsw i64 %add3, %f
  %add5 = add nsw i64 %add4, %g
  %add6 = add nsw i64 %add5, %h
  %add7 = add nsw i64 %add6, %j
  ret i64 %add7
}

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %call = call i64 @stuff(i64 1, i64 1, i64 1, i64 1, i64 1, i64 1, i64 2, i64 2, i64 2)
  %conv = trunc i64 %call to i32
  ret i32 %conv
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.9.0 (http://llvm.org/git/clang.git e88720a6287e5fa399e833ed5ddf4f0b475c37bd) (http://llvm.org/git/llvm.git 9867695c88ba0998618aa879e86315800c49c7c8)"}
